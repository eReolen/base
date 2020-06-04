<?php

/**
 * @file
 * Ding user provider for Publizon.
 */

/**
 * Alter the login form.
 *
 * @param array $form
 *   The form array to alter.
 * @param array $form_state
 *   The state of the form.
 */
function publizon_user_form_alter(array &$form, array &$form_state) {
  $default_value = NULL;

  if (!empty($form['user_login_container'])) {
    // Pre-select library if we have the cookie.
    if (isset($_COOKIE['ereolen_last_library']) &&
      preg_match('/^\d+$/', $_COOKIE['ereolen_last_library'])) {
      $default_value = $_COOKIE['ereolen_last_library'];
    }

    $form['user_login_container']['retailer_id'] = array(
      '#type' => 'select',
      '#title' => t('Select library'),
      '#options' => publizon_get_libraries_list(),
      '#default_value' => $default_value,
    );
  }

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
 *
 * @throws DingProviderUserAuthFailure
 *   On user login failure.
 */
function publizon_user_authenticate($name, $pass, array $values) {
  $client = PublizonUserClient::getClient();

  $support_id = $client->validateLibraryUser($name, $pass, $values['retailer_id']);
  if ($support_id) {
    $res = array(
      'success' => TRUE,
      'creds' => array(
        'name' => $name,
        'pass' => $pass,
      ),
      'user' => array(
        'mail' => '',
        'blocked' => FALSE,
        'data' => array(
          'display_name' => '',
          // Transfer retailer id to save on the user.
          'retailer_id' => $values['retailer_id'],
          'support_id' => is_string($support_id) ? $support_id : '',
        ),
      ),
    );

    // Save cookie for publizon_user_form_alter().
    setcookie('ereolen_last_library', $values['retailer_id'], time() + 3600 * 24 * 180, '/');

  }
  else {
    throw new DingProviderUserAuthFailure();
  }

  return $res;
}

/**
 * Do "authenticate" an externally authenticated user.
 *
 * Not an official provider function yet, but hopefully it will be:
 * https://platform.dandigbib.org/issues/3582
 */
function publizon_user_external_authenticate($name, $pass = NULL, array $values = array()) {
  // Just pass it on to publizon_user_authenticate(), Publizon should handle
  // missing pincode when the client id matches eReolenGo.
  return publizon_user_authenticate($name, $pass, $values);
}

/**
 * Finalize the account after login.
 */
function publizon_user_authenticate_finalize($account) {
}
