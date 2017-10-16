<?php
/**
 * @file
 * reol_rec_material_paragraph.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function reol_rec_material_paragraph_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_rec_material'.
  $field_bases['field_rec_material'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_rec_material',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'max_length' => 255,
      'profile2_private' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  // Exported field_base: 'field_rec_title'.
  $field_bases['field_rec_title'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_rec_title',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'max_length' => 40,
      'profile2_private' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  return $field_bases;
}
