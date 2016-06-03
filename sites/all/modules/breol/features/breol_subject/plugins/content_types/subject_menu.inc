<?php

/**
 * @file
 * CTools content type for subject menu.
 */

$plugin = array(
  'title' => t('Subject menu'),
  'description' => t('The subject menu.'),
  'category' => 'eReolen for kids',
  'single' => TRUE,
  'content type' => 'subject_menu',
  'render callback' => 'subject_menu_content_type_render',

);

/**
 * Render callback.
 */
function subject_menu_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();
  $block->content = '';

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'breol_subject')
    ->propertyCondition('status', 1)
    ->propertyOrderBy('title', 'DESC');

  $res = $query->execute();
  if (!empty($res['node'])) {
    $nodes = node_load_multiple(array_keys($res['node']));
    $block->content = drupal_render(node_view_multiple($nodes));
  }

  return $block;
}
