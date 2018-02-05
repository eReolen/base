/**
 * @file
 * Behaviors for reol_search.
 */


(function ($) {

  'use strict';

  /**
   * Add auto submit on change for search block form radios.
   */
  Drupal.behaviors.reolSearchForm = {
    attach: function (context, settings) {
      $(context).find('#search-block-form #edit-search-type input').change(function (event) {
        // Kill potential Drupal alerting about ajax being stopped due to the
        // form being submitted.
        window.alert = function (text) {};
        $(this).parents('form').attr('action', $(this).val()).submit();
      }).filter(':checked').parent().addClass('selected');
    }
  };

}(jQuery));
