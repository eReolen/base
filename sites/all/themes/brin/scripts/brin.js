(function($) {
  Drupal.behaviors.modalClose = {
    attach : function() {
      $('.modal-close').click(function() {
        Drupal.ding_popup.close({name: $(this).data('modal-name')});
      });
    }
  };

  // Scroll to top when opening a dialog.
  // Dialogs on this site can get pretty big - e.g. when viewing a reading sample.
  // This is furthermore problematic as scrolling is disabled.
  // In _popup.scss we force the popup to the top of the page. jQuery UI should
  // scroll the viewport to make the popup visible but scrolling does not happen on
  // Mobile safari and the popup is rendered out of sight. This forces the browser
  // to scroll to the top of the page when a popup is opened.
  Drupal.behaviors.modalScroll = {
    attach : function() {
      $('body').bind('dialogopen', function() {
        $.scrollTo(0, 0);
      });
    }
  };
})(jQuery);
