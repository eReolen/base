# Marker to tell the VCL compiler that this VCL has been adapted to the
# new 4.0 format.
vcl 4.0;

# Import VMod's
# Used for std.healthy.
import std;
import directors;

# Backend server 0.
backend server0 {
    .host = "nginx0";
    .port = "80";
}

# Backend server 1.
backend server1 {
    .host = "nginx1";
    .port = "80";
}

# Group the backend servers into an director to use varnish as load balancing.
sub vcl_init {
    new servers = directors.round_robin();
    servers.add_backend(server0);
    servers.add_backend(server1);
}

sub vcl_recv {
  # Send all traffic to the a backend server:
  set req.backend_hint = servers.backend();

  # Remove HTTP Authentication. Assume that any basic auth is handled
  # before reaching us and remove the header, as it messes with
  # caching.
  unset req.http.Authorization;

  if (req.method != "GET" && req.method != "HEAD") {
    # We only deal with GET and HEAD by default.
    return (pass);
  }

  # Special DDB CMS handling to check if a given page can be cached by logged in users.
  if (req.restarts == 0 && (req.method == "GET" || req.method == "HEAD")) {
    # Ignore any X-Drupal-Roles from the client.
    unset req.http.X-Drupal-Roles;

    # Lookup Drupal Roles. We're going to change the URL to
    # x-drupal-roles so we'll need to save the original one first.
    set req.http.X-Original-URL = req.url;
    set req.url = "/varnish/roles";

    return (hash);
  }

  # Patterns to pass through un-cached.
  if (req.url ~ "^/status\.php$" ||
      req.url ~ "^/update\.php$" ||
      req.url ~ "^/admin$" ||
      req.url ~ "^/admin/" ||
      req.url ~ "^/user$" ||
      req.url ~ "^/user/" ||
      req.url ~ "^/flag/" ||
      req.url ~ "/edit" ||
      req.url ~ "/ding_availability" ||
      req.url ~ "^/feeds") {
        return (pass);
  }

  # Use anonymous, cached pages if all backend's are down.
  if (!std.healthy(req.backend_hint)) {
    unset req.http.Cookie;
  }

  # Always cache the following file types for all users.
  if (req.url ~ "(?i)\.(pdf|asc|dat|txt|doc|xls|ppt|tgz|csv|png|gif|jpeg|jpg|ico|swf|css|js|json)(\?[\w\d=\.\-]+)?$") {
    unset req.http.Cookie;
  }

  # Remove all cookies that are not session cookies.
  if (req.http.Cookie) {
    # Save the original cookie header so we can mangle it
    set req.http.X-Varnish-PHP_SID = req.http.Cookie;
    set req.http.X-Varnish-PHP_SID = regsuball(req.http.X-Varnish-PHP_SID, ".*;? (S+ESS[a-zA-Z0-9]+)=([\w-]+)(|;| ;).*", "\1=\2");

    // If not cookies left unset the header.
    if (req.http.X-Varnish-PHP_SID == "") {
      unset req.http.Cookie;
    }
    else {
      // There where a session cookie so lets set it back,
      set req.http.Cookie = req.http.X-Varnish-PHP_SID;
    }
    unset req.http.X-Varnish-PHP_SID;
  }

  # Look up in the cache. ding_varnish sets the appropiate Vary
  # headers to make Varnish give each role its own cache bin.
  return (hash);
}

sub vcl_backend_response {
  // Compress content if backend don't do it.
  if (beresp.http.content-type ~ "text") {
    set beresp.do_gzip = true;
  }

  # Allow items to be stale if needed.
  if (beresp.http.ETag || beresp.http.Last-Modified) {
    set beresp.keep = 30m;
  }

  # We need this to cache 404s, 301s and 500s.
  if (beresp.status == 404 || beresp.status == 301 || beresp.status == 500) {
    set beresp.ttl = 10m;
  }

  # Remove cookies for stylesheets, scripts and images used throughout
  # the site. Removing cookies will allow Varnish to cache those
  # files. It is uncommon for static files to contain cookies, but it
  # is possible for files generated dynamically by Drupal. Those
  # cookies are unnecessary, but could prevent files from being
  # cached.
  if (bereq.url ~ "(?i)\.(pdf|asc|dat|txt|doc|xls|ppt|tgz|csv|png|gif|jpeg|jpg|ico|swf|css|js|json)(\?[\w\d=\.\-]+)?$") {
    unset beresp.http.set-cookie;
  }

  # Varnish actually honors Cache-Control: no-cache, despite the
  # number of Google hits claiming that it doesn't (3 didn't). Drupal
  # set no-cache in order to stop browsers from caching too much, so
  # we need to pass it through. We do this by copying it here and
  # fudge it. It's then restored in vcl_deliver.
  if (beresp.http.Cache-Control) {
    set beresp.http.X-Orig-Cache-Control = beresp.http.Cache-Control;
    set beresp.http.Cache-Control = regsuball(beresp.http.Cache-Control, "no-cache", "");
  }

  # If ding_varnish has marked the page as cachable simply deliver is to make
  # sure that it's cached.
  if (beresp.http.X-Drupal-Varnish-Cache) {
    return (deliver);
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
  if (resp.http.X-varnish ~ " ") {
    set resp.http.X-cache = "HIT";
  } else {
    set resp.http.X-cache = "MISS";
  }
}
