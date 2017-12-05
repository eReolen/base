<?php
/**
 * @file
 * ereol_page.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ereol_page_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function ereol_page_node_info() {
  $items = array(
    'ereol_page' => array(
      'name' => t('Fast side'),
      'base' => 'node_content',
      'description' => t('En fast indholds side.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
