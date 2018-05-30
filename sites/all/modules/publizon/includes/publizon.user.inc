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

  // Pre-select library if we have the cookie.
  if (isset($_COOKIE['ereolen_last_library']) &&
    preg_match('/^\d+$/', $_COOKIE['ereolen_last_library'])) {
    $default_value = $_COOKIE['ereolen_last_library'];
  }

  $form['retailer_id'] = array(
    '#type' => 'select',
    '#title' => t('Select library'),
    '#options' => publizon_get_libraries_list(),
    '#default_value' => $default_value,
  );
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
function publizon_user_authenticate($name, $pass, array $values) {
  $res = array();

  $client = PublizonUserClient::getClient();

  if ($client->validateLibraryUser($name, $pass, $values['retailer_id'])) {
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
        ),
      ),
    );

    // Save cookie for publizon_user_form_alter().
    setcookie('ereolen_last_library', $values['retailer_id'], time() + 3600 * 24 * 180, '/');

  }
  else {
    $res = array(
      'success' => FALSE,
    );
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
 *
 * TODO This should not be used, we get data from session instead
 * of receiving it directly. Not good!
 */
function publizon_user_authenticate_finalize($account) {
  $profile = profile2_load_by_user($account->uid, 'provider_publizon');
  $langs = field_language('profile2', $profile);
  // Get retailer id from session.
  // TODO NOT the right way to do it.
  $profile->field_publizon_retailer_id[$langs['field_publizon_retailer_id']][0]['value'] = $_SESSION['ding_user']['user']['data']['retailer_id'];
  $profile->save();
}
