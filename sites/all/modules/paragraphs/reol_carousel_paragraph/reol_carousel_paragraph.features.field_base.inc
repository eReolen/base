<?php
/**
 * @file
 * reol_carousel_paragraph.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function reol_carousel_paragraph_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_carousel'.
  $field_bases['field_carousel'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_carousel',
    'indexes' => array(),
    'locked' => 0,
    'module' => 'reol_field_carousel',
    'settings' => array(
      'profile2_private' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'reol_field_carousel',
  );

  return $field_bases;
}
