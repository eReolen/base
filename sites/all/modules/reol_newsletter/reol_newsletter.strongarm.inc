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
    'app_mode' => 1,
    'reol_description' => array(
      'value' => '<p>Tilmeld dig eReolens nyhedsbrev og modtag inspiration til læsning og lytning af e-bøger og lydbøger fra eReolen.</p><p>I nyhedsbrevet kan du lade dig inspirere af en præsentation af&nbsp;udvalgte&nbsp;og nye titler på eReolen, spændende forfatterskaber og&nbsp;serier samt følge med i nye tiltag&nbsp;og opdateringer.&nbsp;</p><p>Nyhedsbrevet bliver sendt ud en gang om månededen, og du kan altid afmelde dig igen, hvis du ikke ønsker at modtage flere nyhedsbreve.</p>',
      'format' => 'ding_wysiwyg',
    ),
    'SIGNUP_value' => 'APP',
  );
  $export['reol_newsletter_mailchimp_settings:2'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'reol_newsletter_mailchimp_settings:3';
  $strongarm->value = array(
    'app_mode' => 0,
    'reol_description' => array(
      'value' => '<p>Tilmeld dig eReolens nyhedsbrev og modtag inspiration til læsning og lytning af e-bøger og lydbøger fra eReolen.</p><p>I nyhedsbrevet kan du lade dig inspirere af en præsentation af&nbsp;udvalgte&nbsp;og nye titler på eReolen, spændende forfatterskaber og&nbsp;serier samt følge med i nye tiltag&nbsp;og opdateringer.&nbsp;</p><p>Nyhedsbrevet bliver sendt ud en gang om månededen, og du kan altid afmelde dig igen, hvis du ikke ønsker at modtage flere nyhedsbreve.</p>',
      'format' => 'ding_wysiwyg',
    ),
    'SIGNUP_value' => 'WEB',
  );
  $export['reol_newsletter_mailchimp_settings:3'] = $strongarm;

  return $export;
}
