/**
 * Main javascript file for Wille theme.
 */
(function($) {
  /**
   * Toggle the footer menus.
   */
  Drupal.behaviors.footerToggle = {
    attach : function(context, settings) {

      $('.footer .pane-title', context).click(function() {

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
    attach : function(context, settings) {
      $('.icon-menu', context).click(function() {
        $('.topbar .menu').slideToggle(200);
      });
    }
  };

  /**
   * Subject menu.
   *
   * Initialize slick.js for the subject menu.
   */
  Drupal.behaviors.subjectMenu = {
    attach : function(context, settings) {
      $( document ).ready(function() {
        $('.subject-menu', context).slick({
          infinite: true,
          slidesToShow: 6,
          slidesToScroll: 5
        });
      });
    }
  };

})(jQuery);
