<?php
/**
 * @file
 * ereol_article.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ereol_article_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function ereol_article_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function ereol_article_image_default_styles() {
  $styles = array();

  // Exported image style: ereol_article_covers.
  $styles['ereol_article_covers'] = array(
    'label' => 'eReol article covers',
    'effects' => array(
      1 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => '',
          'height' => 390,
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: reol_article_teaser.
  $styles['reol_article_teaser'] = array(
    'label' => 'reol_article_teaser',
    'effects' => array(
      3 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => ' 232',
          'height' => 300,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: reol_article_teaser_background.
  $styles['reol_article_teaser_background'] = array(
    'label' => 'reol_article_teaser_background',
    'effects' => array(
      1 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => ' 565',
          'height' => 300,
        ),
        'weight' => 1,
      ),
      2 => array(
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
function ereol_article_node_info() {
  $items = array(
    'article' => array(
      'name' => t('Artikel'),
      'base' => 'node_content',
      'description' => t('Contains articles written for the frontpage, and for either ebook or audiobook site (or both)'),
      'has_title' => '1',
      'title_label' => t('Titel'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
