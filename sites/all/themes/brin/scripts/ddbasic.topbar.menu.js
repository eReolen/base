/**
 * Creates the top-bar toggle menu.
 */
(function($) {
  Drupal.behaviors.brinTopbar = {
    attach : function() {
      // Hide user login on load.
      $('.js-topbar-user').css("display", "none");

      // Show search on load.
      $('.js-topbar-search').css("display", "block");

      // Check if #login fragment is in url.
      var hash = window.location.hash;
      if (hash === "#login") {
        // Show login box.
        $('#login-link').trigger('click');
      }
    }
  };

  /**
   * Handling of the mobile menu.
   */
  Drupal.behaviors.brinMobileMenu = {
    attach : function() {
      $('.js-topbar-link.topbar-link-menu').on('click touchstart', function(e) {
        var menu = $('.site-header .js-topbar-menu');
        menu.toggle();
        // If we set it invisible, completely remove the display
        // property from the elements style, to fall back to what the
        // style sheets define. Else the menu would stay invisible after
        // re-sizing the window.
        if (menu.css('display') === 'none') {
          menu.css('display', '');
        }
        e.preventDefault();
      });
    }
  };

  /**
   * Main menu dropdown handler.
   */
  Drupal.behaviors.brinMainmenuDropdown = {
    attach : function() {
      var lis = $('.main-menu .main-menu > li:not(.leaf)');
      // Global handler that removes dropdowns on mouseclick.
      $(document).click(function () {
        lis.removeClass('active');
      });

      // Handler for menu items triggering dropdown.
      lis.find('> a').click(function(e) {
        var current = $(this).closest('li').first();
        var active = current.hasClass('active');
        $(this).closest('ul').children('li').removeClass('active');
        if (!active) {
          current.addClass('active');
        }
        e.preventDefault();
        e.stopPropagation();
      });

      // Expand first level menu items by default, for reasons of UX.
      var roots = $('.js-topbar-menu > .main-menu').children('li:not(.leaf)');
      roots.find('> a').each(function () {
        var li = $(this).closest('li').first();
        li.addClass('active-sm');
      });
    }
  };

  /**
   * Login box handler.
   */
  Drupal.behaviors.brinLoginBox = {
    attach : function() {
      $('.js-topbar-link.topbar-link-user').on('click touchstart', function(e) {
        $('.topbar-menu .leaf .topbar-link-user').toggleClass('active');
        $('.js-topbar-user').toggle();
      e.preventDefault();
    });
    }
  };

})(jQuery);
