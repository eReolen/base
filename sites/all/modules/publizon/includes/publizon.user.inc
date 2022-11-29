<?php

/**
 * @file
 * Ding user provider for Publizon.
 */

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
    throw new DingProviderUserAuthFailure('Only single sign on is supported');
}

/**
 * Do "authenticate" an externally authenticated user.
 *
 * Not an official provider function yet, but hopefully it will be:
 * https://platform.dandigbib.org/issues/3582
 */
function publizon_user_external_authenticate($name, $pass = NULL, array $values = array()) {
  throw new DingProviderUserAuthFailure('Only single sign on is supported');
}

/**
 * Finalize the account after login.
 */
function publizon_user_authenticate_finalize($account) {
}
