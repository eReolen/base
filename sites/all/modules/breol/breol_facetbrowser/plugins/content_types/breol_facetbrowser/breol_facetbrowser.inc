<?php

/**
 * @file
 * Replacement ding_facetbrowser content type.
 */

$plugin = array(
  'title' => t('BReol Facetbrowser'),
  'description' => t('Insert Ding facetbrowser on non-search pages'),
  'single' => TRUE,
  'content_types' => array('breol_facetbrowser'),
  'render callback' => 'breol_facetbrowser_content_type_render',
  'category' => t('eReolen for kids'),
  'render last' => TRUE,
);

/**
 * Callback function for the ctools content_type.
 *
 * Slightly adjusted version of ding_facetbrowser_content_type_render.
 */
function breol_facetbrowser_content_type_render($subtype, $conf, $panel_args, $context) {
  $block_content = FALSE;
  $content_in_facet = FALSE;
  $block = new stdClass();

  $block->module = 'ding_facetbrowser';
  $block->delta  = 'ding_facetbrowser';

  $path = drupal_get_path('module', 'ding_facetbrowser');
  drupal_add_js($path . '/js/jquery.cookie.min.js');
  drupal_add_js($path . '/js/ding_facetbrowser.js');
  drupal_add_js(array(
    'ding_facetbrowser' => array(
      'selector' => '.js-facet-browser-toggle',
      'number_of_terms' => variable_get('ding_facetbrowser_number_of_terms', 5),
    ),
  ), 'setting');

  // Invoke ding_facetbrowser() in ting_search.module.
  $results = module_invoke('ting_search', 'ding_facetbrowser');
  if (is_object($results)) {
    foreach ($results->facets as $result) {
      if (count($result->terms) == TRUE) {
        $content_in_facet = TRUE;
        break;
      }
    }
    if ($content_in_facet === TRUE || $results->show_empty == TRUE) {
      $block_content = theme('facetbrowser', array($results->facets, (!empty($results->searchkey) ? $results->searchkey : NULL)));
    }
  }
  $block->title = t('BReol Facetbrowser');
  $block->content = '<div class="js-facet-browser-toggle">' . $block_content . '</div>';
  return $block;
}

/**
 * Returns an edit form for settings.
 */
function breol_facetbrowser_breol_facetbrowser_content_type_edit_form($form, &$form_state) {
  return $form;
}
