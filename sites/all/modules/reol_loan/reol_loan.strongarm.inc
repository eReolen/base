<?php
/**
 * @file
 * reol_loan.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function reol_loan_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ting_reservable_types';
  $strongarm->value = array(
    0 => 'lydbog (net)',
    1 => 'ebog',
  );
  $export['ting_reservable_types'] = $strongarm;

  return $export;
}
