/**
 * @file
 * Autosubmit on select in the ting_search_autocomplete dropdown.
 */

(function ($) {
  Drupal.behaviors.autoSubmitOnMobile = {
    attach: function (context, settings) {
      $('.search-form input[name="search_block_form"]').on('autocompleteSelect', function (e) {
        e.target.form.submit();
      })
    }
  };
})(jQuery);
