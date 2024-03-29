<?php

/**
 * @file
 * Settings for publizon.
 */

/**
 * Publizon settings form.
 *
 * Administration form for the configuration of the communication with
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
function publizon_settings_form(array $form, array &$form_state) {
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

  $form['publizon']['settings']['publizon_reader_order_id_field'] = array(
    '#type' => 'select',
    '#options' => array(
      'retailer_order_number' => 'Retailer order number',
      'internal_order_number' => 'Internal order number',
    ),
    '#title' => t('Order id field'),
    '#description' => t('The field to use for order id in the reader.'),
    '#default_value' => variable_get('publizon_reader_order_id_field'),
    '#required' => TRUE,
  );

  $form['publizon']['settings']['publizon_reader_version'] = array(
    '#type' => 'textfield',
    '#title' => t('Reader version'),
    '#description' => t('The version of the Publizon reader to use.'),
    '#default_value' => variable_get('publizon_reader_version', '2.1.0'),
    '#required' => TRUE,
  );

  $form['publizon']['settings']['publizon_reader_environment'] = array(
    '#type' => 'select',
    '#options' => array(
      'live' => 'live',
      'qa' => 'qa',
    ),
    '#title' => t('Reader environment'),
    '#description' => t('The environment of the Publizon reader to use.'),
    '#default_value' => variable_get('publizon_reader_environment', 'live'),
    '#required' => TRUE,
  );

  $form['publizon']['settings']['publizon_reader_search_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Search enabled'),
    '#default_value' => variable_get('publizon_reader_search_enabled', FALSE),
  );

  $form['publizon']['settings']['publizon_reader_annotations_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Annotations enabled'),
    '#default_value' => variable_get('publizon_reader_annotations_enabled', FALSE),
  );

  $form['publizon']['settings']['publizon_reader_content_selection_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Content selection enabled'),
    '#default_value' => variable_get('publizon_reader_content_selection_enabled', FALSE),
  );

  $form['publizon']['settings']['publizon_reader_mouse_swipe_navigation_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Mouse swipe navigation enabled'),
    '#default_value' => variable_get('publizon_reader_mouse_swipe_navigation_enabled', FALSE),
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

  $libraries = publizon_get_libraries();
  // Add an empty one for adding.
  $libraries[] = new PublizonConfiguredLibrary();

  // Add form elements.
  $i = 1;
  while ($library = array_shift($libraries)) {
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
      '#title' => t('Retailer ID'),
      '#size' => 6,
      '#disabled' => empty($library->retailer_id) ? FALSE : TRUE,
      '#default_value' => $library->retailer_id,
    );

    $form['publizon']['libraries']['l'][$i]['municipality_id'] = array(
      '#type' => 'textfield',
      '#title' => t('Municipality ID'),
      '#size' => 6,
      '#default_value' => $library->municipality_id,
    );

    $form['publizon']['libraries']['l'][$i]['unilogin_id'] = array(
      '#type' => 'textfield',
      '#title' => t('Unilogin ID'),
      '#size' => 6,
      '#default_value' => $library->unilogin_id,
    );

    $form['publizon']['libraries']['l'][$i]['retailer_key_code'] = array(
      '#type' => 'textfield',
      '#title' => t('Retailer key code'),
      '#size' => 20,
      '#default_value' => $library->retailer_key_code,
    );

    $form['publizon']['libraries']['l'][$i]['library_name'] = array(
      '#type' => 'textfield',
      '#title' => t('Library name'),
      '#size' => 32,
      '#default_value' => $library->library_name,
    );

    $form['publizon']['libraries']['l'][$i]['subscribed_users'] = array(
      '#type' => 'textfield',
      '#title' => t('Number of users'),
      '#size' => 6,
      '#default_value' => $library->subscribed_users,
    );

    $form['publizon']['libraries']['l'][$i]['delete'] = array(
      '#markup' => empty($library->retailer_id) ? '' : l(t('delete'),
                     'admin/config/ding/provider/publizon/' .
                     $library->retailer_id . '/delete'),
      '#title' => t('Operations'),
    );

    $i++;
  }

  $municipality_aliases = variable_get('publizon_municipality_aliases', array());

  $form['publizon']['municipality_aliases'] = array(
    '#type' => 'textarea',
    '#title' => t('Municipality aliases'),
    '#description' => t("Format: <code>«municipality id»: «alias id»</code>; one pr. line, e.g. <pre>451: 87\n42: 123</pre>"),
    '#default_value' => _publizon_admin_serialize_municipality_aliases($municipality_aliases),
  );

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

  $form['#theme'] = 'publizon_settings_form';

  // Make the form look like at system form.
  $form = system_settings_form($form);

  // We will handle submit ourself.
  $form['#submit'] = array('publizon_settings_form_submit');

  return $form;
}

/**
 * Returns HTML for the Publizon settings form.
 *
 * @ingroup themeable
 */
function theme_publizon_settings_form($variables) {
  $form = $variables['form'];

  $header = array();
  $rows = array();
  $first_row = TRUE;
  foreach (element_children($form['publizon']['libraries']['l']) as $key) {
    $row = array();
    foreach (element_children($form['publizon']['libraries']['l'][$key]) as $field) {
      if ($first_row) {
        $header[] = $form['publizon']['libraries']['l'][$key][$field]['#title'];
      }
      $form['publizon']['libraries']['l'][$key][$field]['#title_display'] = 'invisible';
      $row[] = drupal_render($form['publizon']['libraries']['l'][$key][$field]);
    }
    $rows[] = $row;
    $first_row = FALSE;
  }
  $form['publizon']['libraries']['#children'] = theme('table', array('header' => $header, 'rows' => $rows));

  // Render the the from.
  return drupal_render_children($form);
}

/**
 * Callback for adding one more error message.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state at submit.
 */
function publizon_settings_form_add_error_message(array $form, array &$form_state) {
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
function publizon_settings_form_remove_error_message(array $form, array &$form_state) {
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
function publizon_settings_form_error_messages_callback(array $form, array $form_state) {
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
function publizon_settings_form_validate(array $form, array &$form_state) {
  // Do not validate when we are trying to remove an element.
  if ($form_state['triggering_element']['#name'] == 'remove-library' || $form_state['triggering_element']['#name'] == 'remove-error-message') {
    return;
  }

  $seen_ids = array();
  foreach ($form_state['values']['publizon']['libraries']['l'] as $i => $library) {
    $name = $library['library_name'];
    $id   = $library['retailer_id'];
    $code = $library['retailer_key_code'];

    // If one of them is filled out, we have to get them all.
    // If none are filled out, it will just be ignored.
    if (!empty($name) || !empty($id) || !empty($code)) {
      if (empty($name)) {
        form_set_error('publizon][libraries][l][' . $i . '][library_name', t('Library name must be specified.'));
      }
      if (empty($id)) {
        form_set_error('publizon][libraries][l][' . $i . '][retailer_id', t('Library retailer id must be specified.'));
      }
      if (empty($code)) {
        form_set_error('publizon][libraries][l][' . $i . '][retailer_key_code', t('Library retailer key code must be specified.'));
      }
      if (isset($seen_ids[$id])) {
        form_set_error('publizon][libraries][l][' . $i . '][retailer_id', t('Library retailer id must be unique.'));
      }
    }
    $seen_ids[$id] = TRUE;
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
function publizon_settings_form_submit(array $form, array &$form_state) {
  // Go through the libraries submitted.
  foreach ($form_state['values']['publizon']['libraries']['l'] as $library) {
    // Because of the validation function above, if one of
    // the fields are empty, we can assume that they all are.
    // Ignore such libraries.
    if (empty($library['library_name'])) {
      continue;
    }

    // Save this one.
    publizon_library_save(PublizonConfiguredLibrary::fromArray($library));
  }

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

  $municipality_aliases = _publizon_admin_deserialize_municipality_aliases($form_state['values']['publizon']['municipality_aliases']);
  variable_set('publizon_municipality_aliases', $municipality_aliases);

  drupal_set_message(t('The configuration options have been saved.'));
}

/**
 * Delete library form.
 */
function publizon_delete_library_form($form, &$form_state, $library) {
  $form['retailer_id'] = array(
    '#type' => 'value',
    '#value' => $library->retailer_id,
  );
  return confirm_form($form,
                      t('Are you sure you want to delete the "@name" library?', array('@name' => $library->library_name)),
                      'admin/config/ding/provider/publizon',
                      NULL,
                      t('Delete')
  );
}

/**
 * Submit handler for delete form.
 */
function publizon_delete_library_form_submit($form, &$form_state) {
  db_delete('publizon_libraries')
    ->condition('retailer_id', $form_state['values']['retailer_id'])
    ->execute();

  $form_state['redirect'] = 'admin/config/ding/provider/publizon';
}

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

/**
 * Submit handler for Publizon settings form.
 */
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

/**
 * Serialize municipality aliases.
 *
 * Example:
 *
 *   [
 *     87 => 42,
 *    123 => 256,
 *   ]
 *
 * is serialized as
 *
 *   87: 42
 *   123: 256
 *
 * @param array $aliases
 *   The aliases (map from id to alias).
 *
 * @return string
 *   The serialized aliases.
 */
function _publizon_admin_serialize_municipality_aliases(array $aliases) {
  $items = [];

  foreach ($aliases as $id => $alias) {
    $items[] = sprintf('%s: %s', $id, $alias);
  }

  return implode(PHP_EOL, $items);
}

/**
 * Deserialize municipality aliases.
 *
 * Example:
 *
 *   87: 42
 *   123: 256
 *   87: 23
 *
 * (note duplicated key 87) is deserialized as
 *
 *   [
 *     87 => 23,
 *    123 => 256,
 *   ]
 *
 * @param string $serialized
 *   The serialized aliases.
 *
 * @return array
 *   The deserialized aliases.
 */
function _publizon_admin_deserialize_municipality_aliases(string $serialized) {
  if (preg_match_all('/^\s*(?<id>\d+)\s*:\s*(?<alias>\d+)\s*$/m', $serialized, $matches)) {
    return array_combine($matches['id'], $matches['alias']);
  }

  return [];
}
