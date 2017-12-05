<?php
/**
 * @file
 * ereol_frontend.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function ereol_frontend_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ding_facetbrowser_facets';
  $strongarm->value = array(
    0 => array(
      'name' => 'facet.extraTitles',
      'title' => 'Ekstra lån',
      'sorting' => 'default',
      'weight' => '-10',
    ),
    1 => array(
      'name' => 'facet.type',
      'title' => 'Materialetype',
      'sorting' => 'default',
      'weight' => '-9',
    ),
    2 => array(
      'name' => 'facet.creator',
      'title' => 'Forfatter',
      'sorting' => 'default',
      'weight' => '-8',
    ),
    3 => array(
      'name' => 'facet.subject',
      'title' => 'Emne',
      'sorting' => 'default',
      'weight' => '-7',
    ),
    4 => array(
      'name' => 'facet.language',
      'title' => 'Sprog',
      'sorting' => 'default',
      'weight' => '-6',
    ),
    5 => array(
      'name' => 'facet.category',
      'title' => 'Målgruppe',
      'sorting' => 'default',
      'weight' => '-5',
    ),
    6 => array(
      'name' => 'facet.date',
      'title' => 'Årstal',
      'sorting' => 'numeric_reverse',
      'weight' => '-4',
    ),
    7 => array(
      'name' => 'facet.acSource',
      'title' => 'Kilde',
      'sorting' => 'default',
      'weight' => '10',
    ),
  );
  $export['ding_facetbrowser_facets'] = $strongarm;

  return $export;
}
