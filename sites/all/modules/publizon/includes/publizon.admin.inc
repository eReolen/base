<?php
/**
 * @file
 * Defines the administration interface for configuring communication with the
 * Pulizon web-service.
 */

/**
 * Publizon settings form.
 *
 * Administration form for the configureation of the communication with
 * publizon.
 *
 * @param array $form
 *   The form input.
 * @param array $form_state
 *   The state of the form.
 *
 * @return array
 *   The finished form.
 */
function publizon_settings_form($form, &$form_state) {
  $form['#tree'] = TRUE;
  drupal_add_css(drupal_get_path('module', 'publizon') . '/css/settings.css');

  $form['publizon']['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Default settings'),
    '#description' => t('These settings are used to communicate with the publizon web-service, when no user is logged in. They are required to be able to fetch information about products (eg. covers and basic information from Publizon)'),
    '#collapsible' => TRUE,
    '#collapsed' => (boolean) variable_get('publizon_base_url', FALSE),
  );

  $form['publizon']['settings']['publizon_base_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Base URL of the web-service'),
    '#description' => t('The URL of the web-service at Publizon (eg. https://libraryservices.pubhub.dk/)'),
    '#default_value' => variable_get('publizon_base_url', 'https://libraryservices.pubhub.dk/'),
    '#required' => TRUE,
  );

  $form['publizon']['settings']['publizon_client_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Client ID'),
    '#description' => t('The client ID to send to publizon.'),
    '#default_value' => variable_get('publizon_client_id', ''),
    '#required' => TRUE,
  );

  if (module_exists('ding_unilogin')) {
    $form['publizon']['settings']['publizon_unilogin_client_id'] = array(
      '#type' => 'textfield',
      '#title' => t('UNI•Login Client ID'),
      '#description' => t('The client ID to send to publizon, for UNI•Login users.'),
      '#default_value' => variable_get('publizon_unilogin_client_id', ''),
      '#required' => TRUE,
    );
  }

  $form['publizon']['settings']['publizon_default_retailer'] = array(
    '#type' => 'textfield',
    '#title' => t('Default library id'),
    '#description' => t('The default librarys id to use for fetching covers. Note: Must be available in list below.'),
    '#default_value' => variable_get('publizon_default_retailer', ''),
    '#required' => TRUE,
  );

  $form['publizon']['settings']['publizon_player_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Player URL'),
    '#description' => t('The URL for the Publizon player.'),
    '#default_value' => variable_get('publizon_player_url', 'https://play.pubhub.dk'),
    '#required' => TRUE,
  );

  $form['publizon']['settings']['publizon_reader_stream_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Reader stream URL'),
    '#description' => t('The URL for the Publizon reader stream.'),
    '#default_value' => variable_get('publizon_reader_stream_url', 'https://streaming.pubhub.dk'),
    '#required' => TRUE,
  );

  $form['publizon']['settings']['publizon_reader_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Reader URL'),
    '#description' => t('The URL for the Publizon reader.'),
    '#default_value' => variable_get('publizon_reader_url', 'https://reader.pubhub.dk'),
    '#required' => TRUE,
  );

  $form['publizon']['settings']['publizon_reader_version'] = array(
    '#type' => 'textfield',
    '#title' => t('Reader version'),
    '#description' => t('The version of the Publizon reader to use.'),
    '#default_value' => variable_get('publizon_reader_version', '1.5.0'),
    '#required' => TRUE,
  );

  $form['publizon']['settings']['publizon_logging'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable logging'),
    '#default_value' => variable_get('publizon_logging', 0),
  );

  // Add libraries fieldset.
  $form['publizon']['libraries'] = array(
    '#type' => 'fieldset',
    '#title' => t('Library configuration'),
    '#description' => t('When users login they are mapped to a given library, which needs to have there own Publizon settings to sent to the web-service.'),
    '#prefix' => '<div id="libraries-fieldset-wrapper">',
    '#suffix' => '</div>',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );

  // Find the number of elements (libraries) to show, base on the current state.
  $libraries = variable_get('publizon_libraries', array());
  $num_libraries = count($libraries) ? count($libraries) : 1;
  if (isset($form_state['values']['publizon']['num_libraries'])) {
    $num_libraries = $form_state['values']['publizon']['num_libraries'];
  }

  // Store the number of libraries to ahah callbacks (add one more).
  $form['publizon']['num_libraries'] = array(
    '#type' => 'value',
    '#value' => $num_libraries,
  );

  // Add form elements.
  for ($i = 0; $i < $num_libraries; $i++) {
    $library = array_shift($libraries);

    // Only show titles for the fields for every 20th row.
    $titles = $i % 20 == 0;

    $form['publizon']['libraries']['l'][$i] = array(
      '#type' => 'fieldset',
      '#title' => t('Library information'),
      '#collapsible' => FALSE,
      '#collapsed' => FALSE,
      '#attributes' => array(
        'class' => array('library-settings'),
      ),
    );

    $form['publizon']['libraries']['l'][$i]['retailer_id'] = array(
      '#type' => 'textfield',
      '#title' => $titles ? t('Retailer ID') : '',
      '#size' => 6,
      '#default_value' => isset($library['retailer_id']) ? $library['retailer_id'] : '',
    );

    $form['publizon']['libraries']['l'][$i]['unilogin_id'] = array(
      '#type' => 'textfield',
      '#title' => $titles ? t('Unilogin ID') : '',
      '#size' => 6,
      '#default_value' => isset($library['unilogin_id']) ? $library['unilogin_id'] : '',
    );

    $form['publizon']['libraries']['l'][$i]['retailer_key_code'] = array(
      '#type' => 'textfield',
      '#title' => $titles ? t('Retailer key code') : '',
      '#size' => 20,
      '#default_value' => isset($library['retailer_key_code']) ? $library['retailer_key_code'] : '',
    );

    $form['publizon']['libraries']['l'][$i]['library_name'] = array(
      '#type' => 'textfield',
      '#title' => $titles ? t('Library name') : '',
      '#size' => 32,
      '#default_value' => isset($library['library_name']) ? $library['library_name'] : '',
    );

    $form['publizon']['libraries']['l'][$i]['subscribed_users'] = array(
      '#type' => 'textfield',
      '#title' => $titles ? t('Number of users') : '',
      '#size' => 6,
      '#default_value' => isset($library['subscribed_users']) ? $library['subscribed_users'] : '',
    );
  }

  $form['publizon']['libraries']['spacer'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="spacer"></div>',
  );

  $form['publizon']['libraries']['add'] = array(
    '#type' => 'submit',
    '#value' => t('Add more'),
    '#submit' => array('publizon_settings_form_add_library'),
    '#name' => 'add-library',
    '#ajax' => array(
      'callback' => 'publizon_settings_form_libraries_callback',
      'wrapper' => 'libraries-fieldset-wrapper',
    ),
    '#prefix' => '<div class="add">',
  );

  $form['publizon']['libraries']['add_count'] = array(
    '#type' => 'textfield',
    '#size' => 1,
    '#default_value' => isset($form_state['values']['publizon']['libraries']['add_count']) ? $form_state['values']['publizon']['libraries']['add_count'] : 1,
    '#suffix' => '</div>',
  );

  if ($num_libraries > 1) {
    $form['publizon']['libraries']['remove'] = array(
      '#type' => 'submit',
      '#value' => t('Remove last'),
      '#submit' => array('publizon_settings_form_remove_library'),
      '#name' => 'remove-library',
      '#ajax' => array(
        'callback' => 'publizon_settings_form_libraries_callback',
        'wrapper' => 'libraries-fieldset-wrapper',
      ),
    );
  }

  // Add messages fieldset.
  $form['publizon']['error_messages'] = array(
    '#type' => 'fieldset',
    '#title' => t('Custom error messages'),
    '#description' => t('Customize the error messages for loan/reservation/bookmark.'),
    '#prefix' => '<div id="error-messages-fieldset-wrapper">',
    '#suffix' => '</div>',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  // Find the number of elements (messages) to show, based on the current state.
  $error_messages = variable_get('publizon_error_messages', array());
  $num_error_messages = count($error_messages) ? count($error_messages) : 1;
  if (isset($form_state['values']['publizon']['num_error_messages'])) {
    $num_error_messages = $form_state['values']['publizon']['num_error_messages'];
  }

  // Store the number of libraries to ahah callbacks (add one more).
  $form['publizon']['num_error_messages'] = array(
    '#type' => 'value',
    '#value' => $num_error_messages,
  );

  $defaults = array(
    'value' => '',
    'format' => 'ding_wysiwyg',
  );
  // Add form elements.
  $no_default = TRUE;
  // If there is no default error message, add one.
  if (!isset($error_messages[-1])) {
    $num_error_messages++;
  }

  for ($i = 0; $i < $num_error_messages; $i++) {
    $error_message = array_shift($error_messages);
    $default = $error_message ? $error_message['error_code'] == -1 : ($i == $num_error_messages - 1 && $no_default);
    $no_default = $no_default ? ($default ? FALSE : TRUE) : FALSE;

    $form['publizon']['error_messages']['e'][$i] = array(
      '#type' => 'fieldset',
      '#title' => $default ? t('Default error') : (t('Error @code', array('@code' => $error_message ? $error_message['error_code'] : '[new]'))),
      '#collapsible' => TRUE,
      '#collapsed' => (bool) $error_message,
      '#attributes' => array(
        'class' => array('error-message-settings'),
      ),
    );

    $form['publizon']['error_messages']['e'][$i]['error_code'] = array(
      '#type' => 'textfield',
      '#title' => t('Code'),
      '#size' => 6,
      '#default_value' => $default ? '-1' : ($error_message ? $error_message['error_code'] : ''),
      '#access' => !$default,
    );

    $form['publizon']['error_messages']['e'][$i]['show_bookmark'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show bookmark button'),
      '#default_value' => $error_message ? $error_message['show_bookmark'] : '',
    );

    $form['publizon']['error_messages']['e'][$i]['show_reserve'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show reserve button'),
      '#default_value' => $error_message ? $error_message['show_bookmark'] : '',
    );

    $message = $error_message ? $error_message['error_text'] : $defaults;
    $form['publizon']['error_messages']['e'][$i]['error_text'] = array(
      '#type' => 'text_format',
      '#title' => t('Error message'),
      '#size' => 50,
      '#default_value' => $message['value'],
      '#format' => $message['format'],
    );
  }

  $form['publizon']['error_messages']['spacer'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="spacer"></div>',
  );

  $form['publizon']['error_messages']['add'] = array(
    '#type' => 'submit',
    '#value' => t('Add more'),
    '#submit' => array('publizon_settings_form_add_error_message'),
    '#name' => 'add-error-message',
    '#ajax' => array(
      'callback' => 'publizon_settings_form_error_messages_callback',
      'wrapper' => 'error-messages-fieldset-wrapper',
    ),
    '#prefix' => '<div class="add">',
  );

  $form['publizon']['error_messages']['add_count'] = array(
    '#type' => 'textfield',
    '#size' => 1,
    '#default_value' => isset($form_state['values']['publizon']['error_messages']['add_count']) ? $form_state['values']['publizon']['error_messages']['add_count'] : 1,
    '#suffix' => '</div>',
  );

  if ($num_error_messages > 1) {
    $form['publizon']['error_messages']['remove'] = array(
      '#type' => 'submit',
      '#value' => t('Remove last'),
      '#submit' => array('publizon_settings_form_remove_error_message'),
      '#name' => 'remove-error-message',
      '#ajax' => array(
        'callback' => 'publizon_settings_form_error_messages_callback',
        'wrapper' => 'error-messages-fieldset-wrapper',
      ),
    );
  }

  // Make the form look like at system form.
  $form = system_settings_form($form);

  // We will handle submit ourself.
  $form['#submit'] = array('publizon_settings_form_submit');

  return $form;
}

/**
 * Callback for adding one more library.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state at submit.
 */
function publizon_settings_form_add_library($form, &$form_state) {
  $form_state['values']['publizon']['num_libraries'] = $form_state['values']['publizon']['num_libraries'] + $form_state['values']['publizon']['libraries']['add_count'];
  $form_state['rebuild'] = TRUE;
}

/**
 * Callback for removing a library.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state at submit.
 */
function publizon_settings_form_remove_library($form, &$form_state) {
  if ($form_state['values']['publizon']['num_libraries'] > 1) {
    $form_state['values']['publizon']['num_libraries']--;
  }
  $form_state['rebuild'] = TRUE;
}

/**
 * Ajax callback for libraries altering.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state at submit.
 */
function publizon_settings_form_libraries_callback($form, $form_state) {
  return $form['publizon']['libraries'];
}

/**
 * Callback for adding one more error message.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state at submit.
 */
function publizon_settings_form_add_error_message($form, &$form_state) {
  $form_state['values']['publizon']['num_error_messages'] = $form_state['values']['publizon']['num_error_messages'] + $form_state['values']['publizon']['error_messages']['add_count'];
  $form_state['rebuild'] = TRUE;
}

/**
 * Callback for removing an error message.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state at submit.
 */
function publizon_settings_form_remove_error_message($form, &$form_state) {
  if ($form_state['values']['publizon']['num_error_messages'] > 1) {
    $form_state['values']['publizon']['num_error_messages']--;
  }
  $form_state['rebuild'] = TRUE;
}

/**
 * Ajax callback for error messages altering.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state at submit.
 */
function publizon_settings_form_error_messages_callback($form, $form_state) {
  return $form['publizon']['error_messages'];
}

/**
 * Validate the publizon settings form.
 *
 * This makes sure that if something is entered in one of the fields,
 * every field for that line should be entered.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state at submit.
 */
function publizon_settings_form_validate($form, &$form_state) {
  // Do not validate when we are trying to remove an element.
  if ($form_state['triggering_element']['#name'] == 'remove-library' || $form_state['triggering_element']['#name'] == 'remove-error-message') {
    return;
  }

  foreach ($form_state['values']['publizon']['libraries']['l'] as $i => $library) {
    $name = $library['library_name'];
    $id   = $library['retailer_id'];
    $code = $library['retailer_key_code'];

    // If one of them is filled out, we have to get them all.
    // If none are filled out, it will just be ignored.
    if (!empty($name) || !empty($id) || !empty($code)) {
      if (empty($name)) {
        form_set_error('publizon][libraries][l][' . $i . '][library_name', t('Library name must be specified!'));
      }
      if (empty($id)) {
        form_set_error('publizon][libraries][l][' . $i . '][retailer_id', t('Library retailer id must be specified!'));
      }
      if (empty($code)) {
        form_set_error('publizon][libraries][l][' . $i . '][retailer_key_code', t('Library retailer key code must be specified!'));
      }
    }
  }
}

/**
 * Submit settings form for Publizon.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state at submit.
 */
function publizon_settings_form_submit($form, &$form_state) {
  $libraries = array();
  // Go through the libraries submitted.
  foreach ($form_state['values']['publizon']['libraries']['l'] as $library) {
    // Because of the validation function above, if one of
    // the fields are empty, we can assume that they all are.
    // Ignore such libraries.
    if (empty($library['library_name'])) {
      continue;
    }

    // Save this one.
    $libraries[$library['retailer_id']] = $library;
  }

  variable_set('publizon_libraries', $libraries);
  // For all other values that the libraries, just save it as a variable.
  foreach ($form_state['values']['publizon']['settings'] as $name => $value) {
    variable_set($name, $value);
  }

  $error_messages = array();
  // Go through the libraries submitted.
  foreach ($form_state['values']['publizon']['error_messages']['e'] as $error_message) {
    // If no error code is defined, do not save it.
    if (empty($error_message['error_code'])) {
      continue;
    }

    // Save this one.
    $error_messages[$error_message['error_code']] = $error_message;
  }

  variable_set('publizon_error_messages', $error_messages);

  drupal_set_message(t('The configuration options have been saved.'));
}
