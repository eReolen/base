/**
 * Main javascript file for Wille theme.
 */
(function($) {
  /**
   * Toggle the footer menus.
   */
  Drupal.behaviors.footerToggle = {
    attach : function() {

      $('.footer .pane-title').click(function() {

        var element = $(this).next().find('ul');

        // Make sure the right classes are added, so we can
        // make sure the arrow points in the right direction.
        if ( element.css('display') === 'none') {
          $(element).slideDown(200);
          $(this).addClass('open');
          $(this).removeClass('closed');
        } else {
          $(this).removeClass('open');
          $(this).addClass('closed');
          $(element).slideUp(200);
        }
      });

    }
  };

  /**
   * Toggle burger menu.
   */
  Drupal.behaviors.burgerMenu = {
    attach : function() {
      $('.icon-menu').click(function() {
        $('.topbar .menu').slideToggle(300);
      });
    }
  };
})(jQuery);
