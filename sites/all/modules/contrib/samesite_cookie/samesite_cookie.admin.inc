<?php

/**
 * @file
 * SameSite cookie attributes admin pages.
 */

/**
 * Form builder function for SameSite cookie config settings.
 */
function samesite_cookie_admin_settings($form) {
  $form['samesite_cookie'] = array(
    '#type' => 'container',
    '#tree' => FALSE,
  );
  $form['samesite_cookie']['heading'] = array(
    '#type' => 'item',
    '#description' => t('The SameSite cookie attribute allows you to control how requests from external resources behave.') . "<br>\n" . t('For more information about the values and implications, you can refer to this !link.', array('!link' => l('SameSite cookies documentation on MDN', 'https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Set-Cookie/SameSite'))),
  );
  $samesite_cookie_override_default = variable_get('samesite_cookie_override_value', 'None');
  $form['samesite_cookie']['samesite_cookie_override_value'] = array(
    '#type' => 'radios',
    '#title' => t('SameSite attribute value to send.'),
    '#description' => t('Choose the SameSite attribute value that Drupal should send to web browsers.'),
    '#options' => array(
      '' => '(no override)',
      'None' => 'None',
      'Lax' => 'Lax',
      'Strict' => 'Strict',
    ),
    '#default_value' => $samesite_cookie_override_default,
  );
  $form['samesite_cookie']['samesite_cookie_enable_legacy_browser_workaround'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable legacy browser workaround'),
    '#description' => t('This workaround is used for browsers that identify with known problematic user agent strings. If the browser is incapable of handling the attribute, do not set it.') . "<br>\n" . t('Based on:') . ' ' . l('https://www.chromium.org/updates/same-site/incompatible-clients', 'https://www.chromium.org/updates/same-site/incompatible-clients') . '.',
    '#default_value' => variable_get('samesite_cookie_enable_legacy_browser_workaround'),
  );
  $form = system_settings_form($form);
  return $form;
}
