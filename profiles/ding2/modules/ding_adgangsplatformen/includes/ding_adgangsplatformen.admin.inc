<?php
/**
 * @file
 * Defines the administration interface for the module.
 */

/**
 * Defines the administration settings form.
 */
function ding_adgangsplatformen_admin_settings_form($form, &$form_state) {
  $form = array(
    '#tree' => TRUE,
  );

  $form['ding_adgangsplatformen_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Adgangsplatformen configuration'),
  );

  $default = ding_adgangsplatformen_get_configuration();

  $form['ding_adgangsplatformen_settings']['clientId'] = array(
    '#type' => 'textfield',
    '#title' => t('Client ID'),
    '#size' => 35,
    '#description' => t('The client id should be obtained from the authentication provider - DBC.'),
    '#default_value' => $default['clientId'],
  );

  $form['ding_adgangsplatformen_settings']['clientSecret'] = array(
    '#type' => 'textfield',
    '#title' => t('Client secret'),
    '#size' => 63,
    '#description' => t('Get this from the provider - DBC.'),
    '#default_value' => $default['clientSecret'],
  );

  $form['ding_adgangsplatformen_settings']['redirectUri'] = array(
    '#type' => 'textfield',
    '#title' => t('Redirect URL'),
    '#description' => t('The URL to be redirected to after login - you should not change this URL as it has to match the provider configuration at DBC.'),
    '#default_value' => $default['redirectUri'],
    '#disabled' => TRUE,
  );

  $form['ding_adgangsplatformen_settings']['urlAuthorize'] = array(
    '#type' => 'textfield',
    '#title' => t('Authorization service'),
    '#description' => t('The authorization service end-point.'),
    '#default_value' => $default['urlAuthorize'],
  );

  $form['ding_adgangsplatformen_settings']['urlAccessToken'] = array(
    '#type' => 'textfield',
    '#title' => t('Access token service'),
    '#description' => t('The access token service end-point.'),
    '#default_value' => $default['urlAccessToken'],
  );

  $form['ding_adgangsplatformen_settings']['urlResourceOwnerDetails'] = array(
    '#type' => 'textfield',
    '#title' => t('Resource end-point'),
    '#description' => t('The location of the resource service.'),
    '#default_value' => $default['urlResourceOwnerDetails'],
  );

  $form['ding_adgangsplatformen_settings']['urlLogout'] = array(
    '#type' => 'textfield',
    '#title' => t('Logout'),
    '#description' => t('Logout service location.'),
    '#default_value' => $default['urlLogout'],
  );

  $form['ding_adgangsplatformen_settings']['revoke'] = array(
    '#type' => 'textfield',
    '#title' => t('Revoke service'),
    '#description' => t('The end-point to use for revoking an access token.'),
    '#default_value' => $default['revoke'],
  );

  $form['ding_adgangsplatformen_settings']['singleLogout'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable single logout'),
    '#return_value' => TRUE,
    '#default_value' => $default['singleLogout'],
  );

  $form['ding_adgangsplatformen_settings']['automaticallyAgency'] = array(
    '#type' => 'checkbox',
    '#title' => t('Automatically select your library at adgangsplatformen (only if agency is detected)'),
    '#return_value' => TRUE,
    '#default_value' => $default['automaticallyAgency'],
  );

  $form['ding_adgangsplatformen_settings']['agencytype'] = array(
    '#type' => 'checkbox',
    '#title' => t('Only show "folkebiblioteker" in library selection dropdown (agencytype=folk)'),
    '#return_value' => TRUE,
    '#default_value' => $default['agencytype'] ?? TRUE,
  );

  $form['ding_adgangsplatformen_settings']['singleLogoutOrigin'] = array(
    '#type' => 'textfield',
    '#title' => t('Iframe url'),
    '#description' => t('The URI from which single logout can be performed.'),
    '#default_value' => $default['singleLogoutOrigin'],
    '#disabled' => TRUE,
    '#states' => array(
      'invisible' => array(
        ':input[name="ding_adgangsplatformen_settings[singleLogout]"]' => array('checked' => FALSE),
      ),
    ),
  );

  $form['token_client'] = array(
    '#type' => 'fieldset',
    '#title' => t('Token client'),
    '#description' => t('This client will be used for deescalating token access after login.'),
    // Collapse config. This should usually not be touched.
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    // Do not use tree here to keep the token client out of the default config.
    '#tree' => FALSE,
  );

  $form['token_client']['ding_adgangsplatformen_token_client_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Client ID'),
    '#default_value' => variable_get('ding_adgangsplatformen_token_client_id'),
  );

  $form['token_client']['ding_adgangsplatformen_token_client_secret'] = array(
    '#type' => 'textfield',
    '#title' => t('Client secret'),
    '#default_value' => variable_get('ding_adgangsplatformen_token_client_secret'),
  );

  return system_settings_form($form);
}
