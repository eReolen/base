<?php
/**
 * @file
 * Ding reservation provider for Publizon.
 */

/**
 * Get list of reservations.
 *
 * @TODO
 */
function publizon_reservation_list($account) {
  // Throw exception if we're not logged in.
  ding_user_get_creds($account);
  $result = array();

  return $result;
}

/**
 * Create reservation.
 *
 * @TODO
 */
function publizon_reservation_create($account, $id, $options) {
  return array();
}

/**
 * Delete reservation.
 *
 * @TODO
 */
function publizon_reservation_delete($account, $id) {
  // Throw exception if we're not logged in.
  ding_user_get_creds($account);
}
