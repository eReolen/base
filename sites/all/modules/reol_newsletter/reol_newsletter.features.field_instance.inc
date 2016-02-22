<?php
/**
 * @file
 * reol_newsletter.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function reol_newsletter_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'profile2-provider_publizon-field_newsletter'
  $field_instances['profile2-provider_publizon-field_newsletter'] = array(
    'bundle' => 'provider_publizon',
    'default_value' => array(
      0 => array(
        'subscribe' => 0,
        'is_default' => TRUE,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'mailchimp_lists',
        'settings' => array(
          'interest_groups' => array(),
          'show_interest_groups' => FALSE,
        ),
        'type' => 'mailchimp_lists_subscribe_default',
        'weight' => 3,
      ),
    ),
    'entity_type' => 'profile2',
    'field_name' => 'field_newsletter',
    'label' => 'Newsletter',
    'required' => 0,
    'settings' => array(
      'interest_groups_title' => 'Interest Groups',
      'mergefields' => array(
        'EMAIL' => '[profile2:field-email]',
        'SIGNUP' => 'www',
        'advanced' => 1,
      ),
      'options' => array(
        'interest_groups' => array(),
        'subscribe' => FALSE,
      ),
      'show_interest_groups' => 0,
      'unsubscribe_on_delete' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'mailchimp_lists',
      'settings' => array(),
      'type' => 'mailchimp_lists_select',
      'weight' => 31,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Newsletter');

  return $field_instances;
}
