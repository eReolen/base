<?php
/**
 * @file
 * Ding loan provider for Publizon.
 */

/**
 * Get list of loans.
 *
 * @param StdClass $account
 *   The account to get loan list for.
 * @param bool $reset
 *   Whether or not to force get.
 *
 * @return array
 *   Array containing the loans for the user.
 */
function publizon_loan_list($account, $reset = FALSE) {
  // Throw exception if we're not logged in.
  $creds = ding_user_get_creds($account);

  $results = &drupal_static(__FUNCTION__, FALSE);
  if (!$results || $reset) {
    // Check if ding_session_cache is available.
    if (module_exists('ding_session_cache') && !$reset) {
      $results = ding_session_cache_get('publizon', 'loans');
    }

    // If no caches have data, get from Publizon.
    if (empty($results) || $reset) {
      $retailer_id = publizon_get_retailer_id($account);

      // Get list of loans from Publizon.
      $client = PublizonLoanClient::getClient();
      $loans = $client->getLibraryUserOrderList($retailer_id, $creds['name']);

      foreach ($loans as $loan) {
        $id = reol_base_ding_entity_get_id($loan->isbn);

        // Title might not be found, do nothing.
        if (!$id) {
          continue;
        }

        $result[$id] = new DingProviderLoan($id, array(
          'ding_entity_id' => $id,
          'loan_date' => date('Y-m-d H:i:s', $loan->order_date),
          'expiry' => date('Y-m-d H:i:s', $loan->expire_date),
          'renewable' => FALSE,
        ));
      }

      // Save into ding session cache.
      if (module_exists('ding_session_cache')) {
        ding_session_cache_set('publizon', 'loans', $results);
      }
    }

  return $result;
}

/**
 * Create a loan.
 *
 * @param array $account
 *   The account that tries to create a loan.
 * @param string $local_id
 *   The local id of the ting object the user is trying to loan.
 */
function publizon_loan_create($account, $local_id) {
  // This will throw exception if not logged in.
  $creds = ding_user_get_creds($account);

  $retailer_id = publizon_get_retailer_id($account);

  $isbn = reol_base_get_isbn($local_id);

  try {
    $client = PublizonLoanClient::getClient();
    // This will throw exception if loan does not go through.
    $client->createLoan($retailer_id, $creds['name'], $creds['pass'], $isbn);
  }
  catch (PublizonException $e) {
    DingPublizonException::convert($e);
  }

  // Clear ding session cache.
  if (module_exists('ding_session_cache')) {
    ding_session_cache_clear('publizon', 'loans');
  }

}

/**
 * Get a single loan.
 *
 * @TODO Should we cache this, or is it okay not to?
 *
 * @param StdClass $account
 *   The account to get loan for.
 * @param string $local_id
 *   The local id to get loan for.
 *
 * @return array
 *   Array containing order-id and retailer-id.
 */
function publizon_loan_get($account, $local_id) {
  // This will throw exception if not logged in.
  $creds = ding_user_get_creds($account);

  $retailer_id = publizon_get_retailer_id($account);

  $isbn = reol_base_get_isbn($local_id);

  $client = PublizonLoanClient::getClient();
  // This will throw exception if loan does not go through.
  $result = $client->getLibraryUserOrder($retailer_id, $creds['name'], $isbn);

  return $result ? array(
    'internal_order_number' => $result->internal_order_number,
    'retailer_order_number' => $result->retailer_order_number,
  ) : array();
}
