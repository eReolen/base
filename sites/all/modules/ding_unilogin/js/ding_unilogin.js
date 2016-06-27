/**
 * @file
 * JS to activate the UNI•Login button.
 */

(function($) {
  "use strict";
  Drupal.behaviors.ding_unilogin = {
    attach: function (context, settigs) {
      $('.unilogin-button', context).once('ding-unilogin', function () {
        var link = $(this);
        // Double encoded to avoid that the web server interprets it.
        var path = encodeURIComponent(encodeURIComponent(window.location.href));
        $.getJSON('/ding_unilogin/get/' + path, function (data) {
          link.attr('href', data.url);
          link.removeClass('element-hidden');
        });
      });
    }
  }
})(jQuery);
