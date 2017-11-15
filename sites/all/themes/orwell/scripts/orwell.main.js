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
      if ($('.main-login-form').length) {
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

  /**
   * Menu dropdown behavior.
   */
  Drupal.behaviors.menuDropdown = {
    attach: function (context) {
      $('.menu-level-2 li.expanded').once(function () {
        var menu = $(this);
        var trigger = menu.find('> a');
        var submenu = menu.find('ul');

        trigger.on('click', function (e) {
          e.preventDefault();
          // Stop propagation, so we don't immediately trigger the
          // click event we attach to the body.
          e.stopPropagation();

          // Close any other open submenus.
          menu.parent().find('.js-active').not(menu).click();

          if (!menu.hasClass('js-active')) {
            menu.addClass('js-active');
            // Dismiss the submenu when the mouse leaves it.
            submenu.on('mouseleave.ereolen', function () {
              trigger.click();
            });

            // Add a click handler to body to dismiss the submenu.
            $('body').on('click.ereolen', function (e) {
              trigger.click();
            });
          }
          else {
            menu.removeClass('js-active');
            submenu.off('mouseleave.ereolen');
            $('body').off('click.ereolen');
          }
        });
      });
    }
  };

})(jQuery);
