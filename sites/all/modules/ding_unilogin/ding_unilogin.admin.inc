<?php
/**
 * @file
 * Implements the administration UI for the module.
 */

/**
 * UNI•Login settings form.
 */
function ding_unilogin_admin_settings_form($form, &$form_state) {
  // Settings for the basic login service.
  $form['login'] = array(
    '#type' => 'fieldset',
    '#title' => t('UNI•Login'),
    '#description' => t('Settings for the base login service.'),
  );

  $form['login']['ding_unilogin_id'] = array(
    '#type' => 'textfield',
    '#title' => t('UNI•Login ID'),
    '#description' => t('The UNI•Login ID. Leave empty to disable UNI•Login.'),
    '#default_value' => variable_get('ding_unilogin_id', ''),
  );

  $form['login']['ding_unilogin_secret'] = array(
    '#type' => 'textfield',
    '#title' => t('UNI•Login shared secret'),
    '#description' => t('The shared secret used to calculate hashes.'),
    '#default_value' => variable_get('ding_unilogin_secret', ''),
  );

  // Settings for WS service general access.
  $form['ws'] = array(
    '#type' => 'fieldset',
    '#title' => t('UNI•Login WS common'),
    '#description' => t('Common settings for the additional information web services.'),
  );

  $form['ws']['ding_unilogin_ws_user'] = array(
    '#type' => 'textfield',
    '#title' => t('UNI•Login webservice user ID'),
    '#default_value' => variable_get('ding_unilogin_ws_user', ''),
  );

  $form['ws']['ding_unilogin_ws_pass'] = array(
    '#type' => 'textfield',
    '#title' => t('UNI•Login webservice password'),
    '#default_value' => variable_get('ding_unilogin_ws_pass', ''),
  );

  // Settings for auth settings.
  $form['auth'] = array(
    '#type' => 'fieldset',
    '#title' => t('UNI•Login Auth'),
    '#description' => t('Settings for the authenticaion web services.'),
  );

  $form['auth']['ding_unilogin_auth_context'] = array(
    '#type' => 'textfield',
    '#title' => t('Context'),
    '#default_value' => variable_get('ding_unilogin_auth_context', ''),
    '#description' => t('The WS05 context to check for access in.'),
  );

  $form['auth']['ding_unilogin_auth_project'] = array(
    '#type' => 'textfield',
    '#title' => t('Project'),
    '#default_value' => variable_get('ding_unilogin_auth_project', ''),
    '#description' => t('The WS05 project to check for access to.'),
  );

  // Municipality mapping.
  $form['mapping'] = array(
    '#type' => 'fieldset',
    '#title' => t('UNI•Login Municipality mapping'),
    '#description' => t('Mapping of UNI•Login municipality IDs to Publizon retailer IDs .'),
  );

  $mapping = '';
  foreach (variable_get('ding_unilogin_municipality_mapping', array()) as $unilogin_id => $publizon_id) {
    $mapping .= $unilogin_id . '|' . $publizon_id;
  }
  $form['mapping']['ding_unilogin_municipality_mapping'] = array(
    '#type' => 'textarea',
    '#title' => t('Mapping'),
    '#default_value' => $mapping,
    '#description' => t('Municipalities, each on its own line, in <em>unilogin_id|retailer_id</em> format.'),
  );

  // Make the form look like at system form.
  $form = system_settings_form($form);

  return $form;
}

/**
 * Validation for the settings form.
 */
function ding_unilogin_admin_settings_form_validate($form, &$form_state) {
  $publizon_libraries = variable_get('publizon_libraries', array());
  $municipalities = array();
  $lines = explode(
    "\n",
    trim($form_state['values']['ding_unilogin_municipality_mapping'])
  );

  foreach ($lines as $line) {
    // Ignore empty lines.
    if (trim($line) == '') {
      continue;
    }

    if (substr_count($line, '|') != 1) {
      form_error(
        $form['mapping']['ding_unilogin_municipality_mapping'],
        t('Invalid line @line', array('@line' => $line))
      );
    }
    else {
      list($unilogin_id, $retailer_id) = explode('|', $line);
      if (isset($publizon_libraries[(int) $retailer_id])) {
        $municipalities[$unilogin_id] = $retailer_id;
      }
      else {
        form_error(
          $form['mapping']['ding_unilogin_municipality_mapping'],
          t('Unknown retailer_id @id (see <a heref=@href>Publizon settings</a> for the configured retailer_ids).', array(
            '@id' => $retailer_id,
            '@href' => url('admin/config/ding/provider/publizon'),
          ))
        );
      }
    }
  }

  form_set_value($form['mapping']['ding_unilogin_municipality_mapping'], $municipalities, $form_state);
}
