<?php
/**
 * @file
 * breol_subject.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function breol_subject_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-subject-field_search_string'
  $field_instances['node-subject-field_search_string'] = array(
    'bundle' => 'subject',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 2,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_search_string',
    'label' => 'Søgestreng',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 32,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Søgestreng');

  return $field_instances;
}
