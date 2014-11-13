<?php
/**
 * @file
 * Ding loan provider for Publizon.
 */

/**
 * Get list of loans.
 *
 * @TODO
 */
function publizon_loan_list($account) {
  // Throw exception if we're not logged in.
  ding_user_get_creds($account);

  $result = array();

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

  // Get the retailer id on the user.
  $profile = profile2_load_by_user($account, 'provider_publizon');
  $profile_wrapper = entity_metadata_wrapper('profile2', $profile);
  $retailer_id = $profile_wrapper->field_publizon_retailer_id->value();

  // Get the object for extracting the ISBN.
  $ting_entity = ding_entity_load($id);
  list($isbn) = $ting_entity->getIsbn();

  $client = PublizonClient::getClient();
  // This will throw exception if loan does not go through.
  $client->createLoan($retailer_id, $creds['name'], $creds['pass'], $isbn);
}
