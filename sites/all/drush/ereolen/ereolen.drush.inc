<?php

/**
 * @file
 * Drush commands for eReolen.
 */


/**
 * Implements hook_drush_command().
 */
function ereolen_drush_command() {
  $items['reol-cleanup'] = array(
    'description' => 'Clean up database for Probo.',
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
  );

  return $items;
}

/**
 * Command callback.
 */
function drush_ereolen_reol_cleanup() {
  drush_print('Please wait...');
  $fields = array_keys(field_info_instances('profile2', 'provider_publizon'));

  // Note which users we delete profiles for, so we can delete the users
  // themselves.
  $uids = db_select('profile', 'p')
        ->fields('p', array('uid'))
        ->condition('type', 'provider_publizon')
        ->execute()
        ->fetchCol();

  drush_print('Deleting profile field data.');
  foreach ($fields as $field) {
    drush_print($field . '...');
    db_query("DELETE FROM field_data_" . $field . " WHERE entity_type = 'profile2' AND bundle = 'provider_publizon'");
    db_query("DELETE FROM field_revision_" . $field  . " WHERE entity_type = 'profile2' AND bundle = 'provider_publizon'");
  }

  drush_print('Deleting profiles.');
  db_query("DELETE FROM profile WHERE type = 'provider_publizon'");

  drush_print('Deleting users.');
  $chunks = array_chunk($uids, 1000);
  $i = 0;
  foreach ($chunks as $chunk) {
    db_delete('users')
      ->condition('uid', $chunk, 'IN')
      ->execute();
    drush_print("\r" . $i += count($chunk), 0, NULL, FALSE);
  }
  drush_print();

  drush_print('Truncate watchdog.');
  db_query("TRUNCATE watchdog");

  drush_print('Flushing cache.');
  drupal_flush_all_caches();

  drush_print('Setting error_level to print out all notices.');
  variable_set('error_level', 2);
  drush_print('Done.');
}
