/**
 * @file
 * Behaviors for reol_base.
 */

(function($) {
  Drupal.behaviors.modalClose = {
    attach : function() {
      $('.modal-close').click(function(e) {
        Drupal.ding_popup.close({name: $(this).data('modal-name')});
        e.preventDefault();
      });
    }
  };
})(jQuery);
