<?php
/**
 * @file
 * breol_carousel_paragraph.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function breol_carousel_paragraph_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance:
  // 'paragraphs_item-material_carousel-field_material_carousel_color'.
  $field_instances['paragraphs_item-material_carousel-field_material_carousel_color'] = array(
    'bundle' => 'material_carousel',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
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
    'field_name' => 'field_material_carousel_color',
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

  return $field_instances;
}
