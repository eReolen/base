<?php

/**
 * @file
 * Displays the search form block.
 *
 * Available variables:
 * - $search_form: The complete search form ready for print.
 * - $search: Associative array of search elements. Can be used to print each
 *   form element separately.
 *
 * Default elements within $search:
 * - $search['search_block_form']: Text input area wrapped in a div.
 * - $search['actions']: Rendered form buttons.
 * - $search['hidden']: Hidden form elements. Used to validate forms when
 *   submitted.
 *
 * Modules can add to the search form, so it is recommended to check for their
 * existence before printing. The default keys will always exist. To check for
 * a module-provided field, use code like this:
 * @code
 *   <?php if (isset($search['extra_field'])): ?>
 *     <div class="extra-field">
 *       <?php print $search['extra_field']; ?>
 *     </div>
 *   <?php endif; ?>
 * @endcode
 *
 * @see template_preprocess_search_block_form()
 */
?>
<div class="search-form js-search-form <?php print(arg(0) == 'search' ? 'open' : ''); ?>">
  <div class="search-form__icon__wrapper js-search-form-trigger">
    <i class="search-form__icon"></i>
  </div>
  <div class="search-form__content js-search-form-target">
    <!-- <i class="search-form__icon--close js-search-form-trigger-close"></i> -->
    <?php print $search_form; ?>
  </div>
</div>
