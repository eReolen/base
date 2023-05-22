<?php

/**
 * @file
 * publizon.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function publizon_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ting_reservable_types';
  $strongarm->value = array(
    0 => 'ebog',
    1 => 'lydbog (net)',
    2 => 'billedbog (net)',
    3 => 'tegneserie (net)',
    4 => 'graphic novel (net)',
    5 => 'musik (net)',
    6 => 'årbog (net)',
    7 => 'bog',
    8 => 'e-node',
  );
  $export['ting_reservable_types'] = $strongarm;

  return $export;
}
