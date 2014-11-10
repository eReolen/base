<?php

/**
 * @file
 * Ding user provider for Publizon
 */

/**
 * Alter the login form.
 *
 * @param array $form
 *   The form array to alter.
 * @param array $form_state
 *   The state of the form
 *
 * @return array
 *   The altered form array.
 */
function publizon_user_user_login_form_alter($form, $form_state) {
  $form['retailer_id'] = array(
    '#type' => 'select',
    '#title' => t('Select library'),
    '#options' => array_map(function ($elem) {
      return $elem['library_name'];
    }, publizon_get_libraries()),
  );

  return $form;
}

/**
 * Alter the authenticate form.
 *
 * @param array $form
 *   The form array to alter.
 * @param array $form_state
 *   The state of the form
 *
 * @return array
 *   The altered form array.
 */
function publizon_user_authenticate_form_alter($form, $form_state) {
  return publizon_user_user_login_form_alter($form, $form_state);
}

/**
 * Authenticate user.
 *
 * @param string $name
 *   The name of the user to sign in.
 * @param string $pass
 *   The password for the user.
 * @param array $values
 *   All the values from the login form.
 *
 * @return array
 *   Result array.
 */
function publizon_user_authenticate($name, $pass, $values) {
  $res = array();

  $client = PublizonClient::getClient();

  if ($client->validateLibraryUser($name, $pass, $values['retailer_id'])) {
    $res = array(
      'success' => TRUE,
      // Transfer retailer id to save on the user.
      'retailer_id' => $values['retailer_id'],
    );
  }
  else {
    $res = array(
      'success' => FALSE,
    );
  }

  return $res;
}

/**
 * Initialise profile.
 *
 * @TODO
 */
function publizon_user_profile_init($profile, $auth_res) {
  publizon_profile_update($profile, $auth_res);

  $profile->save();
}

/**
 * Is user authenticated?.
 *
 * Test that credentials is still valid. If this function is not
 * defined, it is assumed that having credentials available is enough.
 *
 * @TODO
 */
function publizon_user_is_authenticated($creds) {
  return (isset($creds['name']) && isset($creds['pass']));
}

/**
 * Update user account.
 *
 * Update email and/or pincode for user.
 *
 * @TODO
 *
 * @param StdClass $account
 *   User object.
 * @param array $changes
 *   An array with 'mail' and/or 'pass' keys.
 *
 * @return array
 *   An array, optionally with new 'creds' which will be cached.
 */
function publizon_user_account_update($account, $changes) {
  $result = array();

  return $result;
}
