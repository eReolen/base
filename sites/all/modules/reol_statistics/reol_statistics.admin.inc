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
    '#description' => t('Header on statistics pages. Available placeholders: @date: date of display, @municipality: name of the municipality, @subscribed_users: number of subscribed users in the municipality.'),
    '#default_value' => $default_value['value'],
    '#format' => $default_value['format'],
  );

  $default_value = variable_get('reol_statistics_footer',
                                array(
                                  'value' => '',
                                  'format' => 'plain_text',
                                ));
  $form['reol_statistics_footer'] = array(
    '#type' => 'text_format',
    '#title' => t('Footer'),
    '#description' => t('Footer on statistics pages.'),
    '#default_value' => $default_value['value'],
    '#format' => $default_value['format'],
  );

  $form['reol_statistics_isbn_count'] = array(
    '#type' => 'textfield',
    '#title' => t('ISBN check count'),
    '#description' => t('Number of loans from a single class to flag as possible abuse. Exceeding this will show up in the ISBN table.'),
    '#default_value' => variable_get('reol_statistics_isbn_count', 10),
  );

  $form['reol_statistics_isbn_period'] = array(
    '#type' => 'textfield',
    '#title' => t('ISBN check period'),
    '#description' => t('The number of days in the period.'),
    '#default_value' => variable_get('reol_statistics_isbn_period', 14),
  );

  $form['#submit'][] = 'reol_statistics_settings_submit';

  return system_settings_form($form);
}

/**
 * Submit handler for settings form.
 */
function reol_statistics_settings_submit($form, &$form_state) {
  if (variable_get('reol_statistics_isbn_count', 10) != $form_state['values']['reol_statistics_isbn_count'] ||
      variable_get('reol_statistics_isbn_period', 14) != $form_state['values']['reol_statistics_isbn_period']) {
    drupal_set_message(t('Purging ISBN statistics.'), 'status');
    reol_statistics_reset(new ReolStatisticsISBN());
  }
}
