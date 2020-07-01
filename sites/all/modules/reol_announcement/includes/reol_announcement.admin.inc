<?php

/**
 * @file
 * Defines the administration interface for configuring announcements.
 */

/**
 * Announcement settings form.
 *
 * @param array $form
 *   The form input.
 * @param array $form_state
 *   The state of the form.
 *
 * @return array
 *   The finished form.
 */
function reol_announcement_settings_form(array $form, array &$form_state) {
  $form['reol_announcement_state'] = array(
    '#type' => 'radios',
    '#title' => t('Announcement state'),
    '#description' => t('The state of the announcement.'),
    '#options' => array(
      REOL_ANNOUNCEMENT_DISABLED => t('Disabled'),
      REOL_ANNOUNCEMENT_ENABLED => t('Enabled'),
      REOL_ANNOUNCEMENT_WARNING => t('Warning'),
    ),
    '#default_value' => variable_get('reol_announcement_state', REOL_ANNOUNCEMENT_DISABLED),
    '#required' => TRUE,
  );

  $default = array(
    'value' => '',
    'format' => 'ding_wysiwyg',
  );
  $value = variable_get('reol_announcement_announcement', $default);

  $form['reol_announcement_announcement'] = array(
    '#type' => 'text_format',
    '#title' => t('Announcement'),
    '#description' => t('The announcement to display'),
    '#default_value' => $value['value'],
    '#format' => $value['format'],
  );

  // Make the form look like at system form.
  $form = system_settings_form($form);

  return $form;
}
