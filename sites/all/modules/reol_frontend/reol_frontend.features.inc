<?php
/**
 * @file
 * reol_frontend.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function reol_frontend_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "file_entity" && $api == "file_default_displays") {
    return array("version" => "1");
  }
  if ($module == "menu_block" && $api == "menu_block") {
    return array("version" => "1");
  }
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function reol_frontend_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function reol_frontend_image_default_styles() {
  $styles = array();

  // Exported image style: reol_review.
  $styles['reol_review'] = array(
    'label' => 'reol_review',
    'effects' => array(
      1 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 270,
          'height' => 400,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function reol_frontend_node_info() {
  $items = array(
    'video' => array(
      'name' => t('Video'),
      'base' => 'node_content',
      'description' => t('Contains videos as shown on type frontpages.'),
      'has_title' => '1',
      'title_label' => t('Titel'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
