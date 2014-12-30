<?php
/**
 * @file
 * This file contains functions that handles the migration of bookmarks.
 */

define('REOL_BOOKMARK_MIGRATION_EREOLEN', 1);
define('REOL_BOOKMARK_MIGRATION_NETLYDBOG', 2);

/**
 * Ensure that a user has been migrated. If not, migrate bookmarks.
 *
 * @param int $uid
 *   The user id of the user.
 * @param string $loaner_id
 *   The login in of the loaner.
 */
function reol_bookmark_migration_ensure_user($uid, $loaner_id) {
  // Do nothing if user has already been migrated.
  if (reol_bookmark_migration_user_is_migrated($uid)) {
    return;
  }

  // Perform migration.
  $user = user_load($uid);
  $success_1 = reol_bookmark_migration_migrate_user(REOL_BOOKMARK_MIGRATION_EREOLEN, $user, $loaner_id);
  $success_2 = reol_bookmark_migration_migrate_user(REOL_BOOKMARK_MIGRATION_NETLYDBOG, $user, $loaner_id);

  // Mark this user as migrated.
  if ($success_1 && $success_2) {
    reol_bookmark_migration_mark_user_as_migrated($uid);
  }
}

/**
 * Get the legacy uid for a user on the old site.
 *
 * @param int $type
 *   One of the constants above.
 * @param string $loaner_id
 *   The id of the loaner to get uid for.
 *
 * @return string
 *   The uid of the loaner or FALSE if user was not found in old system.
 */
function reol_bookmark_migration_get_legacy_uid($type, $loaner_id) {
  $connection = reol_bookmark_migration_get_connection($type);

  $secret_res = $connection->select('variable', 'v')
    ->fields('v', array('value'))
    ->condition('v.name', 'drupal_private_key')
    ->execute()
    ->fetch();

  $secret = unserialize($secret_res->value);

  $key = md5($secret . $loaner_id);

  // Get uid from Publizon user table on legacy.
  $uid_res = $connection->select('publizon_user', 'u')
    ->fields('u', array('uid'))
    ->condition('u.pid', $key)
    ->execute()
    ->fetch();

  if ($uid_res) {
    return $uid_res->uid;
  }

  return FALSE;
}

/**
 * Get the db connection for a specific type.
 *
 * @param int $type
 *   One of the constants above.
 *
 * @return DatabaseConnection
 *   The database connection for the legacy site database or FALSE on failure.
 */
function reol_bookmark_migration_get_connection($type) {
  switch ($type) {
    case REOL_BOOKMARK_MIGRATION_EREOLEN:
      return Database::getConnection('ereolen', 'legacy');

    case REOL_BOOKMARK_MIGRATION_NETLYDBOG:
      return Database::getConnection('netlydbog', 'legacy');
  }

  return FALSE;
}

/**
 * Mark a user as migrated.
 *
 * @param int $uid
 *   The user id of the user.
 */
function reol_bookmark_migration_mark_user_as_migrated($uid) {
  try {
    db_insert('reol_bookmark_migration_migrated_user')
      ->fields(array(
        'uid' => $uid,
      ))
      ->execute();
  }
  // Duplicate entry exception is ok.
  catch (PDOException $e) {
    // TODO Only supports MySQL.
    if ($e->getCode() != 23000) {
      throw $e;
    }
  }
}

/**
 * Check whether or not a user is already migrated.
 *
 * @param int $uid
 *   The id of the user to check.
 *
 * @return bool
 *   Whether or not user is migrated.
 */
function reol_bookmark_migration_user_is_migrated($uid) {
  $res = db_select('reol_bookmark_migration_migrated_user', 'u')
    ->fields('u')
    ->condition('uid', $uid)
    ->execute()
    ->fetch();

  return (bool) $res;
}

/**
 * Mark an isbn as migrated for the user.
 *
 * @param int $uid
 *   The user id of the user that has this on bookmarks.
 * @param int $isbn
 *   The isbn of the book.
 */
function reol_bookmark_migration_mark_isbn_as_migrated($uid, $isbn) {
  try {
    db_insert('reol_bookmark_migration_migrated_isbn')
      ->fields(array(
        'uid' => $uid,
        'isbn' => $isbn,
      ))
      ->execute();
  }
  // Duplicate entry exception is ok.
  catch (PDOException $e) {
    // TODO Only supports MySQL.
    if ($e->getCode() != 23000) {
      throw $e;
    }
  }
}

/**
 * Check whether or not an isbn for a user is already migrated.
 *
 * @param int $uid
 *   The id of the user to check.
 * @param int $isbn
 *   The isbn to check.
 *
 * @return bool
 *   Whether or not isbn is migrated.
 */
function reol_bookmark_migration_isbn_is_migrated($uid, $isbn) {
  $res = db_select('reol_bookmark_migration_migrated_isbn', 'i')
    ->fields('i')
    ->condition('uid', $uid)
    ->condition('isbn', $isbn)
    ->execute()
    ->fetch();

  return (bool) $res;
}

/**
 * Migrate a users bookmarks.
 *
 * @param int $type
 *   The type to migrate. One of the constants above.
 * @param string $loaner_id
 *   The id of the loaner, used to log in to Publizon.
 *
 * @return bool
 *   Whether or not all bookmarks where migrated.
 */
function reol_bookmark_migration_migrate_user($type, $user, $loaner_id) {
  $success = TRUE;
  // Get id in publizon_user table.
  if ($legacy_uid = reol_bookmark_migration_get_legacy_uid($type, $loaner_id)) {
    $bookmarks = reol_bookmark_migration_get_bookmarks($type, $legacy_uid);

    foreach ($bookmarks as $bookmark) {
      try {
        if (!reol_bookmark_migration_isbn_is_migrated($user->uid, $bookmark)) {
          ding_provider_invoke('bookmark', 'create_internal', $user, $bookmark, $loaner_id);

          // Mark isbn as migrated.
          reol_bookmark_migration_mark_isbn_as_migrated($user->uid, $bookmark);
        }
      }
      catch (DingPublizonException $e) {
        // For now, duplicate in bookmarks will result in error 0,
        // duplicates are ok.
        if ($e->getCode() == 0) {
          // Mark isbn as migrated.
          reol_bookmark_migration_mark_isbn_as_migrated($user->uid, $bookmark);
        }
        else {
          $success = FALSE;
        }
      }
    }
  }
  return $success;
}

/**
 * Get list of bookmarks for a legacy user.
 *
 * @param int $type
 *   The type to get bookmarks for. One of the constants above.
 * @param int $legacy_uid
 *   The user id of the user on the old sites.
 */
function reol_bookmark_migration_get_bookmarks($type, $legacy_uid) {
  $connection = reol_bookmark_migration_get_connection($type);

  $bookmark_res = $connection->select('recall_list', 'b')
    ->fields('b', array('isbn'))
    ->condition('b.uid', $legacy_uid)
    ->execute()
    ->fetchAll();

  // Return array of isbns, where duplicates have been removed.
  return array_unique(array_map(function($elem) {
    return $elem->isbn;
  }, $bookmark_res));
}
