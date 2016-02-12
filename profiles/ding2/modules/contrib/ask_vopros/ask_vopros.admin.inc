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
    '#title' => t('Vopros URL'),
    '#default_value' => variable_get('ask_vopros_uri', 'https://adm.biblioteksvagten.dk'),
    '#description' => t('The address of the Vopros site to send the question to.'),
  );

  $form['ask_vopros_agency_mail'] = array(
    '#type' => 'textfield',
    '#title' => t('Local E-mail'),
    '#default_value' => variable_get('ask_vopros_agency_mail', variable_get('site_mail', '')),
    '#description' => t('E-mail address which Biblioteksvagten can forward inquiries best answered locally to.'),
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
  $url = $form_state['values']['ask_vopros_uri'];
  $parsed = parse_url($url);
  if (!$parsed || empty($parsed['host']) || empty($parsed['scheme'])) {
    form_error($form['ask_vopros_uri'], t('Invalid URL.'));
  }
  if ($parsed['scheme'] != 'https') {
    form_error($form['ask_vopros_uri'], t('Service URL must be a HTTPS URL in order to protect the privacy of the users'));
  }

  if (!preg_match('/^(|0|-?\d+(%|px|em|rem))$/', trim($form_state['values']['ask_vopros_right']))) {
    form_error($form['ask_vopros_right'], t('Invalid length'));
  }
}
