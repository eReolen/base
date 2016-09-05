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
    'article' => array(
      'name' => t('Artikel'),
      'base' => 'node_content',
      'description' => t('Contains articles written for the frontpage, and for either ebook or audiobook site (or both)'),
      'has_title' => '1',
      'title_label' => t('Titel'),
      'help' => '',
    ),
    'author_portrait' => array(
      'name' => t('Om forfatteren'),
      'base' => 'node_content',
      'description' => t('Contains portraits of authors from Forfatterweb'),
      'has_title' => '1',
      'title_label' => t('Author name'),
      'help' => '',
    ),
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
