/**
 * @file
 * Main javascript file for Pratchett theme.
 */

(function ($) {
  'use strict';

  /**
   * Make login link toggle login form.
   */
  Drupal.behaviors.loginFoldout = {
    attach: function (context) {
      // Only add the click-toggle behavior if we have a login form to toggle.
      if ($('.js-login-form').length) {
        $('.js-login-link', context).click(function (e) {
          e.preventDefault();
          $('.pane-user-login').toggle();
        });
      }
    }
  };

  /**
   * Slide toggle facets on search page on mobile.
   */
  Drupal.behaviors.searchPageFacets = {
    attach: function (context) {
      if ($('body.page-search').length) {
        var trigger = $('<div class="facets-trigger-wrapper"><div class="js-facets-trigger"></div><div>');
        $('.panel-col-first').prepend(trigger);

        trigger.on('click', function () {
          $('.panel-col-first').find('.inside').slideToggle();
        });
      }
    }
  };

})(jQuery);
