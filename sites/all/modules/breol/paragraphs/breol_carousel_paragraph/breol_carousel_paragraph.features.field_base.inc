<?php
/**
 * @file
 * breol_carousel_paragraph.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function breol_carousel_paragraph_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_material_carousel_color'.
  $field_bases['field_material_carousel_color'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_material_carousel_color',
    'indexes' => array(
      'rgb' => array(
        0 => 'rgb',
      ),
    ),
    'locked' => 0,
    'module' => 'color_field',
    'settings' => array(
      'default_colors' => '#7bb93a,#3174cf,#0aa9c1,#a729dc,#ff7800,#d50049',
      'profile2_private' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'color_field_rgb',
  );

  return $field_bases;
}
