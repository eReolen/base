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
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 2,
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

  // Exported field_instance: 'node-ereol_page-field_ereol_page_files'.
  $field_instances['node-ereol_page-field_ereol_page_files'] = array(
    'bundle' => 'ereol_page',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'file',
        'settings' => array(),
        'type' => 'file_default',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_ereol_page_files',
    'label' => 'Vedhæft filer',
    'required' => 0,
    'settings' => array(
      'description_field' => 1,
      'file_directory' => 'page',
      'file_extensions' => 'jpg jpeg gif png txt doc docx xls xlsx pdf ppt pptx pps odt ods odp',
      'max_filesize' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'file',
      'settings' => array(
        'progress_indicator' => 'throbber',
      ),
      'type' => 'file_generic',
      'weight' => 5,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Body');
  t('Vedhæft filer');

  return $field_instances;
}
