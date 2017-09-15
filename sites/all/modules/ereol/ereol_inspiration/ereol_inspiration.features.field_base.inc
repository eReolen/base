<?php
/**
 * @file
 * ereol_inspiration.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function ereol_inspiration_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_inspiration_paragraphs'.
  $field_bases['field_inspiration_paragraphs'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_inspiration_paragraphs',
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
