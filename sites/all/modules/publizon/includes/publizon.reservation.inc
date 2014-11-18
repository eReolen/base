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
 * @TODO
 */
function publizon_reservation_create($account, $id, $options) {
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
 */
function publizon_reservation_options($account) {
  $field_form = array(
    '#parents' => array(),
  );
  $form = array();
  $form_state = array();

  $profile = profile2_load_by_user($account, 'provider_publizon');

  // Add phone field.
  $form += reol_base_get_field_form('profile2', 'provider_publizon', 'field_phone', $profile, $field_form, $form_state);

  // Add email field.
  $form += reol_base_get_field_form('profile2', 'provider_publizon', 'field_email', $profile, $field_form, $form_state);

  return $form;
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
    'field_phone',
    'field_email',
  );

  // Check if fields have changed, and change them on the profile.
  foreach ($fields as $field) {
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
