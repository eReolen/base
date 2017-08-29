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
