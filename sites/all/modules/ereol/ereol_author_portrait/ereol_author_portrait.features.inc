<?php
/**
 * @file
 * ereol_author_portrait.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ereol_author_portrait_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function ereol_author_portrait_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function ereol_author_portrait_image_default_styles() {
  $styles = array();

  // Exported image style: reol_author_portrait_full.
  $styles['reol_author_portrait_full'] = array(
    'label' => 'reol_author_portrait_full',
    'effects' => array(
      6 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 360,
          'height' => 400,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: reol_author_portrait_teaser.
  $styles['reol_author_portrait_teaser'] = array(
    'label' => 'reol_author_portrait_teaser',
    'effects' => array(
      7 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 550,
          'height' => 250,
        ),
        'weight' => 1,
      ),
      9 => array(
        'name' => 'image_desaturate',
        'data' => array(),
        'weight' => 2,
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function ereol_author_portrait_node_info() {
  $items = array(
    'author_portrait' => array(
      'name' => t('Om forfatteren'),
      'base' => 'node_content',
      'description' => t('Contains portraits of authors from Forfatterweb'),
      'has_title' => '1',
      'title_label' => t('Author name'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
