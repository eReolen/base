<?php
/**
 * @file
 * breol_video.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function breol_video_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "file_entity" && $api == "file_default_displays") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function breol_video_node_info() {
  $items = array(
    'breol_video' => array(
      'name' => t('Video'),
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
