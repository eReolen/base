<?php
/**
 * @file
 * Defines the administration interface for configuring communication with the
 * Pulizon web-service.
 */

/**
 * Administration form for the configureation of the communication with
 * publizon.
 *
 * @return array $form
 */
function publizon_settings_form($form, &$form_state) {
  $form['#tree'] = TRUE;
  drupal_add_css(drupal_get_path('module', 'publizon') . '/css/settings.css');

  $form['publizon']['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Default settings'),
    '#description' => t('These settings are used to communicate with the publizon web-service, when no user is logged in. They are required to be able to fetch information about products (eg. covers and basic information from Publizon)'),
    '#collapsible' => TRUE,
    '#collapsed' => (boolean)variable_get('publizon_base_url', FALSE),
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

  $form['publizon']['settings']['publizon_logging'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable logging'),
    '#default_value' => variable_get('publizon_logging', 0),
  );

  // Add libraries fieldset.
  $form['publizon']['libraries'] = array(
    '#type' => 'fieldset',
    '#title' => 'Library configuration',
    '#description' => 'When users login they are mapped to a given library, which needs to have there own Publizon settings to sent to the web-service.',
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
    $form['publizon']['libraries'][$i] = array(
      '#type' => 'fieldset',
      '#title' => 'Library information',
      '#collapsible' => FALSE,
      '#collapsed' => FALSE,
      '#attributes' => array(
        'class' => array('library-settings'),
      ),
    );

    $form['publizon']['libraries'][$i]['retailer_id'] = array(
      '#type' => 'textfield',
      '#title' => t('Retailer ID'),
      '#size' => 6,
      '#default_value' => count($libraries) ? $libraries[$i]['retailer_id'] : '',
    );

    $form['publizon']['libraries'][$i]['retailer_key_code'] = array(
      '#type' => 'textfield',
      '#title' => t('Retailer key code'),
      '#size' => 20,
      '#default_value' => count($libraries) ? $libraries[$i]['retailer_key_code'] : '',
    );

    $form['publizon']['libraries'][$i]['library_name'] = array(
      '#type' => 'textfield',
      '#title' => 'Library name',
      '#size' => 32,
      '#default_value' => count($libraries) ? $libraries[$i]['library_name'] : '',
    );
  }

  $form['publizon']['libraries']['spacer'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="spacer"></div>',
  );

  $form['publizon']['libraries']['add'] = array(
    '#type' => 'submit',
    '#value' => t('Add one more'),
    '#submit' => array('publizon_settings_form_add_library'),
    '#name' => 'add',
    '#ajax' => array(
      'callback' => 'publizon_settings_form_libraries_callback',
      'wrapper' => 'libraries-fieldset-wrapper',
    ),
  );
  if ($num_libraries > 1) {
    $form['publizon']['libraries']['remove'] = array(
      '#type' => 'submit',
      '#value' => t('Remove one'),
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

  return $form;
}

/**
 * Callback for adding one more library.
 */
function publizon_settings_form_add_library($form, &$form_state) {
  $form_state['values']['publizon']['num_libraries']++;
  $form_state['rebuild'] = TRUE;
}

/**
 * Callback for removing a library.
 */
function publizon_settings_form_remove_library($form, &$form_state) {
  if ($form_state['values']['publizon']['num_libraries'] > 1) {
    $form_state['values']['publizon']['num_libraries']--;
  }
  $form_state['rebuild'] = TRUE;
}

/**
 * Ajax callback for libraries altering.
 */
function publizon_settings_form_libraries_callback($form, $form_state) {
  return $form['publizon']['libraries'];
}

function publizon_settings_form_validate($form, &$form_state) {
  // Do not validate when we are trying to remove an element.
  if ($form_state['triggering_element']['#name'] == 'remove') {
    return;
  }

  foreach ($form_state['values']['publizon']['libraries'] as $i => $library) {
    $name = $library['library_name'];
    $id   = $library['retailer_id'];
    $code = $library['retailer_key_code'];

    // If one of them is filled out, we have to get them all.
    // If none are filled out, it will just be ignored.
    if (!empty($name) || !empty($id) || !empty($code)) {
      if (empty($name)) {
        form_set_error('publizon][libraries][' . $i . '][library_name', 'Library name must be specified!');
      }
      if (empty($id)) {
        form_set_error('publizon][libraries][' . $i . '][retailer_id', 'Library retailer id must be specified!');
      }
      if (empty($code)) {
        form_set_error('publizon][libraries][' . $i . '][retailer_key_code', 'Library retailer key code must be specified!');
      }
    }
  }
}

/**
 * Submit settings form for Publizon
 */
function publizon_settings_form_submit($form, &$form_state) {
  foreach ($form_state['values']['publizon'] as $name => $value) {
    if ($name == 'libraries') {
      $libraries = array();
      // Go through the libraries submitted.
      foreach ($value as $library) {
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
    }
    else {
      // For all other values that the libraries, just save it as a variable.
      variable_set($name, $value);
    }
  }
}
