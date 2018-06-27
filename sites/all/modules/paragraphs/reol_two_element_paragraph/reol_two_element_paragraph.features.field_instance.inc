<?php
/**
 * @file
 * reol_two_element_paragraph.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function reol_two_element_paragraph_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance:
  // 'paragraphs_item-two_elements-field_two_elements_layout'.
  $field_instances['paragraphs_item-two_elements-field_two_elements_layout'] = array(
    'bundle' => 'two_elements',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 2,
      ),
      'paragraphs_editor_preview' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'paragraphs_item',
    'field_name' => 'field_two_elements_layout',
    'label' => 'Layout',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 3,
    ),
  );

  // Exported field_instance:
  // 'paragraphs_item-two_elements-field_two_elements_primary'.
  $field_instances['paragraphs_item-two_elements-field_two_elements_primary'] = array(
    'bundle' => 'two_elements',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'paragraphs',
        'settings' => array(
          'view_mode' => 'full',
        ),
        'type' => 'paragraphs_view',
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
    'field_name' => 'field_two_elements_primary',
    'label' => 'Primær',
    'required' => 0,
    'settings' => array(
      'add_mode' => 'select',
      'allowed_bundles' => array(
        'audio_preview' => -1,
        'material_carousel' => -1,
        'two_elements' => -1,
        'video' => 'video',
      ),
      'bundle_weights' => array(
        'audio_preview' => 2,
        'material_carousel' => 3,
        'two_elements' => 4,
        'video' => -8,
      ),
      'default_edit_mode' => 'open',
      'title' => 'Element',
      'title_multiple' => 'Elementer',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'paragraphs',
      'settings' => array(),
      'type' => 'paragraphs_embed',
      'weight' => 1,
    ),
  );

  // Exported field_instance:
  // 'paragraphs_item-two_elements-field_two_elements_secondary'.
  $field_instances['paragraphs_item-two_elements-field_two_elements_secondary'] = array(
    'bundle' => 'two_elements',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'paragraphs',
        'settings' => array(
          'view_mode' => 'full',
        ),
        'type' => 'paragraphs_view',
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
    'field_name' => 'field_two_elements_secondary',
    'label' => 'Sekundær',
    'required' => 0,
    'settings' => array(
      'add_mode' => 'select',
      'allowed_bundles' => array(
        'audio_preview' => 'audio_preview',
        'material_carousel' => -1,
        'two_elements' => -1,
      ),
      'bundle_weights' => array(
        'audio_preview' => 2,
        'material_carousel' => 3,
        'two_elements' => 4,
      ),
      'default_edit_mode' => 'open',
      'title' => 'Element',
      'title_multiple' => 'Elementer',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'paragraphs',
      'settings' => array(),
      'type' => 'paragraphs_embed',
      'weight' => 2,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Layout');
  t('Primær');
  t('Sekundær');

  return $field_instances;
}
