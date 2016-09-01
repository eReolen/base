<?php
/**
 * @file
 * breol_search_frontend.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function breol_search_frontend_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ding_facetbrowser_facets';
  $strongarm->value = array(
    0 => array(
      'name' => 'facet.type',
      'title' => 'Læs eller lyt',
      'sorting' => 'default',
      'weight' => '-10',
    ),
    1 => array(
      'name' => 'facet.subject',
      'title' => 'Emne',
      'sorting' => 'default',
      'weight' => '-9',
    ),
    2 => array(
      'name' => 'facet.audienceCategory',
      'title' => 'Alder',
      'sorting' => 'default',
      'weight' => '-8',
    ),
  );
  $export['ding_facetbrowser_facets'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ding_facetbrowser_number_of_terms';
  $strongarm->value = '10';
  $export['ding_facetbrowser_number_of_terms'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ding_facetbrowser_showcount';
  $strongarm->value = '3';
  $export['ding_facetbrowser_showcount'] = $strongarm;

  return $export;
}
