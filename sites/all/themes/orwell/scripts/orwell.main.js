/**
 * @file
 * Main javascript file for Pratchett theme.
 */

(function ($) {
  'use strict';

  // Cookie set/get functions
  function setCookie(c_name, value, exdays) {
    var exdate = new Date();
    exdate.setDate(exdate.getDate() + exdays);
    var c_value = escape(value) + ((exdays==null) ? "" : ("; expires="+exdate.toUTCString()));
    document.cookie = c_name + "=" + c_value;
  }
  function getCookie(c_name) {
    var i,x,y,ARRcookies = document.cookie.split(";");
    for (i = 0; i < ARRcookies.length; i++) {
      x = ARRcookies[i].substr(0,ARRcookies[i].indexOf("="));
      y = ARRcookies[i].substr(ARRcookies[i].indexOf("=")+1);
      x = x.replace(/^\s+|\s+$/g,"");
      if (x==c_name) {
        return unescape(y);
      }
    }
  }

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
   * Toggle between grid and list view on results page
   */
  Drupal.behaviors.searchResultsGridToggle = {
    attach: function (context) {
      var initialView = 'list-view';
      var cookieName = 'eReol_2__searchResultArrangement';
      var expires = 1;

      // determine if we're on results page
      if ($('.search-results').length) {
        var $toggle = $('.arrangement-toggle');

        // Set initial view to what's stored in the cookie, otherwise set to list-view
        if (getCookie(cookieName) == 'list-view') {
          $('.search-results').addClass('list-view');
          $('.arrangement-toggle.toggle-list').addClass('toggle-active');
        } else {
          $('.search-results').addClass('grid-view');
          $('.arrangement-toggle.toggle-grid').addClass('toggle-active');
        }

        // When either toggle is clicked
        $toggle.on('click', function() {
          var $this = $(this);

          // Visually toggle button states
          $('.arrangement-toggle').removeClass('toggle-active');
          $this.addClass('toggle-active');

          // Set/update cookie to arrangement/view type
          if ($this.hasClass('toggle-list')) {
            setCookie(cookieName, "list-view", expires);
            $('.search-results').addClass('list-view').removeClass('grid-view');
          } else {
            setCookie(cookieName, "grid-view", expires);
            $('.search-results').addClass('grid-view').removeClass('list-view');
          }
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
