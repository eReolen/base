<?php
/**
 * @file
 * breol_frontend.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function breol_frontend_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "file_entity" && $api == "file_default_displays") {
    return array("version" => "1");
  }
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_image_default_styles().
 */
function breol_frontend_image_default_styles() {
  $styles = array();

  // Exported image style: breol_295_295.
  $styles['breol_295_295'] = array(
    'label' => 'breol_295_295',
    'effects' => array(
      3 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 295,
          'height' => 295,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: breol_590_295.
  $styles['breol_590_295'] = array(
    'label' => 'breol_590_295',
    'effects' => array(
      1 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 590,
          'height' => 295,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}
