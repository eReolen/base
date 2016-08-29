<?php
/**
 * @file
 * breol_news.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function breol_news_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_breol_cover_image'.
  $field_bases['field_breol_cover_image'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_breol_cover_image',
    'indexes' => array(
      'fid' => array(
        0 => 'fid',
      ),
    ),
    'locked' => 0,
    'module' => 'image',
    'settings' => array(
      'default_image' => 0,
      'profile2_private' => FALSE,
      'uri_scheme' => 'public',
    ),
    'translatable' => 0,
    'type' => 'image',
  );

  // Exported field_base: 'field_carousels'.
  $field_bases['field_carousels'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_carousels',
    'indexes' => array(),
    'locked' => 0,
    'module' => 'reol_field_carousel',
    'settings' => array(
      'profile2_private' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'ting_search_carousel',
  );

  return $field_bases;
}
