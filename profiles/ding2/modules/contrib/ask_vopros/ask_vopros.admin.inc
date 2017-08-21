<?php

/**
 * @file
 * Administrative forms and pages for ask_vopros.
 */

/**
 * Form builder.
 */
function ask_vopros_settings($form, &$form_state) {
  // If ting is configured with an agency id, just use that.
  $agency_id = _ask_vopros_ting_agency_id();
  if (empty($agency_id)) {
    $form['ask_vopros_agency_id'] = array(
      '#type' => 'textfield',
      '#title' => t('Identification'),
      '#default_value' => variable_get('ask_vopros_agency_id', ''),
      '#description' => t('Either a library code in the form of <em>DK-123456</em> or a custom string.'),
    );
  }
  else {
    $form['ask_vopros_agency_id'] = array(
      '#type' => 'item',
      '#title' => t('Identification'),
      '#markup' => check_plain(variable_get('ask_vopros_agency_id', _ask_vopros_ting_agency_id())),
      '#description' => t('This can be overridden with <em>drush vset ask_vopros_agency_id [new value]</em>.'),
    );
  }

  $form['ask_vopros_uri'] = array(
    '#type' => 'textfield',
    '#title' => t('Biblioteksvagten URL'),
    '#default_value' => variable_get('ask_vopros_uri', 'https://adm.biblioteksvagten.dk'),
    '#description' => t('The address of the Biblioteksvagten site to fall back to when local Vopros is closed.'),
  );

  $form['ask_vopros_secondary_uri'] = array(
    '#type' => 'textfield',
    '#title' => t('Vopros URL'),
    '#default_value' => variable_get('ask_vopros_secondary_uri', 'https://adm.biblioteksvagten.dk'),
    '#description' => t('The address of the your own Vopros site to send questions to.'),
  );

  $form['ask_vopros_opening_hours'] = array(
    '#title' => t('Opening hours for local service'),
    '#theme' => 'ask_vopros_opening_hours',
    '#theme_wrappers' => array('form_element'),
    '#description' => t('Local service opening and closing hours for each day of the week, in the format HH:MM. If both opening and closing hours is unset for a given day, the local Vopros is closed on that day.'),
    '#tree' => TRUE,
  );

  $form['ask_vopros_opening_hours']['open'] = array(
    '#theme_wrappers' => array('form_element'),
    '#title' => t('Opens'),
  );

  $form['ask_vopros_opening_hours']['close'] = array(
    '#theme_wrappers' => array('form_element'),
    '#title' => t('Closes'),
  );

  $days = array(
    t('Monday'),
    t('Tuesday'),
    t('Wednesday'),
    t('Thursday'),
    t('Friday'),
    t('Saturday'),
    t('Sunday'),
  );

  $hours = variable_get('ask_vopros_opening_hours', array());
  foreach ($days as $day_num => $name) {
    foreach (array('open', 'close') as $state) {
      $default_value = isset($hours[$state][$day_num]) ?
                     $hours[$state][$day_num] : '';
      $form['ask_vopros_opening_hours'][$state][$day_num] = array(
        '#type' => 'textfield',
        '#title' => $name,
        '#default_value' => $default_value,
        '#size' => 5,
        '#maxlength' => 5,
        '#states' => array(
          'disabled' => array(
            'input[name=ask_vopros_secondary_uri]' => array('value' => ''),
          ),
        ),
      );
    }
  }

  $form['ask_vopros_agency_mail'] = array(
    '#type' => 'textfield',
    '#title' => t('Local E-mail'),
    '#default_value' => variable_get('ask_vopros_agency_mail', variable_get('site_mail', '')),
    '#description' => t('E-mail address which Biblioteksvagten can forward inquiries best answered locally to.'),
  );

  $form['ask_vopros_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Override tab color'),
    '#default_value' => variable_get('ask_vopros_color', ''),
    '#description' => t('Override the tab color. Hex format color in the format #FFFFFF or #CCC. Leave empty for default.'),
    '#size' => 8,
    '#attached' => array(
      // Add Farbtastic color picker.
      'library' => array(
        array('system', 'farbtastic'),
      ),
      'js' => array(
        drupal_get_path('module', 'ask_vopros') . '/js/ask_vopros.admin.js',
      ),
    ),
  );

  $form['ask_vopros_right'] = array(
    '#type' => 'textfield',
    '#title' => t('Override right margin'),
    '#default_value' => variable_get('ask_vopros_right', ''),
    '#description' => t('Right margin of tab, in <number><units> format or a simple 0. Units supported: <em>%</em> (percent) <em>px</em> (pixels) <em>em</em> (font-size) <em>rem</em> (root element font-size). Leave empty for default.'),
  );

  $options = array(
    'chat' => t('Chat'),
    'mail' => t('E-mail'),
    'sms' => t('SMS'),
  );

  $form['ask_vopros_answer_preference'] = array(
    '#type' => 'radios',
    '#title' => t('Default answer method'),
    '#options' => $options,
    '#default_value' => variable_get('ask_vopros_answer_preference', 'mail'),
    '#description' => t('The preferred default answering method. Not all methods may be supported by the server, in which case it chooses its own default.'),
  );

  $options = array(
    'not on' => t('All pages except those listed'),
    'on' => t('Only the listed pages'),
  );

  $form['ask_vopros_visibility_type'] = array(
    '#type' => 'radios',
    '#title' => t('Show block on specific pages'),
    '#options' => $options,
    '#default_value' => variable_get('ask_vopros_visibility_type', 'not on'),
  );

  $description = t("Specify pages by using their paths. Enter one path per line. The '*' character is a wildcard. Example paths are %blog for the blog page and %blog-wildcard for every personal blog. %front is the front page.", array('%blog' => 'blog', '%blog-wildcard' => 'blog/*', '%front' => '<front>'));

  $form['ask_vopros_visibility_pages'] = array(
    '#type' => 'textarea',
    '#title' => '<span class="element-invisible">' . t('Pages') . '</span>',
    '#default_value' => variable_get('ask_vopros_visibility_pages', ''),
    '#description' => $description,
  );

  if ($agency_id) {
    $options = array(
      'external' => TRUE,
      'query' => array(
        'agency_id' => $agency_id,
        'agency_mail' => variable_get('ask_vopros_agency_mail', variable_get('site_mail', '')),
      ),
    );
    $link = url(rtrim(variable_get('ask_vopros_uri', 'https://adm.biblioteksvagten.dk'), '/') . '/embed/ask-question', $options);

    $form['help'] = array(
      '#markup' => t('If you do not want to use the tab, you can always create a simple link to !link which will then be shown in a popup.', array('!link' => $link)),
    );
  }

  return system_settings_form($form);
}

/**
 * Validation handler for settings form.
 */
function ask_vopros_settings_validate($form, &$form_state) {
  if (!empty($form_state['values']['ask_vopros_uri'])) {
    $url = $form_state['values']['ask_vopros_uri'];
    $parsed = parse_url($url);
    if (!$parsed || empty($parsed['host']) || empty($parsed['scheme'])) {
      form_error($form['ask_vopros_uri'], t('Invalid URL.'));
    }
    if ($parsed['scheme'] != 'https') {
      form_error($form['ask_vopros_uri'], t('Service URL must be a HTTPS URL in order to protect the privacy of the users'));
    }
  }

  if (!empty($form_state['values']['ask_vopros_secondary_uri'])) {
    $url = $form_state['values']['ask_vopros_secondary_uri'];
    $parsed = parse_url($url);
    if (!$parsed || empty($parsed['host']) || empty($parsed['scheme'])) {
      form_error($form['ask_vopros_secondary_uri'], t('Invalid URL.'));
    }
    if ($parsed['scheme'] != 'https') {
      form_error($form['ask_vopros_secondary_uri'], t('Service URL must be a HTTPS URL in order to protect the privacy of the users'));
    }
  }

  if (!preg_match('/^(|0|-?\d+(%|px|em|rem))$/', trim($form_state['values']['ask_vopros_right']))) {
    form_error($form['ask_vopros_right'], t('Invalid length'));
  }

  // Validate opening hours.
  for ($day = 0; $day < 7; $day++) {
    foreach (array('open', 'close') as $state) {
      $value = $form_state['values']['ask_vopros_opening_hours'][$state][$day];
      if (empty($value)) {
        $value = NULL;
      }
      elseif (!preg_match('/^(\d{1,2}):(\d{2})$/', $value, $rx) ||
              $rx[1] > 23 || $rx[2] > 59) {
        form_error($form['ask_vopros_opening_hours'][$state][$day], t('Invalid time.'));
      }
    }
  }

  // Fabtastic doesn't update empty fields, so our JS adds an space. Strip it here.
  $color = trim($form_state['values']['ask_vopros_color']);
  form_set_value($form['ask_vopros_color'], $color, $form_state);
  if (!empty($color)) {
    if (!preg_match('/^#([a-f0-9]{3}){1,2}$/iD', $color)) {
      form_error($form['ask_vopros_color'], t('Invalid color.'));
    }
  }
}

/**
 * Renders the opening hours into a table.
 */
function theme_ask_vopros_opening_hours($variables) {
  $rows = array();
  foreach (element_children($variables['elements']) as $state) {
    $row = array();
    $header = array('');
    foreach (element_children($variables['elements'][$state]) as $key) {
      // Copy the label to the header. This avoids having to duplicate the
      // days.
      $header[] = $variables['elements'][$state][$key]['#title'];
      $variables['elements'][$state][$key]['#title_display'] = 'invisible';
      $row[] = drupal_render($variables['elements'][$state][$key]);
    }

    // Prepend the row header, now that the #children of the element has been
    // printed.
    array_unshift($row, drupal_render($variables['elements'][$state]));
    $rows[] = $row;
  }

  return theme('table', array('header' => $header, 'rows' => $rows));
}
