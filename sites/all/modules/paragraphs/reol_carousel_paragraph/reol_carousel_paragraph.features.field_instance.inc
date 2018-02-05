<?php
/**
 * @file
 * reol_carousel_paragraph.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function reol_carousel_paragraph_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance:
  // 'paragraphs_item-material_carousel-field_carousel'.
  $field_instances['paragraphs_item-material_carousel-field_carousel'] = array(
    'bundle' => 'material_carousel',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'reol_field_carousel',
        'settings' => array(
          'render_method' => 'material',
          'search_link' => 1,
        ),
        'type' => 'reol_field_carousel_notabs',
        'weight' => 0,
      ),
      'paragraphs_editor_preview' => array(
        'label' => 'hidden',
        'module' => 'reol_field_carousel',
        'settings' => array(
          'render_method' => 'cover',
          'search_link' => FALSE,
        ),
        'type' => 'reol_field_carousel_notabs',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'paragraphs_item',
    'field_name' => 'field_carousel',
    'label' => 'Karousel',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'reol_field_carousel',
      'settings' => array(),
      'type' => 'reol_field_carousel_widget',
      'weight' => 1,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Karousel');

  return $field_instances;
}
