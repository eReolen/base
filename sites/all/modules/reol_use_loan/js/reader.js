(function($) {
  Drupal.behaviors.reader = {
    attach : function() {
      $('.reader .fullscreen-toggle').click(function() {
        $(this).closest('.reader').toggleClass('fullscreen');
        // Set focus on iframe to allow keyboard navigation.
        $(this).closest('.reader').find('iframe').focus();
      });
    }
  };
})(jQuery);
