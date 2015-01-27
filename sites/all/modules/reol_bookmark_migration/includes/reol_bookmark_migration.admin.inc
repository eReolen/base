<?php
/**
 * @file
 * Defines the administration interface for bookmark migration.
 */

/**
 * Show status page for reol_bookmark_migration.
 */
function reol_bookmark_migration_status() {
  $users_migrated = reol_bookmark_migration_get_users_migrated();
  $users_total = reol_bookmark_migration_get_users_total();
  $isbns_migrated = reol_bookmark_migration_get_isbns_migrated();
  $isbns_total = reol_bookmark_migration_get_isbns_total();

  return theme('reol_bookmark_migration_status', array(
    'migrated_users_progress' => theme('progress_bar', array(
      'percent' => $users_total > 0 ? $users_migrated / $users_total * 100 : 0,
      'message' => t('@count of @total users have been migrated', array('@count' => $users_migrated, '@total' => $users_total)),
    )),
    'migrated_isbns_progress' => theme('progress_bar', array(
      'percent' => $isbns_total > 0 ? $isbns_migrated / $isbns_total * 100 : 0,
      'message' => t('@count of @total titles have been migrated', array('@count' => $isbns_migrated, '@total' => $isbns_total)),
    )),
  ));
}

/**
 * Get the number of users that have been migrated fully.
 *
 * @return int
 *   The count.
 */
function reol_bookmark_migration_get_users_migrated() {
  $q = db_select('reol_bookmark_migration_migrated_user', 'u');
  $q->addExpression('COUNT(uid)', 'count');
  $res = $q->execute()
    ->fetch();

  return $res->count;
}

/**
 * Get the number of users from old sites.
 *
 * @return int
 *   The count.
 */
function reol_bookmark_migration_get_users_total() {
  module_load_include('inc', 'reol_bookmark_migration', 'includes/reol_bookmark_migration.migration');
  $types = array(
    REOL_BOOKMARK_MIGRATION_EREOLEN,
    REOL_BOOKMARK_MIGRATION_NETLYDBOG,
  );

  $sum = 0;
  foreach ($types as $type) {
    if ($connection = reol_bookmark_migration_get_connection($type)) {
      $q = $connection->select('recall_list', 'l');
      $q->addExpression('COUNT(distinct(uid))', 'count');
      $res = $q->execute()
        ->fetch();

      $sum += $res->count;
    }
  }

  return $sum;
}

/**
 * Get the number of isbns that have been migrated fully.
 *
 * @return int
 *   The count.
 */
function reol_bookmark_migration_get_isbns_migrated() {
  $q = db_select('reol_bookmark_migration_migrated_isbn', 'i');
  $q->addExpression('COUNT(uid)', 'count');
  $res = $q->execute()
    ->fetch();

  return $res->count;
}

/**
 * Get the number of isbns from old sites.
 *
 * @return int
 *   The count.
 */
function reol_bookmark_migration_get_isbns_total() {
  module_load_include('inc', 'reol_bookmark_migration', 'includes/reol_bookmark_migration.migration');
  $types = array(
    REOL_BOOKMARK_MIGRATION_EREOLEN,
    REOL_BOOKMARK_MIGRATION_NETLYDBOG,
  );

  $sum = 0;
  foreach ($types as $type) {
    if ($connection = reol_bookmark_migration_get_connection($type)) {
      // TODO Could be more efficient.
      $q = $connection->select('recall_list', 'l');
      $q->addExpression('COUNT(DISTINCT(CONCAT(uid,isbn)))', 'count');
      $res = $q->execute()
        ->fetch();

      $sum += $res->count;
    }
  }

  return $sum;
}
