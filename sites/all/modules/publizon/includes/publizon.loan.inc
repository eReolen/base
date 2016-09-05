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

  $result = &drupal_static(__FUNCTION__, array());
  if (!$result || $reset) {
    $retailer_id = publizon_get_retailer_id($account);

    // Get list of loans from Publizon.
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

      $result[$id] = new DingProviderLoan($id, array(
                       'ding_entity_id' => $id,
                       'loan_date' => date('Y-m-d H:i:s', $loan->order_date),
                       'expiry' => date('Y-m-d H:i:s', $loan->expire_date),
                       'renewable' => FALSE,
                       'display_name' => $loan->title,
                     ));

      $result[$id]->publizon_type = reol_base_get_ting_type(reol_base_get_type_from_format($loan->format));
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
    module_invoke_all('publizon_loan', $account, $creds['name'], $isbn, $retailer_id);
  }
  catch (PublizonException $e) {
    PublizonDingProviderException::convert($e);
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

/**
 * Add a fake cover field to pseudo entities to get publizon covers shown.
 */
function publizon_loan_populate_pseudo_entity($ting_entity) {
  if (isset($ting_entity->ding_entity_id) &&
    preg_match('/^publizon:(.*)$/', $ting_entity->ding_entity_id, $matches)) {
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
