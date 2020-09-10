<?php

/**
 * @file
 * Carousel for search page with zero results.
 */

$plugin = array(
  'title' => t('Ting zero hit search carousel'),
  'single' => TRUE,
  'description' => t('A carousel for when there is no search results'),
  'category' => t('ereolen.dk'),
  'render callback' => 'reol_zero_search_carousel_content_type_render',
  'edit form' => 'reol_zero_search_carousel_content_type_edit_form',
  'admin title' => 'reol_zero_search_carousel_content_type_admin_title',
);

/**
 * Return the pane contents.
 */
function reol_zero_search_carousel_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();

  $search_result = drupal_static('ting_search_results');
  if (isset($search_result)) {
    $results = isset($search_result->numTotalObjects) ? (int) $search_result->numTotalObjects : 0;
  }

  if (($results < 1) && ($searches = variable_get('reol_zero_search_carousel_search_queries', array()))) {
    $tabs = array();
    foreach ($searches as $index => $search) {
      $chunk = _reol_zero_search_get_frontpage_covers($index, 0, TING_SEARCH_CAROUSEL_CHUNK_SIZE, TRUE);
      $tabs[$index] = array(
        'title' => $search['title'],
        'subtitle' => $search['subtitle'],
        'path' => 'reol_zero_search/results/ajax/' . $index,
        'content' => $chunk['collections'],
        'offset' => $chunk['next_offset'],
        'placeholders' => TING_SEARCH_CAROUSEL_CHUNK_SIZE,
      );
    }

    $vars = array(
      'tabs' => $tabs,
      'transition' => variable_get('reol_zero_search_carousel_transition', 'fade'),
      'show_description' => variable_get('reol_zero_search_carousel_description_toggle', FALSE),
    );
    $block->content = theme('ting_search_carousel', $vars);
  }

  return $block;
}

/**
 * Return the pane title.
 */
function reol_zero_search_carousel_content_type_admin_title($subtype, $conf, $context) {
  return t('Ting zero hit search carousel');
}

/**
 * Returns an edit form for the content type.
 */
function reol_zero_search_carousel_content_type_edit_form($form, &$form_state) {
  return $form;
}
