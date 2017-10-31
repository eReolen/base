<?php
/**
 * @file
 * reol_author_quote_paragraph.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function reol_author_quote_paragraph_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'paragraphs_item-author_quote-field_author_quote'.
  $field_instances['paragraphs_item-author_quote-field_author_quote'] = array(
    'bundle' => 'author_quote',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
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
    'field_name' => 'field_author_quote',
    'label' => 'Citat',
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

  // Exported field_instance:
  // 'paragraphs_item-author_quote-field_author_quote_material'.
  $field_instances['paragraphs_item-author_quote-field_author_quote_material'] = array(
    'bundle' => 'author_quote',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Kopier URLen på det materiale du vil referere til.',
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
    'field_name' => 'field_author_quote_material',
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
      'weight' => 2,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Citat');
  t('Kopier URLen på det materiale du vil referere til.');
  t('Materiale');

  return $field_instances;
}
