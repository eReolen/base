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
  $strongarm->name = 'autologout_enforce_admin';
  $strongarm->value = 0;
  $export['autologout_enforce_admin'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_inactivity_message';
  $strongarm->value = 'Af sikkerhedsmæssige årsager er du blevet logget ud, da du har været inaktiv de seneste 12 timer

';
  $export['autologout_inactivity_message'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_message';
  $strongarm->value = 'Af sikkerhedsmæssige årsager vil du automatisk blive logget ud om et øjeblik. Vil du fortsætte med at være logget ind?

';
  $export['autologout_message'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_no_dialog';
  $strongarm->value = 0;
  $export['autologout_no_dialog'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_padding';
  $strongarm->value = '60';
  $export['autologout_padding'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_redirect_url';
  $strongarm->value = '<front>';
  $export['autologout_redirect_url'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_role_1';
  $strongarm->value = 0;
  $export['autologout_role_1'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_role_10';
  $strongarm->value = 1;
  $export['autologout_role_10'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_role_10_timeout';
  $strongarm->value = '0';
  $export['autologout_role_10_timeout'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_role_1_timeout';
  $strongarm->value = '1800';
  $export['autologout_role_1_timeout'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_role_2';
  $strongarm->value = 0;
  $export['autologout_role_2'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_role_2_timeout';
  $strongarm->value = '1800';
  $export['autologout_role_2_timeout'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_role_3';
  $strongarm->value = 1;
  $export['autologout_role_3'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_role_3_timeout';
  $strongarm->value = '0';
  $export['autologout_role_3_timeout'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_role_4';
  $strongarm->value = 0;
  $export['autologout_role_4'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_role_4_timeout';
  $strongarm->value = '1800';
  $export['autologout_role_4_timeout'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_role_5';
  $strongarm->value = 0;
  $export['autologout_role_5'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_role_5_timeout';
  $strongarm->value = '1800';
  $export['autologout_role_5_timeout'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_role_6';
  $strongarm->value = 0;
  $export['autologout_role_6'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_role_6_timeout';
  $strongarm->value = '1800';
  $export['autologout_role_6_timeout'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_role_7';
  $strongarm->value = 0;
  $export['autologout_role_7'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_role_7_timeout';
  $strongarm->value = '1800';
  $export['autologout_role_7_timeout'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_role_8';
  $strongarm->value = 0;
  $export['autologout_role_8'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_role_8_timeout';
  $strongarm->value = '0';
  $export['autologout_role_8_timeout'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_role_9';
  $strongarm->value = 1;
  $export['autologout_role_9'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_role_9_timeout';
  $strongarm->value = '0';
  $export['autologout_role_9_timeout'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_role_logout';
  $strongarm->value = 1;
  $export['autologout_role_logout'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_use_alt_logout_method';
  $strongarm->value = 0;
  $export['autologout_use_alt_logout_method'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_use_watchdog';
  $strongarm->value = 0;
  $export['autologout_use_watchdog'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_whitelisted_ip_addresses';
  $strongarm->value = '';
  $export['autologout_whitelisted_ip_addresses'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'image_toolkit';
  $strongarm->value = 'tinypng';
  $export['image_toolkit'] = $strongarm;

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

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'tinypng_api_key';
  $strongarm->value = 'SET ME IN SETTINGS.PHP';
  $export['tinypng_api_key'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'tinypng_fallback_toolkit';
  $strongarm->value = 'imagemagick';
  $export['tinypng_fallback_toolkit'] = $strongarm;

  return $export;
}
