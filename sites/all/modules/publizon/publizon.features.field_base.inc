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

  // Exported field_base: 'field_email'.
  $field_bases['field_email'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_email',
    'indexes' => array(),
    'locked' => 0,
    'module' => 'email',
    'settings' => array(
      'profile2_private' => 1,
    ),
    'translatable' => 0,
    'type' => 'email',
  );

  // Exported field_base: 'field_phone'.
  $field_bases['field_phone'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_phone',
    'indexes' => array(),
    'locked' => 0,
    'module' => 'number',
    'settings' => array(
      'profile2_private' => 1,
    ),
    'translatable' => 0,
    'type' => 'number_integer',
  );

  // Exported field_base: 'field_publizon_retailer_id'.
  $field_bases['field_publizon_retailer_id'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_publizon_retailer_id',
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
