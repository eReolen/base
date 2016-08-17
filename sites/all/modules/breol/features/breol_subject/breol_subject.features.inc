<?php
/**
 * @file
 * breol_subject.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function breol_subject_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function breol_subject_node_info() {
  $items = array(
    'breol_subject' => array(
      'name' => t('Tema'),
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
