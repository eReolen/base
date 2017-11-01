<?php
/**
 * @file
 * ereol_page.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function ereol_page_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_ereol_page_body'.
  $field_bases['field_ereol_page_body'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_ereol_page_body',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'profile2_private' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'text_long',
  );

  return $field_bases;
}
