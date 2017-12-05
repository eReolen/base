<?php

/**
 * @file
 * Publizon debt provider for Ding.
 */

/**
 * Provide list of DingProviderDebt objects for a user.
 *
 * @param StdClass $account
 *   User object to provide debts for.
 * @param bool $reset
 *   Reset static cache if TRUE else get debts from cache.
 *
 * @return array
 *   DingProviderDebt objects in array, keyed by debt ID.
 */
function publizon_debt_list($account, $reset = FALSE) {
  return array();
}

/**
 * Mark debts as paid.
 *
 * @param float $amount
 *   The total amount paid.
 * @param array $debt_ids
 *   IDs of the paid debts.
 * @param mixed $order_id
 *   Order ID of the payment transaction, to be recorded in the backend system.
 *
 * @return array
 *   Array from publizon with the results.
 */
function publizon_debt_payment_received($amount, $debt_ids = array(), $order_id = NULL) {
  return array();
}

/**
 * Translate publizon debt types into an human readable string in english.
 *
 * @param string $debt_type
 *   The publizon debt type.
 *
 * @return string
 *   English translation of the debt type. It has been
 */
function publizon_debt_translate_debt_type($debt_type) {
  return '';
}
