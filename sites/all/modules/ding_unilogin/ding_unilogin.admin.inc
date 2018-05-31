<?php

/**
 * @file
 * Implements the administration UI for the module.
 */

/**
 * UNI•Login settings form.
 */
function ding_unilogin_admin_settings_form($form, &$form_state) {
  // Settings for the basic login service.
  $form['login'] = array(
    '#type' => 'fieldset',
    '#title' => t('UNI•Login'),
    '#description' => t('Settings for the base login service.'),
  );

  $form['login']['ding_unilogin_publizon_client_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Publizon Client ID'),
    '#description' => t('The client ID to send to publizon, for UNI•Login users.'),
    '#default_value' => variable_get('ding_unilogin_publizon_client_id', ''),
    '#required' => TRUE,
  );

  $form['login']['ding_unilogin_id'] = array(
    '#type' => 'textfield',
    '#title' => t('UNI•Login ID'),
    '#description' => t('The UNI•Login ID. Leave empty to disable UNI•Login.'),
    '#default_value' => variable_get('ding_unilogin_id', ''),
  );

  $form['login']['ding_unilogin_secret'] = array(
    '#type' => 'textfield',
    '#title' => t('UNI•Login shared secret'),
    '#description' => t('The shared secret used to calculate hashes.'),
    '#default_value' => variable_get('ding_unilogin_secret', ''),
  );

  $form['login']['ding_unilogin_global_logout'] = array(
    '#type' => 'checkbox',
    '#title' => t('Global logout'),
    '#description' => t('Log out of UNI•Login when logging out of Drupal.'),
    '#default_value' => variable_get('ding_unilogin_global_logout', 0),
  );

  // Settings for WS service general access.
  $form['ws'] = array(
    '#type' => 'fieldset',
    '#title' => t('UNI•Login WS common'),
    '#description' => t('Common settings for the additional information web services.'),
  );

  $form['ws']['ding_unilogin_ws_user'] = array(
    '#type' => 'textfield',
    '#title' => t('UNI•Login webservice user ID'),
    '#default_value' => variable_get('ding_unilogin_ws_user', ''),
  );

  $form['ws']['ding_unilogin_ws_pass'] = array(
    '#type' => 'textfield',
    '#title' => t('UNI•Login webservice password'),
    '#default_value' => variable_get('ding_unilogin_ws_pass', ''),
  );

  // Settings for auth settings.
  $form['auth'] = array(
    '#type' => 'fieldset',
    '#title' => t('UNI•Login Auth'),
    '#description' => t('Settings for the authenticaion web services.'),
  );

  $form['auth']['ding_unilogin_auth_context'] = array(
    '#type' => 'textfield',
    '#title' => t('Context'),
    '#default_value' => variable_get('ding_unilogin_auth_context', ''),
    '#description' => t('The WS05 context to check for access in. If no context is given, all valid UNI•Login users are granted access.'),
  );

  $form['auth']['ding_unilogin_auth_project'] = array(
    '#type' => 'textfield',
    '#title' => t('Project'),
    '#default_value' => variable_get('ding_unilogin_auth_project', ''),
    '#description' => t('The WS05 project to check for access to.'),
  );

  // Make the form look like at system form.
  $form = system_settings_form($form);

  return $form;
}
