/**
 * @file
 * Handle destination on adgangsplatformen button.
 *
 * As the form is ajax load the current path is not available in drupal.
 */
(function ($) {
  'use strict';

  Drupal.behaviors.breol_base_adgangsplatformen = {
    attach: function (context, settings) {
      $('.adgangsplatformen-button').once(function() {
        var element = $(this);
        var path = window.location.pathname;
        if (path === '/') {
          path = '/user';
        }
        element.attr('href', element.attr('href') + '?destination=' + path);
      });
    }
  };
})(jQuery);
