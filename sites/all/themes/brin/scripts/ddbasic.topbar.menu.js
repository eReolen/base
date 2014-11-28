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
    }
  };

  /**
   * Handling of the mobile menu.
   */
  Drupal.behaviors.brinMobileMenu = {
    attach : function() {
      $('.js-topbar-link.topbar-link-menu').on('click touchstart', function(e) {
        $('.site-header .js-topbar-menu').toggle();
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
        lis.removeClass('active');
        var li = $(this).closest('li').first();
        li.toggleClass('active');
          e.preventDefault();
          e.stopPropagation();
      });
    }
  };
})(jQuery);
