<?php
/**
 * @file
 * reol_frontend.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function reol_frontend_ctools_plugin_api($module = NULL, $api = NULL) {
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
    'name' => 'reol_review',
    'label' => 'reol_review',
    'effects' => array(
      1 => array(
        'label' => 'Skalér og beskær',
        'help' => 'Skalering og beskæring bevarer billedets højde-bredde-forhold og beskærer derefter den største dimension. Det er nyttigt til at generere kvadratiske thumbnails uden at forvrænge billedet.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 270,
          'height' => 400,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: reol_article_teaser.
  $styles['reol_article_teaser'] = array(
    'name' => 'reol_article_teaser',
    'label' => 'reol_article_teaser',
    'effects' => array(
      2 => array(
        'label' => 'Skalér og beskær',
        'help' => 'Skalering og beskæring bevarer billedets højde-bredde-forhold og beskærer derefter den største dimension. Det er nyttigt til at generere kvadratiske thumbnails uden at forvrænge billedet.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 270,
          'height' => 300,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: reol_article_teaser_background.
  $styles['reol_article_teaser_background'] = array(
    'name' => 'reol_article_teaser_background',
    'label' => 'reol_article_teaser_background',
    'effects' => array(
      3 => array(
        'label' => 'Skalér og beskær',
        'help' => 'Skalering og beskæring bevarer billedets højde-bredde-forhold og beskærer derefter den største dimension. Det er nyttigt til at generere kvadratiske thumbnails uden at forvrænge billedet.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 560,
          'height' => 300,
        ),
        'weight' => 1,
      ),
      5 => array(
        'label' => 'Afmæt',
        'help' => 'Afmæt konverterer et billede til gråtoner.',
        'effect callback' => 'image_desaturate_effect',
        'dimensions passthrough' => TRUE,
        'module' => 'image',
        'name' => 'image_desaturate',
        'data' => array(),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: reol_author_portrait_full.
  $styles['reol_author_portrait_full'] = array(
    'name' => 'reol_author_portrait_full',
    'label' => 'reol_author_portrait_full',
    'effects' => array(
      6 => array(
        'label' => 'Skalér og beskær',
        'help' => 'Skalering og beskæring bevarer billedets højde-bredde-forhold og beskærer derefter den største dimension. Det er nyttigt til at generere kvadratiske thumbnails uden at forvrænge billedet.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
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
    'name' => 'reol_author_portrait_teaser',
    'label' => 'reol_author_portrait_teaser',
    'effects' => array(
      7 => array(
        'label' => 'Skalér og beskær',
        'help' => 'Skalering og beskæring bevarer billedets højde-bredde-forhold og beskærer derefter den største dimension. Det er nyttigt til at generere kvadratiske thumbnails uden at forvrænge billedet.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 550,
          'height' => 250,
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
      'name' => t('Article'),
      'base' => 'node_content',
      'description' => t('Contains articles written for the frontpage, and for either ebook or audiobook site (or both)'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'author_portait' => array(
      'name' => t('Author portait'),
      'base' => 'node_content',
      'description' => t('Contains portraits of authors from Forfatterweb'),
      'has_title' => '1',
      'title_label' => t('Author name'),
      'help' => '',
    ),
  );
  return $items;
}
