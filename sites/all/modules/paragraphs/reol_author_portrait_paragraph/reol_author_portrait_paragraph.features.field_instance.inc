<?php
/**
 * @file
 * reol_author_portrait_paragraph.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function reol_author_portrait_paragraph_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance:
  // 'paragraphs_item-author_portrait-field_author_portrait'.
  $field_instances['paragraphs_item-author_portrait-field_author_portrait'] = array(
    'bundle' => 'author_portrait',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 0,
      ),
      'paragraphs_editor_preview' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'paragraphs_item',
    'field_name' => 'field_author_portrait',
    'label' => 'Forfatterportræt',
    'required' => FALSE,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'entityreference',
      'settings' => array(
        'match_operator' => 'CONTAINS',
        'path' => '',
        'size' => 60,
      ),
      'type' => 'entityreference_autocomplete',
      'weight' => 1,
    ),
  );

  // Exported field_instance:
  // 'paragraphs_item-author_portrait-field_portrait_color'.
  $field_instances['paragraphs_item-author_portrait-field_portrait_color'] = array(
    'bundle' => 'author_portrait',
    'default_value' => array(
      0 => array(
        'rgb' => '#787878',
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'color_field',
        'settings' => array(),
        'type' => 'color_field_default_formatter',
        'weight' => 1,
      ),
      'paragraphs_editor_preview' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'paragraphs_item',
    'field_name' => 'field_portrait_color',
    'label' => 'Farve',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'color_field',
      'settings' => array(),
      'type' => 'color_field_default_widget',
      'weight' => 2,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Farve');
  t('Forfatterportræt');

  return $field_instances;
}
