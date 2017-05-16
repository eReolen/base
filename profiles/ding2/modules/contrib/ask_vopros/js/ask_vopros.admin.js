/**
 * @file
 * JavaScript functions for the ask_vopros admin page.
 */

(function ($) {
  Drupal.behaviors.askVoprosAdmin = {
    attach: function (context, settings) {
      $('#ask-vopros-settings .form-item-ask-vopros-color').once('ask-vopros-admin-color', function () {
        var input = $('input', this)
        // Farbtastic doesn't update an empty input element.
        if (input.val() == '') {
          input.val(' ');
        }
        $(this).append('<div id="placeholder"></div>')
        $('#placeholder').farbtastic(input);
      });
    }
  }
})(jQuery);
