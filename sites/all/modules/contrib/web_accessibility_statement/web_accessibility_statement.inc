<?php
/**
 * @file
 * Helper functions for web accessibility statement module.
 */

/**
 * Admin form for web accessibility.
 *
 * @param array $form
 *   The admin form.
 * @param array $form_state
 *   The state of the form.
 * @return mixed
 *   The form structure.
 */
function accessibility_admin_form(array $form, array &$form_state) {
  $form['web_accessibility_statement_url'] = [
    '#type' => 'textfield',
    '#title' => t('Accessibility statement absolute url'),
    '#description' => t('Add the absolute url to the accessibility report.'),
    '#maxlength' => 128,
    '#size' => 64,
    '#default_value' => variable_get('web_accessibility_statement_url'),
  ];

  return system_settings_form($form);
}
