<?php
/**
 * @file
 * breol_video.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function breol_video_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_breol_video'.
  $field_bases['field_breol_video'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_breol_video',
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

  return $field_bases;
}
