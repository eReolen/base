<?php
/**
 * @file
 * ereol_page.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function ereol_page_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-ereol_page-field_ereol_page_body'.
  $field_instances['node-ereol_page-field_ereol_page_body'] = array(
    'bundle' => 'ereol_page',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_ereol_page_body',
    'label' => 'Body',
    'required' => 0,
    'settings' => array(
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 20,
      ),
      'type' => 'text_textarea',
      'weight' => 2,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Body');

  return $field_instances;
}
