<?php
/**
 * @file
 * breol_section.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function breol_section_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function breol_section_node_info() {
  $items = array(
    'breol_section' => array(
      'name' => t('Sektion'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('titel'),
      'help' => '',
    ),
  );
  return $items;
}
