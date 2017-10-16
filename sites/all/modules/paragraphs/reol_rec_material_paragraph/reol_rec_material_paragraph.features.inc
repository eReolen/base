<?php
/**
 * @file
 * reol_rec_material_paragraph.features.inc
 */

/**
 * Implements hook_paragraphs_info().
 */
function reol_rec_material_paragraph_paragraphs_info() {
  $items = array(
    'recommended_material' => array(
      'name' => 'Redaktøren anbefaler',
      'bundle' => 'recommended_material',
      'locked' => '1',
    ),
  );
  return $items;
}
