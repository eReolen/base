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
  if ($node->type === 'breol_news') {
    // Get file url for cover image.
    $variables['file_uri'] = null;
    if (!empty($node->field_breol_cover_image[LANGUAGE_NONE][0])) {
      $file_uri = file_create_url($node->field_breol_cover_image[LANGUAGE_NONE][0]['uri']);
      $variables['file_uri'] = $file_uri;
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
