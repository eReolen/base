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
    'name' => 'breol_295_295',
    'label' => 'breol_295_295',
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
          'width' => 295,
          'height' => 295,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: breol_590_295.
  $styles['breol_590_295'] = array(
    'name' => 'breol_590_295',
    'label' => 'breol_590_295',
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
          'width' => 590,
          'height' => 295,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}
