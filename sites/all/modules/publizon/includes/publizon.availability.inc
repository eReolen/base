<?php
/**
 * @file
 * Availability-provider for Publizon.
 */

/**
 * Available items.
 *
 * @TODO
 *
 * @param array $local_ids
 *   Array of local ids to check.
 *
 * @return array
 *   Result array containing the keys; available, reservable,
 *   loaned, reserved. Array is keyed by local id.
 */
function publizon_availability_items($local_ids) {
  global $user;

  $to_check = array();
  foreach ($local_ids as $local_id) {
    $isbn = reol_base_get_isbn($local_id);
    // If we do not have an ISBN number, we cannot get status.
    if (!$isbn) {
      continue;
    }

    $to_check[$isbn] = $local_id;
  }

  try {
    // This will throw exception if not logged in.
    $creds = ding_user_get_creds($user);
    $retailer_id = publizon_get_retailer_id($user);
    $card_number = $creds['name'];
  }
  // If no user is logged in, try with the default retailer.
  catch (DingProviderAuthException $e) {
    $retailer_id = variable_get('publizon_default_retailer', '');
    $card_number = NULL;
  }

  try {
    $client = PublizonLoanClient::getClient();
    $results = $client->getProductLoanStatusList($retailer_id, array_keys($to_check), $card_number);
    $return = array();
    foreach ($results as $result) {
      $isbn = $result->isbn;
      $status = $result->loanStatus;

      $return[$to_check[$isbn]] = array(
        'available' => $status == 4 || $status == 3,
        'reservable' => $status == 5,
        'loaned' => $status == 1,
        'reserved' => $status == 2,
        'bookmarked' => $result->onChecklist,
        'notloanable' => $status == 0,
      );
    }
    return $return;
  }
  catch (PublizonException $e) {
    watchdog('publizon', 'Error getting availability from publizon, error message: @error', array('@error' => $e->getMessage()), WATCHDOG_ERROR);
    $return = array();
  }
}

/**
 * Available holdings.
 * @TODO
 */
function publizon_availability_holdings($provider_ids) {
  // For now, everything is available everywhere.
  $res = publizon_availability_items($provider_ids);

  return $res;
}
