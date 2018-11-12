<?php
/**
 * @file
 * Panels pane to display page title with result count.
 */

$plugin = array(
  'title' => t('Ting search count'),
  'description' => t("Display result count."),
  'content_types' => array('search_result_count'),
  'category' => t('eReolen for kids'),
  'required context' => new ctools_context_required(t('Keywords'), 'string'),
  'render last' => TRUE,
);

/**
 * Render the ting search results amount block.
 */
function breol_frontend_search_result_count_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();

  $search_result = ting_search_current_results();
  if (isset($search_result)) {
    $results = $search_result->getNumTotalObjects();
    $string = format_plural($results,
      'Search result: 1 result',
      'Search result: @count results');
    $block->content = array(
      'title' => array(
        '#theme' => 'html_tag',
        '#tag' => 'div',
        '#attributes' => array('class' => array('page-title')),
        '#value' => $string,
      ),
    );
  }

  return $block;
}

/**
 * Enable admin settings page.
 */
function breol_frontend_search_result_count_content_type_edit_form($form, &$form_state) {
  return $form;
}
