<?php

/**
 * @file
 * Settings for prevent unpublish module.
 */

/**
 * Administrative settings form.
 *
 * @param array $form
 *   The form input.
 * @param array $form_state
 *   The state of the form.
 *
 * @return array
 *   The finished form.
 */
function reol_prevent_unpublish_settings_form(array $form, array &$form_state) {
  $form = [];

  $form['wrapper'] = [
    '#type' => 'fieldset',
    '#title' => t('Settings'),
  ];

  $form['wrapper']['reol_prevent_unpublish_nid'] = [
    '#type' => 'textfield',
    '#title' => t('Node identifiers'),
    '#description' => t('Comma separated list of node nid that should never be unpublished.'),
    '#default_value' => variable_get('reol_prevent_unpublish_nid', ''),
  ];

  return system_settings_form($form);
}
