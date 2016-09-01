<?php
/**
 * @file
 * breol_page.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function breol_page_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function breol_page_node_info() {
  $items = array(
    'breol_page' => array(
      'name' => t('Fast side'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('titel'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
