<?php
/**
 * @file
 * reol_user.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function reol_user_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_newsletter'
  $field_bases['field_newsletter'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_newsletter',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'mailchimp_lists',
    'settings' => array(
      'double_opt_in' => 0,
      'mc_list_id' => '4bc9190fe1',
      'profile2_private' => 0,
      'send_welcome' => 0,
      'unsubscribe_action' => 'remove',
    ),
    'translatable' => 0,
    'type' => 'mailchimp_lists_subscription',
  );

  return $field_bases;
}
