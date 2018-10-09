<?php
/**
 * @file
 * Defines the administration interface for configuring overdrive
 */

/**
 * Overdrive settings form.
 *
 * @param array $form
 *   The form input.
 * @param array $form_state
 *   The state of the form.
 *
 * @return array
 *   The finished form.
 */
function overdrive_settings_form($form, &$form_state) {
  $default = array(
    'value' => '',
    'format' => 'ding_wysiwyg',
  );
  $default = variable_get('overdrive_information_text', $default);

  $form['overdrive_information_text'] = array(
    '#type' => 'text_format',
    '#title' => t('Information text'),
    '#description' => t('The text to display before begin redirected to overdrive.'),
    '#default_value' => $default['value'],
    '#format' => $default['format'],
  );

  // Make the form look like at system form.
  $form = system_settings_form($form);

  return $form;
}

/**
 * Mappings form callback.
 */
function overdrive_mappings_form($form, &$form_state) {
  $form['#tree'] = TRUE;
  $form['#attached'] = array(
    'css' => array(
      drupal_get_path('module', 'overdrive') . '/css/overdrive.admin.css',
    )
  );

  if (!empty($form_state['input']['container'])) {
    $containers = $form_state['input']['container'];
  }
  else {
    $containers = overdrive_triggers_load();
  }

  if (isset($form_state['clicked_button'])) {
    if ($form_state['clicked_button']['#value'] == t('Remove')) {
      unset($containers[$form_state['clicked_button']['#name']]);
    }

    if ($form_state['clicked_button']['#value'] == t('Add another')) {
      $containers[] = array(
        'search_trigger' => '',
        'search_query' => '',
      );
    }
  }

  $form['container'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'overdrive-mappings'
      ),
    ),
  );

  foreach ($containers as $i => $default) {
    $default = isset($default['wrapper']) ? $default['wrapper'] : $default;
    $form['container'][$i] = overdrive_mappings_form_element($i, $default);
  }

  $form['add_item'] = array(
    '#type' => 'submit',
    '#value' => t('Add another'),
    '#submit' => array('overdrive_mappings_form_rebuild'),
    '#attributes' => array(
      'class' => array(
        'btn-add-another'
      ),
    ),
  );

  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  if (!empty($_POST) && form_get_errors()) {
    drupal_set_message(t('The settings have not been saved because of the errors.'), 'error');
  }

  $form['#theme'] = 'system_settings_form';
  $form['#submit'][] = 'overdrive_mappings_form_submit';

  return $form;
}

/**
 * Mappings form element construct helper.
 *
 * @param $i
 *   The form index.
 * @param $default
 *   The default values.
 *
 * @return array
 *   The form element.
 */
function overdrive_mappings_form_element($i, $default) {
  $form['wrapper'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'mapping',
        ($i % 2 == 0 ? 'odd' : 'even'),
      ),
    ),
  );

  $form['wrapper']['tid'] = array(
    '#type' => 'hidden',
    '#value' => isset($default['tid']) ? $default['tid'] : -1,
  );

  $form['wrapper']['search_trigger'] = array(
    '#type' => 'textfield',
    '#title' => t('Trigger'),
    '#default_value' => isset($default['search_trigger']) ? $default['search_trigger'] : '',
    '#size' => 40,
    '#required' => TRUE,
  );

  $form['wrapper']['search_query'] = array(
    '#type' => 'textfield',
    '#title' => t('query'),
    '#default_value' => isset($default['search_query']) ? $default['search_query'] : '',
    '#size' => 60,
    '#required' => TRUE,
  );

  $form['wrapper']['remove_item'] = array(
    '#type' => 'submit',
    '#value' => t('Remove'),
    '#name' => $i,
    '#submit' => array('overdrive_mappings_form_remove'),
    '#limit_validation_errors' => array(),
  );

  return $form;
}

/**
 * Remove item form action callback.
 */
function overdrive_mappings_form_remove($form, &$form_state) {
  // Remove database field.
  if (isset($form_state['clicked_button'])) {
    if ($form_state['clicked_button']['#value'] == t('Remove')) {
      $id = $form_state['clicked_button']['#name'];
      $tid = $form_state['input']['container'][$id]['wrapper']['tid'];
      if ($tid !== -1) {
        db_delete('overdrive_triggers')
          ->condition('tid', $tid)
          ->execute();
      }
    }
  }

  $form_state['rebuild'] = TRUE;
}

/**
 * Add one more form callback.
 */
function overdrive_mappings_form_rebuild($form, &$form_state) {
  $form_state['rebuild'] = TRUE;
}

/**
 * Mappings form submit handler.
 */
function overdrive_mappings_form_submit($form, &$form_state) {
  $triggers = array();
  $values = $form_state['values']['container'];
  foreach ($values as $value) {
    unset($value['wrapper']['remove_item']);
    $triggers[] = $value['wrapper'];
  }

  overdrive_triggers_save($triggers);
}
