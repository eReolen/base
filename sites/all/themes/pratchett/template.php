<?php

/**
 * @file
 * Preprocess and Process Functions.
 */

/**
 * Implements hook_js_alter().
 */
function pratchett_js_alter(&$javascript) {
  // Override script from ding_availability.
  $avail_js = drupal_get_path('module', 'ding_availability') . '/js/ding_availability_labels.js';
  $new_aval_js = drupal_get_path('theme', 'pratchett') . '/assets/scripts/ding_availability_labels.js';
  if (isset($javascript[$avail_js])) {
    $javascript[$avail_js]['data'] = $new_aval_js;
    $types = array();
    foreach (reol_base_get_types_by('ext_name') as $type) {
      $types[$type['ext_name']] = $type['title'];
    }
    $javascript['settings']['data'][] = array(
      'ding_availability_type_mapping' => $types,
      'ding_availability_type_strings' => array(
        // For some reason the Drupal.t() doesn't get picked up from
        // ding_availability_labels.js. The reason might be that we're loading
        // it dynamically. So pass the strings from here and use formatString in
        // the JS.
        'available' => t('@type can be borrowed'),
        'reservable' => t('@type can be reserved'),
      ),
    );
  }
}

/**
 * Implements hook_preprocess_html().
 */
function pratchett_preprocess_html(&$variables) {
  // Adding Viewport to HTML Header.
  $viewport = array(
    '#tag' => 'meta',
    '#attributes' => array(
      'name' => 'viewport',
      'content' => 'width=device-width, initial-scale=1, shrink-to-fit=no',
    ),
  );

  drupal_add_html_head($viewport, 'viewport');
}

/**
 * Implements hook_preprocess_node().
 */
function pratchett_preprocess_node(&$variables) {
  // Add tpl suggestions for node view modes on node type.
  if (isset($variables['view_mode'])) {
    $variables['theme_hook_suggestions'][] = 'node__' . 'view_mode__' . $variables['view_mode'];
    $variables['theme_hook_suggestions'][] = 'node__' . $variables['node']->type . '__view_mode__' . $variables['view_mode'];
  }
}

/**
 * Implements hook_ting_collection_view_alter().
 *
 * Suppress the type icon on the material in the ting_primary_object when the
 * collection contains more than one material. This removes the type-icon in
 * search results where the cover represents more than one material (likely of
 * different types).
 */
function pratchett_ting_collection_view_alter(&$build) {
  if (isset($build['ting_primary_object'])) {
    foreach (element_children($build['ting_primary_object']) as $key) {
      $collection = $build['ting_primary_object']['#object'];
      if (isset($build['ting_primary_object'][$key]['ting_cover'])) {
        // Signal to pratchett_ting_object_cover that this is a collection, so
        // it can build the correct link.
        $build['ting_primary_object'][$key]['ting_cover'][0]['#object']->reol_is_collection = TRUE;
        if (count($collection->entities) > 1) {
          $build['ting_primary_object'][$key]['ting_cover'][0]['#object']->reol_no_type_icons = TRUE;
        }
      }
    }
  }
}

/**
 * Implements theme_ting_object_cover().
 *
 * Default theme function implementation.
 */
function pratchett_ting_object_cover($variables) {
  // Start with the default rendering.
  $output = theme_ting_object_cover($variables);

  // Add type/quota icons.
  $ding_entity = $variables['object'];
  $icons = reol_frontend_ding_entity_icons($ding_entity);

  // Add link if the id is not to a fake material.
  $ding_entity_id = $ding_entity->ding_entity_id;
  if (!reol_base_fake_id($ding_entity_id) && !isset($ding_entity->reol_no_link)) {
    $path = isset($ding_entity->reol_is_collection) ? 'ting/collection/' : 'ting/object/';
    $output = l($output, $path . $ding_entity_id, array('html' => TRUE));
  }

  return '<div class="ting-cover-wrapper">' . $output . $icons . '</div>';
}

/**
 * Implements hook_preprocess_menu_link().
 *
 * Add destination to login link when using SSO authentication.
 */
function pratchett_preprocess_menu_link(&$variables) {
  if (module_exists('ding_adgangsplatformen')) {
    $element = &$variables['element'];
    if ($element['#href'] == DING_ADGANGSPLATFORMEN_LOGIN_URL) {
      $destination = drupal_get_destination();
      // Handle issues with lazy-pane and destination.
      if ($destination['destination'] === 'lazy-pane/ajax') {
        $path = $_GET['q'];
        $query = drupal_http_build_query(drupal_get_query_parameters());
        if ($query != '') {
          $path .= '?' . $query;
        }
        $destination = array('destination' => $path);
      }
      $element['#localized_options']['query'] = array(
        $destination,
      );
    }
  }
}
