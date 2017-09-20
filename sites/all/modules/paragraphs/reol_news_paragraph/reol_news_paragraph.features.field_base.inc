<?php

/**
 * @file
 * reol_news_paragraph.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function reol_news_paragraph_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_carousel_count'.
  $field_bases['field_carousel_count'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_carousel_count',
    'indexes' => array(),
    'locked' => 0,
    'module' => 'number',
    'settings' => array(
      'profile2_private' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'number_integer',
  );

  return $field_bases;
}
