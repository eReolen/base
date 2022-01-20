<?php

/**
 * @file
 * Admin form for media_videotool.
 */

use Drupal\media_videotool\ApiClient;

/**
 * The administration form for this module.
 *
 * @param array $form
 *   The form input.
 * @param array $form_state
 *   The state of the form.
 *
 * @return array
 *   The finished form.
 */
function media_videotool_admin_form(array $form, array &$form_state) {
  $form['media_videotool_api_key'] = [
    '#type' => 'fieldset',
    '#title' => t('API keys'),
    '#tree' => TRUE,
    '#description' => t('Enter API keys from <a href="@api_info_url">@api_info_url</a>', ['@api_info_url' => 'https://videotool.dk/settings/api_keys.php']),
  ];

  $form['media_videotool_api_key']['public'] = [
    '#type' => 'textfield',
    '#title' => t('Public key'),
    '#default_value' => variable_get('media_videotool_api_key')['public'] ?? NULL,
    '#required' => TRUE,
  ];

  $form['media_videotool_api_key']['secret'] = [
    '#type' => 'textfield',
    '#title' => t('Secret key'),
    '#default_value' => variable_get('media_videotool_api_key')['secret'] ?? NULL,
    '#required' => TRUE,
  ];

  return system_settings_form($form);
}

/**
 * Validate handler for the administration form.
 *
 * @param array $form
 *   The form input.
 * @param array $form_state
 *   The state of the form.
 */
function media_videotool_admin_form_validate(array $form, array &$form_state) {
  $client = new ApiClient([
    'public_key' => $form_state['values']['media_videotool_api_key']['public'] ?? NULL,
    'secret_key' => $form_state['values']['media_videotool_api_key']['secret'] ?? NULL,
  ]);
  if (!$client->authenticate()) {
    form_set_error('media_videotool_api_key', t('Cannot authenticate with Videotool API'));
  }
}
