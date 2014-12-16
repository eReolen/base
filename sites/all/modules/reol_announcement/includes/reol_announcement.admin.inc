<?php
/**
 * @file
 * Defines the administration interface for configuring announcements
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
function reol_announcement_settings_form($form, &$form_state) {
  $form['state'] = array(
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

  $form['announcement'] = array(
    '#type' => 'text_format',
    '#title' => t('Announcement'),
    '#description' => t('The announcement to display'),
    '#value' => variable_get('reol_announcement_announcement', ''),
    '#format' => 'ding_wysiwyg',
  );

  // Make the form look like at system form.
  $form = system_settings_form($form);

  return $form;
}
