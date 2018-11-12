/**
 * @file
 * JS to activate the UNI•Login button.
 */

(function ($) {
  'use strict';

  /**
   * Fetch the correct link, update the login link and show it.
   *
   * The login form loaded over AJAX doesn't now the path the user is
   * really on, so we hack it in with JS.
   */
  Drupal.behaviors.ding_unilogin = {
    attach: function (context, settings) {
      $('.unilogin-button', context).once('ding-unilogin', function () {
        var link = $(this);
        var path = window.location.href;
        // Add the id of the link clicked to open the popup, so we'll
        // be able to re-trigger it when returning from UNI•Login..
        if (Drupal.ding_unilogin.last_clicked) {
          // We'll encode the id once more to ensure that it'll stay
          // un-decoded all the way back to our triggering JS.
          path = path + (path.match(/\?/) ? '&' : '?') +
            'ding-unilogin-trigger=' + encodeURIComponent(Drupal.ding_unilogin.last_clicked);
        }
        // Double encoded to avoid that the web server decodes it.
        path = encodeURIComponent(encodeURIComponent(path));
        $.getJSON('/ding_unilogin/get/' + path, function (data) {
          link.attr('href', data.url);
          link.removeClass('element-hidden');
        });
      });
    }
  };
})(jQuery);
