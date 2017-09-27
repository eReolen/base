<?php
/**
 * @file
 * reol_link_paragraph.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function reol_link_paragraph_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_link_color'.
  $field_bases['field_link_color'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_link_color',
    'indexes' => array(
      'rgb' => array(
        0 => 'rgb',
      ),
    ),
    'locked' => 0,
    'module' => 'color_field',
    'settings' => array(
      'default_colors' => '#797979,#e3e3e3,#d8133f,#3b73a0,#84ba76',
      'profile2_private' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'color_field_rgb',
  );

  return $field_bases;
}
