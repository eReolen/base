<?php
/**
 * @file
 * Ding reservation provider for Publizon.
 */

/**
 * Get list of reservations.
 *
 * @param StdClass $account
 *   The user to get the list for.
 *
 * @TODO
 */
function publizon_reservation_list($account) {
  $result = array(
    DING_RESERVATION_READY => array(),
    DING_RESERVATION_NOT_READY => array(),
    DING_RESERVATION_INTERLIBRARY_LOANS => array(),
  );

  // Throw exception if we're not logged in.
  $creds = ding_user_get_creds($account);

  $retailer_id = publizon_get_retailer_id($account);

  // Get list of reservations from Publizon.
  $client = PublizonClient::getClient();
  $reservations = $client->listReservations($retailer_id, $creds['name']);

  module_load_include('client.inc', 'ting');
  foreach ($reservations as $reservation) {
    $id = $reservation->bookId;
    $type = $reservation->status == 2 ? DING_RESERVATION_READY : DING_RESERVATION_NOT_READY;
    $result[$type][$id] = new DingProviderReservation($id, array(
      'order_id' => $id,
      // TODO Hardcoding this until API is ready.
      'ding_entity_id' => '870970-basis:50604934',
      'ready_for_pickup' => $reservation->status == 2,
      'created' => date('Y-m-d H:i:s', $reservation->createdUtc),
      'queue_number' => 10,
      'renewable' => FALSE,
      'reservation_type' => $type,
    ));

    // If reservation is ready, add pickup date.
    if ($type == DING_RESERVATION_READY) {
      $result[$type][$id]['pickup_date'] = date('Y-m-d H:i:s', $reservation->expireUtc);
    }
  }

  return $result;
}

/**
 * Create reservation.
 *
 * @param StdClass $account
 *   The account that is creating a reservation.
 * @param string $local_id
 *   The provider id of the title to reserve.
 * @param array $options
 *   Array of options from the options form.
 *
 * @return array
 *   Result array possibly containing the number in queue.
 */
function publizon_reservation_create($account, $local_id, $options) {
  $isbn = reol_base_get_isbn($local_id);
  // If we do not have an ISBN number, we cannot reserve anything.
  if (!$isbn) {
    throw new DingProviderReservationNotAvailable();
  }
  // This will throw exception if not logged in.
  $creds = ding_user_get_creds($account);

  // Get the retailer id on the user.
  $profile = profile2_load_by_user($account, 'provider_publizon');
  $profile_wrapper = entity_metadata_wrapper('profile2', $profile);
  $retailer_id = $profile_wrapper->field_publizon_retailer_id->value();

  // Get the email and phone for notifications.
  // Only if user has selected to get notifications.
  $email = '';
  if ($options['email_notification']) {
    $email_lang = field_language('profile2', $profile, 'field_email');
    $email = $options['field_email'][$email_lang][0]['email'];
  }
  $phone = '';
  if ($options['phone_notification']) {
    $phone_lang = field_language('profile2', $profile, 'field_phone');
    $phone = $options['field_phone'][$phone_lang][0]['value'];
  }

  $client = PublizonClient::getClient();
  // This will throw exception if reservation does not go through.
  $client->createReservation($retailer_id, $creds['name'], $creds['pass'], $isbn, $email, $phone);
  return array();
}

/**
 * Delete reservation.
 *
 * @TODO
 */
function publizon_reservation_delete($account, $id) {
  // Throw exception if we're not logged in.
  ding_user_get_creds($account);
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
 * @param array $account
 *   The account options have been submitted for.
 * @param array $values
 *   The values submitted.
 */
function publizon_reservation_options_submit($account, $values) {
}

/**
 * Default options for the user.
 *
 * @param array $account
 *   The account to get default options for.
 *
 * @return array
 *   Array of the default options keyed by form item name.
 */
function publizon_reservation_default_options($account) {
  return array();
}

/**
 * Default interest period.
 *
 * @TODO
 */
function publizon_reservation_default_interest_period($profile = NULL) {
  return 0;
}

/**
 * Ding requires this function. We do not need it.
 *
 * @return NULL
 *   Empty response always.
 */
function publizon_reservation_branch_name($branch_id) {
  return NULL;
}
