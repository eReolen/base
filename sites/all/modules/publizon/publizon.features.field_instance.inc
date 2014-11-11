<?php
/**
 * @file
 * publizon.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function publizon_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'profile2-provider_publizon-publizon_retailer_id'
  $field_instances['profile2-provider_publizon-field_publizon_retailer_id'] = array(
    'bundle' => 'provider_publizon',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'profile2',
    'field_name' => 'field_publizon_retailer_id',
    'label' => 'Retailer id',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 0,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Retailer id');

  return $field_instances;
}
