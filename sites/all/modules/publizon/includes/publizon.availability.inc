<?php

/**
 * @file
 * Availability-provider for Publizon.
 */

/**
 * Available items.
 *
 * @param array $local_ids
 *   Array of local ids to check.
 *
 * @return array
 *   Result array containing the keys; available, reservable,
 *   loaned, reserved. Array is keyed by local id.
 */
function publizon_availability_items(array $local_ids) {
  global $user;

  // Ensure that ISBN numbers are local ids.
  $to_check = array();
  foreach ($local_ids as $local_id) {
    $isbn = reol_base_get_isbn($local_id);
    // If we do not have an ISBN number, we cannot get status.
    if (!$isbn) {
      continue;
    }

    $to_check[$isbn] = $local_id;
  }

  // Check cache as calls to publizon is expensive and this availability
  // function is called many time for each material displayed. When selecting
  // blue icons, for each ding entity button to figure out if it should be
  // displayed etc. so that's 5-8 time for every material show on the page.
  $results = array();
  $cache = &drupal_static(__FUNCTION__, array());
  foreach ($to_check as $isbn => $local_id) {
    if (!empty($cache[$local_id])) {
      $results[$local_id] = $cache[$local_id];
      unset($to_check[$isbn]);
    }
  }

  // Fast escape as all was fetched from cache.
  if (empty($to_check)) {
    return $results;
  }

  try {
    // This will throw exception if not logged in.
    $creds = ding_user_get_creds($user);
    $retailer_id = publizon_get_retailer_id($user);
    $card_number = $creds['name'];
  }
  catch (DingProviderAuthException $e) {
    // If no user is logged in, try with the default retailer.
    $retailer_id = variable_get('publizon_default_retailer', '');
    $card_number = NULL;
  }

  try {
    $client = PublizonLoanClient::getClient();
    $loanStatus = $client->getProductLoanStatusList($retailer_id, array_keys($to_check), $card_number);
    foreach ($loanStatus as $loanStatus) {
      $isbn = $loanStatus->isbn;
      $status = $loanStatus->loanStatus;

      $data = array(
        'available' => $status == 4 || $status == 3,
        'reservable' => $status == 5,
        'loaned' => $status == 1,
        'reserved' => $status == 2,
        'bookmarked' => $loanStatus->onChecklist,
        'notloanable' => $status == 0,
      );
      $key = $to_check[$isbn];
      $results[$key] = $data;

      // Store in cache
      $cache[$key] = $data;
    }
  }
  catch (PublizonException $e) {
    watchdog('publizon', 'Error getting availability from publizon, error message: @error', array('@error' => $e->getMessage()), WATCHDOG_ERROR);
  }

  return $results;
}

/**
 * Available holdings.
 */
function publizon_availability_holdings($provider_ids) {
  // For now, everything is available everywhere.
  $res = publizon_availability_items($provider_ids);

  return $res;
}
