<?php

/**
 * @file
 * Preprocess and Process Functions.
 */

/**
 * Implements hook_preprocess_html().
 */
function pratchett_preprocess_html(&$variables) {

  // Adding Viewport to HTML Header.
  $viewport = array(
    '#tag' => 'meta',
    '#attributes' => array(
      'name' => 'viewport',
      'content' => 'width=device-width, initial-scale=1, maximum-scale=1, user-scalable=no',
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
      if (count($collection->entities) > 1) {
        if (isset($build['ting_primary_object'][$key]['ting_cover'])) {
          $build['ting_primary_object'][$key]['ting_cover'][0]['#suppress_type_icon'] = TRUE;
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
  $icons = array();

  // Add type/quota icons.
  $ting_entity = $variables['object'];
  // Don't know if these should be shown yet.
  // if ($ting_entity->reply->on_quota) {
  //   $icons[] = 'quota';
  // }
  if (!isset($variables['elements']['#suppress_type_icon']) ||
    !$variables['elements']['#suppress_type_icon']) {
    if ($ting_entity && $ting_entity->reply && isset($ting_entity->reply->on_quota)) {
      $icons[] = reol_base_get_type_name($ting_entity->type);
    }
  }
  $icons = theme('reol_overlay_icons', array('icons' => $icons));

  // Add link if the id is not to a fake material.
  $ding_entity_id = $variables['elements']['#object']->ding_entity_id;
  if (!reol_base_fake_id($ding_entity_id)) {
    $output = l($output, 'ting/collection/' . $ding_entity_id, array('html' => TRUE));
  }

  return '<div class="ting-cover-wrapper">' . $output . $icons . '</div>';
}
