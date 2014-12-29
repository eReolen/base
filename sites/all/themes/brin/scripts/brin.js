(function($) {
  Drupal.behaviors.modalClose = {
    attach : function() {
      $('.modal-close').click(function() {
        Drupal.ding_popup.close({name: $(this).data('modal-name')});
      });
    }
  };
})(jQuery)
