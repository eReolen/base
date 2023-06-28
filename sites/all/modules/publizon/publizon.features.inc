<?php

/**
 * @file
 * publizon.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function publizon_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_default_profile2_type().
 */
function publizon_default_profile2_type() {
  $items = array();
  $items['provider_publizon'] = entity_import('profile2_type', '{
    "userCategory" : true,
    "userView" : true,
    "type" : "provider_publizon",
    "label" : "Publizon provider type",
    "weight" : "0",
    "data" : { "registration" : 0 }
  }');
  return $items;
}
