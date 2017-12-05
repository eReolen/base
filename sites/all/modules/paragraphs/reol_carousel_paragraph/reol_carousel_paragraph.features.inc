<?php
/**
 * @file
 * reol_carousel_paragraph.features.inc
 */

/**
 * Implements hook_paragraphs_info().
 */
function reol_carousel_paragraph_paragraphs_info() {
  $items = array(
    'material_carousel' => array(
      'name' => 'Materiale karrusel',
      'bundle' => 'material_carousel',
      'locked' => '1',
    ),
  );
  return $items;
}
