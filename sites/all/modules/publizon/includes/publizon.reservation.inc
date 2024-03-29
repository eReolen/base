<?php

/**
 * @file
 * Ding reservation provider for Publizon.
 */

/**
 * Get list of reservations.
 *
 * @param object $account
 *   The user to get the list for.
 * @param string $get_type
 *   The type to get reservations for.
 * @param bool $reset
 *   If TRUE cache is reset (default: FALSE).
 *
 * @return array
 *   Result array of reservations.
 *
 * @throws DingProviderAuthException
 */
function publizon_reservation_list($account, $get_type = '', bool $reset = FALSE) {
  $results = &drupal_static(__FUNCTION__, NULL);

  if (is_null($results) || $reset) {
    // Check if ding_session_cache is available.
    if (module_exists('ding_session_cache') && !$reset) {
      $results = ding_session_cache_get('publizon', 'reservation', NULL);
    }

    // If both static cache and session cache failed, try reloading information
    // from publizon.
    if (is_null($results) || $reset) {
      $results = array(
        DING_RESERVATION_READY => array(),
        DING_RESERVATION_NOT_READY => array(),
        DING_RESERVATION_INTERLIBRARY_LOANS => array(),
      );

      // Throw exception if we're not logged in.
      $creds = ding_user_get_creds();

      $retailer_id = publizon_get_retailer_id($account);

      // Get list of reservations from Publizon.
      $client = PublizonReservationClient::getClient();
      $reservations = $client->listReservations($retailer_id, $creds['name']);

      $isbns = array();
      foreach ($reservations as $reservation) {
        $isbns[] = $reservation->isbn;
      }

      if ($isbns) {
        $mapping = reol_base_ding_entity_get_ids($isbns);
      }

      foreach ($reservations as $reservation) {
        // Title might not be found, use an fake ID.
        if (!isset($mapping[$reservation->isbn])) {
          $ding_id = 'publizon:' . $reservation->isbn;
        }
        else {
          $ding_id = $mapping[$reservation->isbn];
        }

        $ting_entity = ding_entity_load($ding_id);
        if ($ting_entity) {
          $id = $ting_entity->localId;
          $type = $reservation->status == 2 ? DING_RESERVATION_READY : DING_RESERVATION_NOT_READY;
          $data = array(
            'order_id' => $id,
            'ding_entity_id' => $ding_id,
            'ready_for_pickup' => $reservation->status == 2,
            'created' => date('Y-m-d H:i:s', $reservation->createdUtc),
            // To avoid warnings, we have to set this, even though we remove
            // it later.
            'expiry' => date('Y-m-d H:i:s', 0),
            'renewable' => FALSE,
            'reservation_type' => $type,
            'display_name' => $reservation->title,
          );

          // If reservation is ready, add pickup date.
          if ($type == DING_RESERVATION_READY) {
            $data['pickup_date'] = date('Y-m-d H:i:s', $reservation->expireUtc);
          }

          $results[$type][$id] = new DingProviderReservation($id, $data);
          if ($reservation->expectedRedeemDateUtc) {
            $results[$type][$id]->expected_date = date('Y-m-d H:i:s', $reservation->expectedRedeemDateUtc);
          }
        }

      }

      // Store the reservations into ding session cache.
      if (module_exists('ding_session_cache')) {
        ding_session_cache_set('publizon', 'reservation', $results);
      }
    }
  }

  return !empty($get_type) ? $results[$get_type] : $results;
}

/**
 * Create reservation.
 *
 * @param object $account
 *   The account that is creating a reservation.
 * @param string $local_id
 *   The provider id of the title to reserve.
 * @param array $options
 *   Array of options from the options form.
 *
 * @return array
 *   Result array possibly containing the number in queue.
 */
function publizon_reservation_create($account, $local_id, array $options) {
  $isbn = reol_base_get_isbn($local_id);
  // If we do not have an ISBN, we cannot reserve anything.
  if (!$isbn) {
    throw new DingProviderReservationNotAvailable();
  }

  // Get user profile.
  $profile = profile2_load_by_user($account->uid, 'provider_publizon');
  $profile_wrapper = entity_metadata_wrapper('profile2', $profile);

  // Get the email and phone for notifications.
  // Only if user has selected to get notifications.
  $email = '';
  if ($options['email_notification']) {
    $email = $profile_wrapper->field_email->value();
  }

  $phone = '';
  if ($options['phone_notification']) {
    $phone = $profile_wrapper->field_phone->value();
  }

  try {
    $client = PublizonReservationClient::getClient();

    // Get the retailer id on the user.
    $retailer_id = publizon_get_retailer_id($account);

    // This will throw exception if not logged in.
    $creds = ding_user_get_creds();
    $user_data = publizon_get_user_data();

    // Check if institution tags exists (to prevent users already logged-in
    // missing this object. We have this extra check).
    $tags = $user_data['tags'] ?? array();

    // This will throw exception if reservation does not go through.
    $client->createReservation($retailer_id, $creds['name'], $creds['pass'], $isbn, $email, $phone, $tags);

    // Clear ding session cache.
    if (module_exists('ding_session_cache')) {
      ding_session_cache_clear('publizon', 'reservation');
    }
  }
  catch (PublizonException $e) {
    PublizonDingProviderException::convert($e);
  }

  return array();
}

/**
 * Delete reservation.
 *
 * @param object $account
 *   The account to delete reservation for.
 * @param string $local_id
 *   The local id of the title to delete reservation for.
 */
function publizon_reservation_delete($account, $local_id) {
  $isbn = reol_base_get_isbn($local_id);
  // If we do not have an ISBN number, we cannot remove reservation.
  // This should not happen, as same check is performed during reserve.
  if (!$isbn) {
    return;
  }
  // This will throw exception if not logged in.
  $creds = ding_user_get_creds($account);

  // Get the retailer id on the user.
  $retailer_id = publizon_get_retailer_id($account);

  $client = PublizonReservationClient::getClient();
  // This will throw exception if reservation is not deleted.
  $client->deleteReservation($retailer_id, $creds['name'], $isbn);

  // Clear ding session cache.
  if (module_exists('ding_session_cache')) {
    ding_session_cache_clear('publizon', 'reservation');
  }
}

/**
 * Provide options for reservation.
 *
 * As ding_provider/ding_reservation does not provide access to the form
 * and form_state variables, we have to use form_alter instead. When adding
 * fields to a form, the function alters both form and form_state, and we
 * need those changed applied.
 *
 * @see publizon_form_ding_reservation_reserve_form_alter()
 */
function publizon_reservation_options($account) {
  return array();
}

/**
 * Submit options form.
 *
 * @param object $account
 *   The account options have been submitted for.
 * @param array $values
 *   The values submitted.
 */
function publizon_reservation_options_submit($account, array $values) {
}

/**
 * Default options for the user.
 *
 * @param object $account
 *   The account to get default options for.
 *
 * @return array
 *   Array of the default options keyed by form item name.
 */
function publizon_reservation_default_options($account) {
  return array();
}

/**
 * Ding requires this function. We do not need it.
 *
 * @return null
 *   Empty response always.
 */
function publizon_reservation_branch_name($branch_id) {
  return NULL;
}

/**
 * Ding requires this function. We do not need it.
 */
function publizon_reservation_default_interest_period() {
  return 0;
}

/**
 * Returns whether or not deletions are enabled.
 *
 * @return bool
 *   Whether or not deletions are enabled.
 */
function publizon_reservation_reservation_deletion_enabled() {
  return TRUE;
}

/**
 * Implements provider reservation, is_reservable.
 *
 * This should not be used as we determined this in reol_loan in entity_button
 * hook.
 */
function publizon_reservation_is_reservable($provider_ids) {
  return FALSE;
}
