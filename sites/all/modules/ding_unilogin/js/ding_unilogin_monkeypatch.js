/**
 * @file
 * Monkeypatch AJAX to note which popup was triggered.
 */

(function ($) {
  'use strict';

  Drupal.ding_unilogin = Drupal.ding_unilogin || {};

  /**
   * Global variable for the id of the link of the last opened popup.
   */
  Drupal.ding_unilogin.last_clicked = null;

  /**
   * Patch AJAX to note the link clicked before opening popups.
   *
   * We have to find all .use-ajax links and look them up in
   * Drupal.ajax, as we can't just traverse Drupal.ajax because it's
   * really a function.
   */
  Drupal.behaviors.ding_unilogin_patchajax = {
    attach: function (context, settings) {
      $('.use-ajax', context).once('ding-unilogin-boobytrap', function () {
        var id = $(this).attr('id');
        if (id) {
          if (typeof Drupal.ajax[id] !== 'undefined') {
            // Add in our own beforeSend that saves the id first.
            var oldBeforeSend = Drupal.ajax[id].options.beforeSend;
            Drupal.ajax[id].options.beforeSend = function() {
              Drupal.ding_unilogin.last_clicked = id;
              oldBeforeSend();
            };
          }
        }
      });
    }
  };

  /**
   * Re-triggers a popup.
   *
   * Will click on the link with the id given, in order to trigger the
   * popup opening.
   */
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
  };
})(jQuery);
