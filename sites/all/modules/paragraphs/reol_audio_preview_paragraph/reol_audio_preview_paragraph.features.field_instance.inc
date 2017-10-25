<?php
/**
 * @file
 * reol_audio_preview_paragraph.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function reol_audio_preview_paragraph_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance:
  // 'paragraphs_item-audio_preview-field_preview_material'.
  $field_instances['paragraphs_item-audio_preview-field_preview_material'] = array(
    'bundle' => 'audio_preview',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Kopier URLen på den lydbog du vil lave lydprøve for.',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
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
    'field_name' => 'field_preview_material',
    'label' => 'Materiale',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 1,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Kopier URLen på den lydbog du vil lave lydprøve for.');
  t('Materiale');

  return $field_instances;
}
