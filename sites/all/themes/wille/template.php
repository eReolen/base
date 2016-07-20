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
  if ($node->type === 'breol_news' || $node->type === 'breol_section' || $node->type === 'breol_subject') {
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
    $variables['cover_background_color'] = 'transparant';
    if (!empty($variables['field_color'][0]['rgb'])) {
      $variables['cover_background_color'] = $variables['field_color'][0]['rgb'];
    }
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
