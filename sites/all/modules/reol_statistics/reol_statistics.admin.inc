<?php

/**
 * @file
 * Adminstative pages for the module.
 */

/**
 * Settings page callback.
 */
function reol_statistics_settings($form, &$form_state) {
  $form = array();

  $form['reol_statistics_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#description' => t('Title of statistics page'),
    '#default_value' => variable_get('reol_statistics_title', REOL_STATISTICS_DEFAULT_TITLE),
  );

  $default_value = variable_get('reol_statistics_header',
                                array(
                                  'value' => REOL_STATISTICS_DEFAULT_HEADER,
                                  'format' => 'plain_text',
                                ));
  $form['reol_statistics_header'] = array(
    '#type' => 'text_format',
    '#title' => t('Header'),
    '#description' => t('Header on statistics pages. Available placeholders: @date: date of Display, @municipality: name of the municipality, @subscribed_users: number of subscribed users in the municipality.'),
    '#default_value' => $default_value['value'],
    '#format' => $default_value['format'],
  );

  return system_settings_form($form);
}
