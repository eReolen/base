<?php

/**
 * @file
 * Ding user provider for Publizon
 */

/**
 * Authenticate user.
 *
 * @TODO
 */
function publizon_user_authenticate($name, $pass) {
  $res = array(
    'success' => FALSE,
  );
  return $res;
}

/**
 * Initialise profile.
 *
 * @TODO
 */
function publizon_user_profile_init($profile, $auth_res) {
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
