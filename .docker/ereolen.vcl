#
# This is an VCL file for eReolen.
#
# Created by merging the Varnish 3 VCL for Ding2 (originally based on
# [1]) with Mateusz Papiernik' Varnish 4 VCL for Drupal [2], with
# tender love.
#
# [1] https://fourkitchens.atlassian.net/wiki/display/TECH/Configure+Varnish+3+for+Drupal+7
# [2] https://www.digitalocean.com/community/tutorials/how-to-speed-up-your-drupal-7-website-with-varnish-4-on-ubuntu-14-04-and-debian-7
#
# Might be useful for Ding2 sites in general.
#
# Marker to tell the VCL compiler that this VCL has been adapted to the
# new 4.0 format.
vcl 4.0;

# Import VMod's
# Used for std.healthy.
import std;

# Default backend definition. Set this to point to your content server.
backend default {
    .host = "nginx";
    .port = "80";
}

sub vcl_recv {
  # Remove HTTP Authentication. Assume that any basic auth is handled
  # before reaching us and remove the header, as it messes with
  # caching.
  unset req.http.Authorization;

  # The search-blank hack in ting_search doesn't work. Remove it for
  # the moment.
  if (req.url ~ "\?q=search-blank") {
    set req.url = regsuball(req.url, "\?q=search-blank", "");
  }

  # Ensure that ding_wayf and SimpleSAMLphp is not cached.
  if (req.url ~ "^/simplesaml" || req.url ~ "^/wayf") {
    return (pipe);
  }

  # Pipe these paths directly to Apache/NginX for streaming.
  if (req.url ~ "^/admin/content/backup_migrate/export") {
    return (pipe);
  }

  if (req.method != "GET" && req.method != "HEAD") {
    # We only deal with GET and HEAD by default.
    return (pass);
  }

  # Patterns to pass through un-cached.
  if (req.url ~ "^/status\.php$" ||
      req.url ~ "^/update\.php$" ||
      req.url ~ "^/admin$" ||
      req.url ~ "^/admin/" ||
      req.url ~ "^/user$" ||
      req.url ~ "^/user/" ||
      req.url ~ "^/flag/" ||
      req.url ~ "^.*/ajax/" ||
      req.url ~ "/ahah/" || 
      req.url ~ "/edit" ||
      req.url ~ "/ding_availability" ||
      req.url ~ "^/feeds") {
        return (pass);
  }

  # Use anonymous, cached pages if all backends are down.
  if (!std.healthy(req.backend_hint)) {
    unset req.http.Cookie;
  }

  # Always cache the following file types for all users.
  if (req.url ~ "(?i)\.(pdf|asc|dat|txt|doc|xls|ppt|tgz|csv|png|gif|jpeg|jpg|ico|swf|css|js)(\?[\w\d=\.\-]+)?$") {
    unset req.http.Cookie;
  }

  if (req.restarts == 0 && (req.method == "GET" || req.method == "HEAD")) {
    # Ignore any X-Drupal-Roles from the client.
    unset req.http.X-Drupal-Roles;

    # Lookup Drupal Roles. We're going to change the URL to
    # x-drupal-roles so we'll need to save the original one first.
    set req.http.X-Original-URL = req.url;
    set req.url = "/varnish/roles";

    return (hash);
  }

  # Remove all cookies that are not necessary for Drupal to work
  # properly. Since it would be cumbersome to REMOVE certain
  # cookies, we specify which ones are of interest to us, and remove
  # all others. In this particular case we leave SESS, SSESS and
  # NO_CACHE cookies used by Drupal's administrative interface.
  # Cookies in cookie header are delimited with ";", so when there
  # are many cookies, the header looks like "Cookie1=value1;
  # Cookie2=value2; Cookie3..." and so on. That allows us to work
  # with ";" to split cookies into individual ones.
  # Cookies are only removed for non-logged in users,
  # those with role 1 (anonymous user).
  if (req.http.Cookie && req.http.X-Drupal-Roles == "1") {
    # 1. We add ; to the beginning of cookie header
    set req.http.Cookie = ";" + req.http.Cookie;
    # 2. We remove spaces following each occurence of ";". After
    # this operation all cookies are delimited with no spaces.
    set req.http.Cookie = regsuball(req.http.Cookie, "; +", ";");
    # 3. We replace ";" INTO "; " (adding the space we have
    # previously removed) in cookies named SESS..., SSESS... and
    # NO_CACHE. After this operation those cookies will be easy to
    # differentiate from the others, because those will be the
    # only one with space after ";"
    set req.http.Cookie = regsuball(req.http.Cookie, ";(SESS[a-z0-9]+|SSESS[a-z0-9]+|NO_CACHE)=", "; \1=");
    # 4. We remove all cookies with no space after ";", so
    # basically we remove all cookies other than those above.
    set req.http.Cookie = regsuball(req.http.Cookie, ";[^ ][^;]*", "");
    # 5. We strip leading and trailing whitespace and semicolons.
    set req.http.Cookie = regsuball(req.http.Cookie, "^[; ]+|[; ]+$", "");

    # If there are no cookies after our striping procedure, we
    # remove the header altogether, thus allowing Varnish to cache
    # this page
    if (req.http.Cookie == "") {
      unset req.http.Cookie;
    }
    # if any of our cookies of interest are still there, we disable
    # caching and pass the request straight to Apache/NginX and Drupal
    else {
      return (pass);
    }
  }

  # Handle compression correctly. Different browsers send different
  # "Accept-Encoding" headers, even though they mostly all support the same
  # compression mechanisms. By consolidating these compression headers into
  # a consistent format, we can reduce the size of the cache and get more hits.
  # @see: http:// varnish.projects.linpro.no/wiki/FAQ/Compression
  if (req.http.Accept-Encoding) {
    if (req.http.Accept-Encoding ~ "gzip") {
      # If the browser supports it, we'll use gzip.
      set req.http.Accept-Encoding = "gzip";
    }
    else if (req.http.Accept-Encoding ~ "deflate") {
      # Next, try deflate if it is supported.
      set req.http.Accept-Encoding = "deflate";
    }
    else {
      # Unknown algorithm. Remove it and send unencoded.
      unset req.http.Accept-Encoding;
    }
  }

  # Look up in the cache. ding_varnish sets the appropiate Vary
  # headers to make Varnish give each role its own cache bin.
  return (hash);
}

sub vcl_backend_response {
  # Allow items to be stale if needed.
  set beresp.grace = 6h;

  # We need this to cache 404s, 301s, 500s. Otherwise, depending on backend but
  # definitely in Drupal's case these responses are not cacheable by default.
  if (beresp.status == 404 || beresp.status == 301) {
#  if (beresp.status == 404 || beresp.status == 301 || beresp.status == 500) {
    set beresp.ttl = 10m;
  }

  # Remove cookies for stylesheets, scripts and images used throughout
  # the site. Removing cookies will allow Varnish to cache those
  # files. It is uncommon for static files to contain cookies, but it
  # is possible for files generated dynamically by Drupal. Those
  # cookies are unnecessary, but could prevent files from being
  # cached.
  if (bereq.url ~ "(?i)\.(pdf|asc|dat|txt|doc|xls|ppt|tgz|csv|png|gif|jpeg|jpg|ico|swf|css|js)(\?[\w\d=\.\-]+)?$") {
    unset beresp.http.set-cookie;
  }

  # If ding_varnish has marked the page as cachable simply deliver is to make
  # sure that it's cached.
  if (beresp.http.X-Drupal-Varnish-Cache) {
    return (deliver);
  }

  # Varnish actually honors Cache-Control: no-cache, despite the
  # number of Google hits claiming that it doesn't (3 didn't). Drupal
  # set no-cache in order to stop browsers from caching too much, so
  # we need to pass it through. We do this by copying it here and
  # fudge it. It's then restored in vcl_deliver.
  # See https://www.varnish-ca che.org/trac/browser/bin/varnishd/default.vcl?rev=791321739fccc7fe5bfaabbad99b0d81b792c1f8&order=name
  if (beresp.http.Cache-Control) {
    set beresp.http.X-Orig-Cache-Control = beresp.http.Cache-Control;
    set beresp.http.Cache-Control = regsuball(beresp.http.Cache-Control, "no-cache", "");
  }
}

sub vcl_deliver {
  # If the response contains the X-Drupal-Roles header and the request URL
  # is right. Copy the X-Drupal-Roles header over to the request and restart.
  if (req.url == "/varnish/roles" && resp.http.X-Drupal-Roles) {
    set req.http.X-Drupal-Roles = resp.http.X-Drupal-Roles;
    set req.url = req.http.X-Original-URL;
    unset req.http.X-Original-URL;
    return (restart);
  }

  # Restore the unfudged Cache-Control.
  if (resp.http.X-Orig-Cache-Control) {
    set resp.http.Cache-Control = resp.http.X-Orig-Cache-Control;
    unset resp.http.X-Orig-Cache-Control;
  }

  # If response X-Drupal-Roles is not set, move it from the request.
  if (!resp.http.X-Drupal-Roles) {
    set resp.http.X-Drupal-Roles = req.http.X-Drupal-Roles;
  }

  # Remove server information
  set resp.http.X-Powered-By = "Ding T!NG";

  # Debug
  # In Varnish 4 the obj.hits counter behaviour has changed, so we use a
  # different method: if X-Varnish contains only 1 id, we have a miss, if it
  # contains more (and therefore a space), we have a hit.
  if (resp.http.x-varnish ~ " ") {
    set resp.http.x-cache = "HIT";
  } else {
    set resp.http.x-cache = "MISS";
  }
}
