<?php

/**
 * @file
 * Implements functions used to log users into the system through SSO services.
 */

/**
 * Implements hook_auth_single_sign_on().
 *
 * @oaram string $uuid
 *   Unique id for the person that's should be generated credentials for.
 *
 * @throws DingProviderUserAuthFailure
 *   If authentication fails.
 */
function publizon_auth_single_sign_on($name, array $extra) {
  $lib = publizon_filter_libraries_list(array($extra['attributes']['municipality']));
  $retailer_id = reset($lib)->retailer_id;
  if (is_null($retailer_id)) {
    throw new DingProviderUserAuthFailure('Unable to find retailer id');
  }

  /** @TODO Get $support_id somewhere */
//  /** @var \PublizonLoanClient $client */
//    $client = PublizonLoanClient::getClient();
//    $orders = $client->getLibraryUserOrderList($retailer_id, $name);
//  $support_id = $client->validateLibraryUser($name, NULL, $retailer_id);
  $support_id = 'XR56KQ';
  if ($support_id) {
    $res = array(
      'success' => TRUE,
      'creds' => array(
        'name' => $name,
        'pass' => '',
      ),
      'user' => array(
        'mail' => '',
        'blocked' => FALSE,
        'data' => array(
          'display_name' => '',
          // Transfer retailer id to save on the user.
          'retailer_id' => $retailer_id,
          'support_id' => is_string($support_id) ? $support_id : '',
        ),
      ),
    );

    // Save cookie for publizon_user_form_alter().
    setcookie('ereolen_last_library', $retailer_id, time() + 3600 * 24 * 180, '/');
  }
  else {
    throw new DingProviderUserAuthFailure();
  }

  return $res;
}
