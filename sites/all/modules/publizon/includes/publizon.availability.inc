<?php
/**
 * @file
 * Availability-provider for Publizon.
 */

/**
 * Available items.
 * @TODO
 */
function publizon_availability_items($provider_ids) {
  $res = array();

  // For now, everything is reservable and available.
  foreach ($provider_ids as $id) {
    $res[$id] = array(
      'available' => FALSE,
      'reservable' => TRUE,
    );
  }
  return $res;
}

/**
 * Available holdings.
 * @TODO
 */
function publizon_availability_holdings($provider_ids) {
  // For now, everything is available everywhere.
  $res = publizon_availability_items($provider_ids);

  return $res;
}
