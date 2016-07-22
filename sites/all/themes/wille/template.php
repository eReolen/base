<?php

/**
 * @file
 * Preprocess and Process Functions.
 */

/**
 * Implements hook_preprocess_node().
 */
function wille_preprocess_node(&$variables, $hook) {

  // Add tpl suggestions for node view modes on node type.
  if (isset($variables['view_mode'])) {
    $variables['theme_hook_suggestions'][] = 'node__' . 'view_mode__' . $variables['view_mode'];
    $variables['theme_hook_suggestions'][] = 'node__' . $variables['node']->type . '__view_mode__' . $variables['view_mode'];
  }

  $node = $variables['node'];
  if ($node->type === 'breol_news' || $node->type === 'breol_section') {
    // Get file url for cover image.
    $variables['file_uri'] = null;
    if (!empty($node->field_breol_cover_image[LANGUAGE_NONE][0])) {
      $file_uri = file_create_url($node->field_breol_cover_image[LANGUAGE_NONE][0]['uri']);
      $variables['file_uri'] = $file_uri;
    }
  }

  // We know we always gonna use the slick library when the node type is
  // breol_subject.
  if ($node->type === 'breol_subject') {
    libraries_load('slick');
  }
}

/**
 * hook_preprocess_image().
 *
 * Remove Height and Width Inline Styles from Drupal Images.
 */
function wille_preprocess_image(&$variables) {
  foreach (array('width', 'height') as $key) {
    unset($variables[$key]);
  }
}

/**
 * Implements hook_preprocess_preprocess_material_item().
 */
function wille_preprocess_material_item(&$variables) {
  $element = $variables['element'];
  // TODO Can we rely on this?
  $ding_entity_id = $element['#cover']['#object']->ding_entity_id;
  $ting_entity = ding_entity_load($ding_entity_id);

  $add_classes = _wille_type_icon_classes(reol_base_get_type_name($ting_entity->type), $ting_entity->reply->on_quota);
  $variables['classes_array'] = array_merge($variables['classes_array'], $add_classes);
}


/**
 * Implements hook_preprocess_ting_object_cover().
 *
 * Adds type icon to ting object covers.
 */
function wille_preprocess_ting_object_cover(&$variables) {
  if (!isset($variables['elements']['#suppress_type_icon']) ||
    !$variables['elements']['#suppress_type_icon']) {
    $ting_entity = $variables['object'];
    if ($ting_entity && $ting_entity->reply) {
      $add_classes = _wille_type_icon_classes(reol_base_get_type_name($ting_entity->type), $ting_entity->reply->on_quota);
      $variables['classes'] = array_merge($variables['classes'], $add_classes);
    }
  }
}

/**
 * Return classes for type icon.
 *
 * @return array
 *   Classes as array.
 */
function _wille_type_icon_classes($type, $quota = NULL) {
  $classes = array(
    'type-icon',
    'type-icon-' . $type,
  );
  if (is_bool($quota)) {
    $classes[] = 'type-icon-' . ($quota ? 'quota' : 'noquota');
  }
  return $classes;
}
