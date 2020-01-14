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

  // We wan't do disable caching on pages with loan buttons, i.e.
  // publication details pages and user pages.
  $arg = arg();
  $on_page_with_loan_button = FALSE
    // Ting details page.
    || (count($arg) > 1 && 'ting' === $arg[0] && in_array($arg[1], ['collection', 'object']))
    // User pages.
    || (count($arg) > 0 && 'user' === $arg[0]);

  $retailer_id = variable_get('publizon_default_retailer', '');
  $card_number = NULL;
  if ($on_page_with_loan_button) {
    try {
      global $user;

      // This will throw exception if not logged in.
      $creds = ding_user_get_creds();
      $retailer_id = publizon_get_retailer_id($user);
      $card_number = $creds['name'];
    }
    catch (DingProviderAuthException $e) {
      // If no user is logged in, try with the default retailer.
    }
  }

  // Whitelisted cards should not use cached responses.
  $use_cache = !in_array($card_number, variable_get('publizon_test_card_numbers', []));

  // Check cache as calls to publizon is expensive and this availability
  // function is called many time for each material displayed. When selecting
  // blue icons, for each ding entity button to figure out if it should be
  // displayed etc. so that's 5-8 time for every material show on the page.
  $results = array();
  $static_cache = &drupal_static(__FUNCTION__, []);
  foreach ($to_check as $isbn => $local_id) {
    if (!empty($static_cache[$local_id])) {
      $results[$local_id] = $static_cache[$local_id];
      unset($to_check[$isbn]);
    }
    else {
      if ($use_cache) {
        $cid = 'availability_' . $local_id;
        $cache = cache_get($cid);
        if ($cache && REQUEST_TIME < $cache->expire) {
          $results[$local_id] = $cache->data;
          unset($to_check[$isbn]);

          // Also store in static cache to speed up.
          $static_cache[$local_id] = $results[$local_id];
        }
      }
    }

    // Fast escape as all was fetched from cache.
    if (empty($to_check)) {
      return $results;
    }
  }

  $client = PublizonLoanClient::getClient();
  $loan_status_list = $client->getProductLoanStatusList($retailer_id, array_keys($to_check), $card_number);

  foreach ($loan_status_list as $loan_status) {
    $isbn = $loan_status->isbn;
    $status = $loan_status->loanStatus;

    $data = array(
      'available' => $status == 4 || $status == 3,
      'reservable' => $status == 5,
      // Always set the next 3 to FALSE to ensure that this is cacheable for
      // anonymous users. This information will be fetched from the logged
      // in user's cache.
      'loaned' => FALSE,
      'reserved' => FALSE,
      'bookmarked' => FALSE,
      'notloanable' => $status == 0,
    );

    $key = $to_check[$isbn];
    $results[$key] = $data;

    if ($use_cache) {
      // Store in cache.
      $static_cache[$key] = $data;

      // Store the loans into ding session cache.
      $cid = 'availability_' . $key;
      $expire = variable_get('publizon_availability_expire', 3600);
      cache_set($cid, $data, 'cache', REQUEST_TIME + $expire);
    }
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
