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
 *
 * @return array
 *   Array containing the loans for the user.
 */
function publizon_loan_list($account) {
  $result = array();

  // Throw exception if we're not logged in.
  $creds = ding_user_get_creds($account);

  $retailer_id = publizon_get_retailer_id($account);

  // Get list of loans from Publizon.
  $client = PublizonClient::getClient();
  $loans = $client->getLibraryUserOrderList($retailer_id, $creds['name']);

  module_load_include('client.inc', 'ting');
  foreach ($loans as $loan) {
    // Get the id from a search in Ting.
    $res = ting_do_search("term.identifier=" . $loan->isbn);
    list($id) = array_keys($res->collections);

    $result[$id] = new DingProviderLoan($id, array(
      'ding_entity_id' => $id,
      'loan_date' => date('Y-m-d', $loan->order_date),
      'expiry' => date('Y-m-d', $loan->expire_date),
      'renewable' => FALSE,
    ));
  }

  return $result;
}

/**
 * Renew loan.
 *
 * @TODO
 */
function publizon_loan_renew($account, $ids) {
  ding_user_get_creds($account);

  $result = array();

  return $result;
}

/**
 * Create a loan.
 *
 * @param array $account
 *   The account that tries to create a loan.
 * @param string $id
 *   The id of the ting object the user is trying to loan.
 */
function publizon_loan_create($account, $id) {
  // This will throw exception if not logged in.
  $creds = ding_user_get_creds($account);

  $retailer_id = publizon_get_retailer_id($account);

  // Get the object for extracting the ISBN.
  $ting_entity = ding_entity_load($id);
  list($isbn) = $ting_entity->getIsbn();

  $client = PublizonClient::getClient();
  // This will throw exception if loan does not go through.
  $client->createLoan($retailer_id, $creds['name'], $creds['pass'], $isbn);
}
