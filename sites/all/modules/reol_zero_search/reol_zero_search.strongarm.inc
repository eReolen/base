<?php
/**
 * @file
 * reol_zero_search.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function reol_zero_search_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'reol_zero_search_carousel_description_toggle';
  $strongarm->value = 1;
  $export['reol_zero_search_carousel_description_toggle'] = $strongarm;

  return $export;
}
