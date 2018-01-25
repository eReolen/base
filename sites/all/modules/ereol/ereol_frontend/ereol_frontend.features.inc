<?php
/**
 * @file
 * ereol_frontend.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ereol_frontend_ctools_plugin_api($module = NULL, $api = NULL) {
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
function ereol_frontend_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function ereol_frontend_image_default_styles() {
  $styles = array();

  // Exported image style: ereol_cover_base.
  $styles['ereol_cover_base'] = array(
    'label' => 'eReol cover base',
    'effects' => array(
      1 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 260,
          'height' => 375,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}
