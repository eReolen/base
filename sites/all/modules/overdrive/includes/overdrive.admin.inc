<?php
/**
 * @file
 * Defines the administration interface for configuring overdrive
 */

/**
 * Overdrive settings form.
 *
 * @param array $form
 *   The form input.
 * @param array $form_state
 *   The state of the form.
 *
 * @return array
 *   The finished form.
 */
function overdrive_settings_form($form, &$form_state) {
  $default = array(
    'value' => '',
    'format' => 'ding_wysiwyg',
  );
  $default = variable_get('overdrive_information_text', $default);

  $form['overdrive_information_text'] = array(
    '#type' => 'text_format',
    '#title' => t('Information text'),
    '#description' => t('The text to display before begin redirected to overdrive.'),
    '#default_value' => $default['value'],
    '#format' => $default['format'],
  );

  // Make the form look like at system form.
  $form = system_settings_form($form);

  return $form;
}
