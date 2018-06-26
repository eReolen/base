<?php
/**
 * @file
 * reol_two_element_paragraph.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function reol_two_element_paragraph_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_two_elements_layout'.
  $field_bases['field_two_elements_layout'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_two_elements_layout',
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        0 => 'Primær til venstre',
        1 => 'Primær til højre',
      ),
      'allowed_values_function' => '',
      'profile2_private' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'list_boolean',
  );

  // Exported field_base: 'field_two_elements_primary'.
  $field_bases['field_two_elements_primary'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_two_elements_primary',
    'indexes' => array(),
    'locked' => 0,
    'module' => 'paragraphs',
    'settings' => array(
      'profile2_private' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'paragraphs',
  );

  // Exported field_base: 'field_two_elements_secondary'.
  $field_bases['field_two_elements_secondary'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_two_elements_secondary',
    'indexes' => array(),
    'locked' => 0,
    'module' => 'paragraphs',
    'settings' => array(
      'profile2_private' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'paragraphs',
  );

  return $field_bases;
}
