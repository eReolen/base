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
  $block->title = '';
  $block->content = '';
  $view_mode = 'teaser';

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'breol_subject')
    ->propertyCondition('status', 1)
    ->fieldOrderBy('field_weight', 'value')
    ->propertyOrderBy('title');

  $res = $query->execute();
  if (!empty($res['node'])) {
    $nodes = node_load_multiple(array_keys($res['node']));
    $content = node_view_multiple($nodes, $view_mode);

    $block->content = array(
      '#type' => 'ding_carousel',
      '#title' => '',
      '#items' => array_intersect_key($content['nodes'], array_flip(element_children($content['nodes']))),
    );

  }

  return $block;
}
