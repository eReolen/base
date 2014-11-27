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
})(jQuery);
