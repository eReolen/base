<?php
/**
 * @file
 * Panels pane to display page title with result count.
 */

$plugin = array(
  'title' => t('Ting search - page title'),
  'description' => t("Display title with result count."),
  'content_types' => array('ting_search'),
  'render callback' => 'ting_search_result_count_content_type_render',
  'category' => t('Ting'),
  'required context' => new ctools_context_required(t('Keywords'), 'string'),
  'render last' => TRUE,
);

/**
 * Render the ting search results amount block.
 */
function ting_search_result_count_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();

  $search_result = ting_search_current_results();
  if (isset($search_result)) {
    $results = $search_result->getNumTotalObjects();
    $block->content = array(
      'title' => array(
        '#theme' => 'html_tag',
        '#tag' => 'h1',
        '#attributes' => array('class' => array('page-title')),
        '#value' =>  t('Search result <span class="js-count" data-js-count="!count" class="search-field-in-content--amount">(!count !string)</span>', array(
          '!count' => $results,
          '!string' => format_plural($results > 1 ? $results : 1, 'Result', 'Results'),
        ))
      ),
    );
  }

  return $block;
}

/**
 * Enable admin settings page.
 */
function ting_search_search_result_count_content_type_edit_form($form, &$form_state) {
  return $form;
}
