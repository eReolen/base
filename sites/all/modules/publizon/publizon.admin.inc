<?php

/**
 * @file
 * Implements the administration UI for the publizon module.
 */

/**
 * Publizon settings form.
 */
function publizon_admin_settings_form($form, &$form_state) {
  $form['publizon_test_card_numbers'] = array(
    '#type' => 'textarea',
    '#title' => t('Test card numbers'),
    '#description' => t('Card numbers used for testing. One per line.'),
    '#default_value' => implode(PHP_EOL, variable_get('publizon_test_card_numbers', [])),
    '#rows' => 20,
  );

  // Make the form look like at system form.
  $form['#submit'][] = 'publizon_admin_settings_form_submit';
  $form = system_settings_form($form);

  return $form;
}

function publizon_admin_settings_form_submit(array $form, array &$form_state) {
  $values = &$form_state['values'];

  $values['publizon_test_card_numbers'] = array_filter(
    array_map(
      'trim',
      explode(
        PHP_EOL,
        $values['publizon_test_card_numbers']
      )
    )
  );
}
