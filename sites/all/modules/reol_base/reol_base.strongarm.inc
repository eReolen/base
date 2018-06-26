<?php
/**
 * @file
 * reol_base.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function reol_base_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ting_cache_lifetime';
  $strongarm->value = '86400';
  $export['ting_cache_lifetime'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ting_online_types';
  $strongarm->value = array(
    'ebog' => 0,
    'lydbog (net)' => 0,
    'billedbog (net)' => 0,
    'tegneserie (net)' => 0,
    'e-node' => 0,
    'musik (net)' => 0,
  );
  $export['ting_online_types'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ting_openlist_wsdl';
  $strongarm->value = 'http://v2_test.openlist.server003.b14cms.dk/?wsdl';
  $export['ting_openlist_wsdl'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ting_reservable_sources';
  $strongarm->value = array(
    0 => 'bibliotekskatalog',
    1 => 'ereolen',
    2 => 'netlydbog',
  );
  $export['ting_reservable_sources'] = $strongarm;

  return $export;
}
