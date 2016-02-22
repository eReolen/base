<?php
/**
 * @file
 * Plugin to provide access control based upon whether or not we are in app_mode
 */

$plugin = array(
  'title' => t("App mode"),
  'description' => t('Is the site in app mode?'),
  'callback' => 'reol_newsletter_app_mode_ctools_access_check',
);

/**
 * Check for access.
 */
function reol_newsletter_app_mode_ctools_access_check($conf, $context) {
  return reol_newsletter_is_app_mode();
}
