<?php
/**
 * @file
 * reol_newsletter.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function reol_newsletter_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'reol_newsletter_mailchimp_settings:1';
  $strongarm->value = array(
    'app_mode' => 0,
    'reol_description' => array(
      'value' => '<p>Tilmeld dig eReolens</p><h2>Nyhedsbrev</h2>',
      'format' => 'ding_wysiwyg',
    ),
  );
  $export['reol_newsletter_mailchimp_settings:1'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'reol_newsletter_mailchimp_settings:2';
  $strongarm->value = array(
    'signup_value' => 'APP',
    'app_mode' => 1,
  );
  $export['reol_newsletter_mailchimp_settings:2'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'reol_newsletter_mailchimp_settings:3';
  $strongarm->value = array(
    'signup_value' => 'WEB',
    'app_mode' => 0,
  );
  $export['reol_newsletter_mailchimp_settings:3'] = $strongarm;

  return $export;
}
