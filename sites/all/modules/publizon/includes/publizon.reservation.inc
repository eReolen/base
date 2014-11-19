<?php
/**
 * @file
 * Ding reservation provider for Publizon.
 */

/**
 * Get list of reservations.
 *
 * @TODO
 */
function publizon_reservation_list($account) {
  // Throw exception if we're not logged in.
  ding_user_get_creds($account);
  $result = array();

  return $result;
}

/**
 * Create reservation.
 *
 * @param StdClass $account
 *   The account that is creating a reservation.
 * @param mixed $id
 *   The provider id of the title to reserve.
 * @param array $options
 *   Array of options from the options form.
 *
 * @return array
 *   Result array possibly containing the number in queue.
 */
function publizon_reservation_create($account, $id, $options) {
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
  $client->createReservation($retailer_id, $creds['name'], $creds['pass'], $options['isbn'], $email, $phone);
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
 * Save the values onto the user, if they have changed.
 *
 * @param array $account
 *   The account options have been submitted for.
 * @param array $values
 *   The values submitted.
 */
function publizon_reservation_options_submit($account, $values) {
  $profile = profile2_load_by_user($account, 'provider_publizon');

  $changed = FALSE;
  $fields = array(
    'field_phone' => 'phone_notification',
    'field_email' => 'email_notification',
  );

  // Check if fields have changed, and change them on the profile.
  foreach ($fields as $field => $checkbox) {
    // To not confuse the user, we only save values that result in notification.
    // If they have not chosen notif for the field, do not save the value.
    if (!$values[$checkbox]) {
      continue;
    }

    $lang = field_language('profile2', $profile, $field);
    if ($profile->$field != $values[$field]) {
      $profile->$field = $values[$field];
      $changed = TRUE;
    }
  }

  // Save if we have changes.
  if ($changed) {
    $profile->save();
  }
}

/**
 * Default options for the user.
 *
 * If the default options are actually valid, the reservation
 * form would never be shown. We do not want this, we hardcode
 * it to not be set.
 *
 * @param array $account
 *   The account to get default options for.
 *
 * @return array
 *   Array of the default options keyed by form item name.
 */
function publizon_reservation_default_options($account) {
  return array(
    'field_phone' => NULL,
    'field_email' => NULL,
    'phone_notification' => NULL,
    'email_notification' => NULL,
    'isbn' => NULL,
  );
}

/**
 * Default interest period.
 *
 * @TODO
 */
function publizon_reservation_default_interest_period($profile = NULL) {
  return 0;
}
