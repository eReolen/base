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

  $form['publizon']['settings']['publizon_retailer_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Retailer ID'),
    '#description' => t("This is the library's identification at publizon, which you should recieve from them."),
    '#default_value' => variable_get('publizon_retailer_id', ''),
    '#required' => TRUE,
  );

  $form['publizon']['settings']['publizon_retailer_key_code'] = array(
    '#type' => 'textfield',
    '#title' => t('Retailer key code'),
    '#description' => t('This is a MD5 hash of the code provided with the retailer ID above.'),
    '#default_value' => variable_get('publizon_retailer_key_code', ''),
    '#required' => TRUE,
  );

  $form['publizon']['settings']['publizon_client_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Client ID'),
    '#description' => t('The client ID to send to publizon.'),
    '#default_value' => variable_get('publizon_client_id', ''),
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
      '#default_value' => $library ? $library['retailer_id'] : '',
    );

    $form['publizon']['libraries']['l'][$i]['retailer_key_code'] = array(
      '#type' => 'textfield',
      '#title' => $titles ? t('Retailer key code') : '',
      '#size' => 20,
      '#default_value' => $library ? $library['retailer_key_code'] : '',
    );

    $form['publizon']['libraries']['l'][$i]['library_name'] = array(
      '#type' => 'textfield',
      '#title' => $titles ? t('Library name') : '',
      '#size' => 32,
      '#default_value' => $library ? $library['library_name'] : '',
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
    '#name' => 'add',
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
      '#name' => 'remove',
      '#ajax' => array(
        'callback' => 'publizon_settings_form_libraries_callback',
        'wrapper' => 'libraries-fieldset-wrapper',
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
  if ($form_state['triggering_element']['#name'] == 'remove') {
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

  drupal_set_message(t('The configuration options have been saved.'));
}
