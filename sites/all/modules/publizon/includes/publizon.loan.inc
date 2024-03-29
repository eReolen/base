<?php

/**
 * @file
 * Ding loan provider for Publizon.
 */

/**
 * Get list of loans.
 *
 * @param object $account
 *   The account to get loan list for.
 * @param bool $reset
 *   Whether or not to force get.
 *
 * @return array
 *   Array containing the loans for the user.
 *
 * @throws DingProviderAuthException
 *   Is thrown if user is not logged in.
 */
function publizon_loan_list($account, $reset = FALSE) {
  $results = &drupal_static(__FUNCTION__, NULL);

  if (is_null($results) || $reset) {
    // Check if ding_session_cache is available.
    if (module_exists('ding_session_cache') && !$reset) {
      $results = ding_session_cache_get('publizon', 'loans', NULL);
    }

    // If both static cache and session cache failed, try reloading information
    // from publizon.
    if (is_null($results) || $reset) {
      $retailer_id = publizon_get_retailer_id($account);

      // Get list of loans from Publizon.
      $creds = ding_user_get_creds();
      $client = PublizonLoanClient::getClient();
      $loans = $client->getLibraryUserOrderList($retailer_id, $creds['name']);

      $isbns = array();
      foreach ($loans as $loan) {
        $isbns[] = $loan->isbn;
      }

      if ($isbns) {
        $mapping = reol_base_ding_entity_get_ids($isbns);
      }

      foreach ($loans as $loan) {
        // Title might not be found, use an fake ID.
        if (!isset($mapping[$loan->isbn])) {
          $id = 'publizon:' . $loan->isbn;
        }
        else {
          $id = $mapping[$loan->isbn];
        }

        $results[$id] = new DingProviderLoan($id, array(
          'ding_entity_id' => $id,
          'loan_date' => date('Y-m-d H:i:s', $loan->order_date),
          'expiry' => date('Y-m-d H:i:s', $loan->expire_date),
          'renewable' => FALSE,
          'display_name' => $loan->title,
        ));

        $results[$id]->publizon_type = reol_base_get_ting_type(reol_base_get_type_from_format($loan->format));
        $results[$id]->publizon_on_quota = $loan->on_quota;
      }

      // Store the loans into ding session cache.
      if (module_exists('ding_session_cache')) {
        ding_session_cache_set('publizon', 'loans', $results);
      }
    }
  }

  return is_null($results) ? array() : $results;
}

/**
 * Create a loan.
 *
 * @param object $account
 *   The account that tries to create a loan.
 * @param string $local_id
 *   The local id of the ting object the user is trying to loan.
 *
 * @throws DingProviderAuthException
 *   Is thrown if user is not logged in.
 * @throws PublizonDingProviderException
 */
function publizon_loan_create($account, $local_id) {
  $retailer_id = publizon_get_retailer_id($account);
  $isbn = reol_base_get_isbn($local_id);

  try {
    // This will throw exception if not logged in.
    $creds = ding_user_get_creds();
    $user_data = publizon_get_user_data();

    $institution_id = NULL;
    if (function_exists('ding_unilogin_get_user_data')) {
      $unilogin_data = ding_unilogin_get_user_data();
      if (isset($unilogin_data['institutions'])
        && is_array($unilogin_data['institutions'])) {
        $institutions = $unilogin_data['institutions'];
        $institution = reset($institutions);
        if (NULL !== $institution) {
          $institution_id = $institution->instnr;
        }
      }
    }

    // The user may belong to an institution that has been removed from the
    // current institution list (session with old data is still alive).  Don't
    // allow creating a new loan in this case.
    if (NULL !== $institution_id
        && module_exists('ding_unilogin')
        && empty(ding_unilogin_filter_institutions([$institution_id]))) {
      throw new PublizonException('Invalid institution', 87);
    }

    $client = PublizonLoanClient::getClient();

    // Check if institution tags exists (to prevent users already logged-in
    // missing this object. We have this extra check).
    $tags = $user_data['tags'] ?? array();

    // This will throw exception if loan does not go through.
    $client->createLoan($retailer_id, $creds['name'], $creds['pass'], $isbn, $institution_id, $tags);
    module_invoke_all('publizon_loan', $account, $creds['name'], $isbn, $retailer_id);
  }
  catch (PublizonException $e) {
    PublizonDingProviderException::convert($e);
  }

  // Clear ding session cache.
  if (module_exists('ding_session_cache')) {
    ding_session_cache_clear('publizon', 'loans');
    ding_session_cache_clear('ding_loan', 'list');
  }
}

/**
 * Get a single loan.
 *
 * @param object $account
 *   The account to get loan for.
 * @param string $local_id
 *   The local id to get loan for.
 *
 * @return array
 *   Array containing order-id and retailer-id.
 *
 * @throws DingProviderAuthException
 *   Is thrown if user is not logged in.
 */
function publizon_loan_get($account, $local_id) {
  // This will throw exception if not logged in.
  $creds = ding_user_get_creds();

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

/**
 * Add a fake cover field to pseudo entities to get publizon covers shown.
 */
function publizon_loan_populate_pseudo_entity($ting_entity) {
  if (isset($ting_entity->ding_entity_id) && preg_match('/^publizon:(.*)$/', $ting_entity->ding_entity_id, $matches)) {
    $ting_entity->ting_cover = array(
      LANGUAGE_NONE => array(
        0 => array(
          'local_id' => $matches[1],
        ),
      ),
    );
  }

  return $ting_entity;
}
