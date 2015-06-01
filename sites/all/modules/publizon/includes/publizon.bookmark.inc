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
  $result = array();

  // Throw exception if we're not logged in.
  $creds = ding_user_get_creds($account);

  $retailer_id = publizon_get_retailer_id($account);

  // Get checklist from Publizon.
  $client = PublizonChecklistClient::getClient();
  $checklist = $client->getChecklist($retailer_id, $creds['name']);

  $isbns = array();
  foreach ($checklist as $item) {
    $isbns[] = $item->isbn;
  }

  if ($isbns) {
    $mapping = reol_base_ding_entity_get_ids($isbns);
  }

  foreach ($checklist as $item) {
    // Title might not be found, do nothing.
    if (!isset($mapping[$item->isbn])) {
      continue;
    }
    $id = $mapping[$item->isbn];

    $result[] = $id;
  }

  return $result;
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
  // Throw exception if we're not logged in.
  $creds = ding_user_get_creds($account);

  $retailer_id = publizon_get_retailer_id($account);

  try {
    // Add to checklist in Publizon.
    $client = PublizonChecklistClient::getClient();
    $checklist = $client->addChecklistItem($retailer_id, $creds['name'], reol_base_get_isbn($local_id));
  }
  catch (PublizonException $e) {
    DingPublizonException::convert($e);
  }
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
  // Throw exception if we're not logged in.
  $creds = ding_user_get_creds($account);

  $retailer_id = publizon_get_retailer_id($account);

  try {
    // Delete from checklist in Publizon.
    $client = PublizonChecklistClient::getClient();
    $checklist = $client->deleteChecklistItem($retailer_id, $creds['name'], reol_base_get_isbn($local_id));
  }
  catch (PublizonException $e) {
    DingPublizonException::convert($e);
  }
}
