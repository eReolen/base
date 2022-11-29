As of Drupal 7.79, a SameSite cookie attribute is set for Drupal's session cookies[1]. This module provides functionality in the Drupal Admin UI to customize the response sent to clients.

    Choose whether "None", "Lax", "Strict", or no attribute is sent.
    Work around legacy browsers that are unable to accept SameSite=None cookies

For general information on the SameSite cookie attribute, you can refer to this MDN documentation:
https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Set-Cookie/SameSite

For information about the legacy browsers that have problems with SameSite=None (that this module provides a workaround for), you can refer to this Chromium documentation:
https://www.chromium.org/updates/same-site/incompatible-clients
Per the Chromium documentation:

    Some user agents are known to be incompatible with the `SameSite=None` attribute.

        Versions of Chrome from Chrome 51 to Chrome 66 (inclusive on both ends). These Chrome versions will reject a cookie with `SameSite=None`. This also affects older versions of Chromium-derived browsers, as well as Android WebView. This behavior was correct according to the version of the cookie specification at that time, but with the addition of the new "None" value to the specification, this behavior has been updated in Chrome 67 and newer. (Prior to Chrome 51, the SameSite attribute was ignored entirely and all cookies were treated as if they were `SameSite=None`.)
        Versions of UC Browser on Android prior to version 12.13.2. Older versions will reject a cookie with `SameSite=None`. This behavior was correct according to the version of the cookie specification at that time, but with the addition of the new "None" value to the specification, this behavior has been updated in newer versions of UC Browser.
        Versions of Safari and embedded browsers on MacOS 10.14 and all browsers on iOS 12. These versions will erroneously treat cookies marked with `SameSite=None` as if they were marked `SameSite=Strict`. This bug has been fixed on newer versions of iOS and MacOS.


[1]: https://www.drupal.org/node/3207213
