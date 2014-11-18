<?php
/**
 * @file
 * reol_loan.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function reol_loan_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'profile2-provider_publizon-field_email'
  $field_instances['profile2-provider_publizon-field_email'] = array(
    'bundle' => 'provider_publizon',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'email',
        'settings' => array(),
        'type' => 'email_default',
        'weight' => 2,
      ),
    ),
    'entity_type' => 'profile2',
    'field_name' => 'field_email',
    'label' => 'email',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'email',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'email_textfield',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'profile2-provider_publizon-field_phone'
  $field_instances['profile2-provider_publizon-field_phone'] = array(
    'bundle' => 'provider_publizon',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_integer',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'profile2',
    'field_name' => 'field_phone',
    'label' => 'Phone',
    'required' => 0,
    'settings' => array(
      'max' => 99999999,
      'min' => '00000001',
      'prefix' => '+45',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 1,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Phone');
  t('email');

  return $field_instances;
}
