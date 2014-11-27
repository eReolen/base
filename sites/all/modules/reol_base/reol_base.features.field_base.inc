<?php
/**
 * @file
 * reol_base.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function reol_base_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'reol_entity_type'
  $field_bases['field_reol_entity_type'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_reol_entity_type',
    'foreign keys' => array(),
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(),
      'allowed_values_function' => 'reol_base_get_entity_types',
    ),
    'translatable' => 0,
    'type' => 'list_text',
  );

  return $field_bases;
}
