<?php
/**
 * @file
 * reol_author_portrait_paragraph.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function reol_author_portrait_paragraph_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_author_portrait'.
  $field_bases['field_author_portrait'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_author_portrait',
    'indexes' => array(
      'target_id' => array(
        0 => 'target_id',
      ),
    ),
    'locked' => 0,
    'module' => 'entityreference',
    'settings' => array(
      'handler' => 'base',
      'handler_settings' => array(
        'behaviors' => array(
          'views-select-list' => array(
            'status' => 0,
          ),
        ),
        'sort' => array(
          'direction' => 'ASC',
          'property' => 'title',
          'type' => 'property',
        ),
        'target_bundles' => array(
          'author_portrait' => 'author_portrait',
        ),
      ),
      'target_type' => 'node',
    ),
    'translatable' => 0,
    'type' => 'entityreference',
  );

  // Exported field_base: 'field_portrait_color'.
  $field_bases['field_portrait_color'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_portrait_color',
    'indexes' => array(
      'rgb' => array(
        0 => 'rgb',
      ),
    ),
    'locked' => 0,
    'module' => 'color_field',
    'settings' => array(
      'default_colors' => '#787878,#dcdcdc,#b81b40,#3b5998,#95b978,#70848e,#3c3c3c,#5f7f9f',
      'profile2_private' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'color_field_rgb',
  );

  return $field_bases;
}
