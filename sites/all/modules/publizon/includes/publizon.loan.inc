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
 * @TODO
 */
function publizon_loan_create($account, $id) {
  return array(
    'queue_number' => 100,
  );
}
