<?php
/**
 * @file
 * Ding bookmark provider for Publizon.
 */

/**
 * Get list of bookmarks.
 *
 * @param StdClass $account
 *   The account to get bookmarks for.
 *
 * @return array
 *   Array containing the bookmarks for the user.
 */
function publizon_bookmark_list($account) {
  return array();
}

/**
 * Create a bookmark for a title and user.
 *
 * @param StdClass $account
 *   The user to bookmark for.
 * @param string $local_id
 *   The local id to bookmark.
 */
function publizon_bookmark_create($account, $local_id) {

}

/**
 * Delete a bookmark for a title and user.
 *
 * @param StdClass $account
 *   The user to delete bookmark for.
 * @param string $local_id
 *   The local id to delete bookmark for.
 */
function publizon_bookmark_delete($account, $local_id) {

}
