/**
 * @file
 * Behaviors for reol_base.
 */

(function ($) {
  'use strict';

  Drupal.behaviors.modalClose = {
    attach: function (context, setting) {
      $('.modal-close').click(function (e) {
        Drupal.ding_popup.close({name: $(this).data('modal-name')});
        e.preventDefault();
      });
    }
  };
})(jQuery);
