/**
 * @file
 * Autosubmit on select in the ting_search_autocomplete dropdown.
 */

(function ($) {
  'use strict';

  Drupal.behaviors.autoSubmitOnMobile = {
    attach: function (context, settings) {
      // First selector is eReolen, second is eReolenGo.
      $('.search-form input[name="search_block_form"], #search-block-form input[name="search_block_form"]').on('autocompleteSelect', function (e) {
        e.target.form.submit();
      });
    }
  };
})(jQuery);
