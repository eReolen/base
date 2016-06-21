<?php
/**
 * @file
 * Implements the administration UI for the module.
 */

/**
 * UNI•Login settings form.
 */
function ding_unilogin_admin_settings_form($form, &$form_state) {
  $form['ding_unilogin_id'] = array(
    '#type' => 'textfield',
    '#title' => t('UNI•Login ID'),
    '#description' => t('The UNI•Login ID. Leave empty to disable UNI•Login.'),
    '#default_value' => variable_get('ding_unilogin_id', ''),
  );

  $form['ding_unilogin_secret'] = array(
    '#type' => 'textfield',
    '#title' => t('UNI•Login shared secret'),
    '#description' => t('The shared secret used for UNI•Login.'),
    '#default_value' => variable_get('ding_unilogin_secret', ''),
  );

  $form['ding_unilogin_client_id'] = array(
    '#type' => 'textfield',
    '#title' => t('UNI•Login Client ID'),
    '#description' => t('The client ID to send to publizon for UNI•Login users.'),
    '#default_value' => variable_get('ding_unilogin_client_id', ''),
  );

  // Make the form look like at system form.
  $form = system_settings_form($form);

  return $form;
}
