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

  Drupal.behaviors.brinMainmenuDropdown = {
    attach : function() {
      var lis = $('.main-menu .main-menu > li:not(.leaf)');
      $('.main-menu .main-menu > li:not(.leaf) > a').click(function(e) {
        lis.removeClass('active active-trail');
        var li = $(this).parents('li').first();
        li.toggleClass('active active-trail');
          e.preventDefault();
      });
    }
  };
})(jQuery);
