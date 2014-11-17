<?php
/**
 * @file
 * publizon.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function publizon_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'publizon_retailer_id'
  $field_bases['field_publizon_retailer_id'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_publizon_retailer_id',
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
      'allowed_values_function' => 'publizon_get_libraries_list',
      'profile2_private' => 0,
    ),
    'translatable' => 0,
    'type' => 'list_text',
  );

  return $field_bases;
}