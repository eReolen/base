<?php
/**
 * @file
 * Defines the administration interface for configuring communication with the
 * Pulizon web-service.
 */

/**
 * Administration form for the configureation of the communication with
 * publizon.
 *
 * @return array $form
 */
function publizon_settings_form($form, &$form_state) {
  $form['publizon']['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Default settings'),
    '#description' => t('These settings are used to communicate with the publizon web-service, when no user is logged in. They are required to be able to fetch information about products (eg. covers and basic information from Publizon)'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );

  $form['publizon']['settings']['publizon_base_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Base URL of the web-service'),
    '#description' => t('The URL of the web-service at Publizon (eg. https://libraryservices.pubhub.dk/)'),
    '#default_value' => variable_get('publizon_base_url', 'https://libraryservices.pubhub.dk/'),
    '#required' => TRUE,
  );

  $form['publizon']['settings']['publizon_retailer_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Retailer ID'),
    '#description' => t("This is the library's identification at publizon, which you should recieve from them."),
    '#default_value' => variable_get('publizon_retailer_id', ''),
    '#required' => TRUE,
  );

  $form['publizon']['settings']['publizon_retailer_key_code'] = array(
    '#type' => 'textfield',
    '#title' => t('Retailer key code'),
    '#description' => t('This is a MD5 hash of the code provided with the retailer ID above.'),
    '#default_value' => variable_get('publizon_retailer_key_code', ''),
    '#required' => TRUE,
  );

  $form['publizon']['settings']['publizon_logging'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable logging'),
    '#default_value' => variable_get('publizon_logging', 0),
  );

  // Make the form look like at system form.
  $form = system_settings_form($form);

  return $form;
}
