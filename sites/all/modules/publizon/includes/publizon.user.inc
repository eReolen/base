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
    '#options' => publizon_get_libraries_list(),
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
  }
  else {
    $res = array(
      'success' => FALSE,
    );
  }

  return $res;
}

/**
 * Finalize the account after login.
 *
 * TODO This should not be used, we get data from session instead
 * of receiving it directly. Not good!
 */
function publizon_user_authenticate_finalize($account) {
  // Add provider role to user.
  // TODO Make sure that Ding is not supposed to handle this.
  user_multiple_role_edit(array($account->uid), 'add_role', 8);

  $profile = profile2_load_by_user($account->uid, 'provider_publizon');
  $langs = field_language('profile2', $profile);
  // Get retailer id from session.
  // TODO NOT the right way to do it.
  $profile->field_publizon_retailer_id[$langs['field_publizon_retailer_id']][0]['value'] = $_SESSION['ding_user']['user']['data']['retailer_id'];
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
