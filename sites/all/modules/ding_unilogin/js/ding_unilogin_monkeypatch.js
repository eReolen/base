/**
 * @file
 * Monkeypatch AJAX to note which popup was triggered.
 */

(function($) {
  "use strict";
  Drupal.ding_unilogin = Drupal.ding_unilogin || {};
  Drupal.ding_unilogin.last_clicked = null;

  Drupal.behaviors.ding_unilogin_patchajax = {
    attach: function (context, settings) {
      $('.use-ajax', context).once('ding-unilogin-boobytrap', function () {
        var id = $(this).attr('id');
        if (id) {
          if (typeof Drupal.ajax[id] !== 'undefined') {
            var oldBeforeSend = Drupal.ajax[id].options.beforeSend;
            Drupal.ajax[id].options.beforeSend = function() {
              Drupal.ding_unilogin.last_clicked = id;
              oldBeforeSend();
            }
          }
        }
      });
    }
  }

  Drupal.behaviors.ding_unilogin_trigger = {
    attach: function (context, settings) {
      var match;
      if (match = window.location.search.match(/(\?|&)ding-unilogin-trigger=([^&]+)/)) {
        var id = decodeURIComponent(match[2]);
        // Loose the GET parameter in modern browsers.
        if (window.history.replaceState) {
          window.history.replaceState({}, document.title, window.location.href.replace(/(\?|&)ding-unilogin-trigger=([^&]+)/, ''));
        }

        if (typeof Drupal.ajax[id] !== 'undefined') {
          $(Drupal.ajax[id].element).trigger('click');
        }
      }
    }
  }
})(jQuery);
