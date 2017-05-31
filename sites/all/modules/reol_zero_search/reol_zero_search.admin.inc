<?php

/**
 * @file
 * Administrative pages.
 */

/**
 * Admin settings form for frontend display of carousel.
 */
function reol_zero_search_settings_admin_form($form, &$form_state) {
  $form = array();

  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Frontend settings'),
  );

  $form['settings']['reol_zero_search_carousel_description_toggle'] = array(
    '#title' => t('Show descriptions for navigational tabs'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('reol_zero_search_carousel_description_toggle', 0),
    '#required' => FALSE,
    '#description' => t('Toggle whether descriptions of the various searches are displayed or not.'),
  );

  $transitions = array();
  foreach (ting_search_carousel_transitions() as $name => $transition) {
    $transitions[$name] = $transition['name'];
  }

  $form['settings']['reol_zero_search_carousel_transition'] = array(
    '#title' => t('Tab switching transition'),
    '#type' => 'select',
    '#options' => $transitions,
    '#default_value' => variable_get('reol_zero_search_carousel_transition', 'fade'),
    '#description' => t('The JS transition used when switching tabs. This applies to the front page carousel.'),
  );

  return system_settings_form($form);
}

/**
 * Search queries admin form.
 *
 * @param array $form
 *   Form.
 * @param array $form_state
 *   Form state.
 *
 * @return array
 *   Form structure.
 */
function reol_zero_search_admin_form(array $form, array &$form_state) {
  $form['reol_zero_search_carousel_search_queries'] = array(
    '#tree' => TRUE,
    '#prefix' => '<div id="reol-zero-search-wrapper">',
    '#suffix' => '</div>',
    '#theme' => 'reol_zero_search_admin_form_table',
  );

  // Get current saved queries.
  if (!isset($form_state['searches'])) {
    $form_state['searches'] = variable_get('reol_zero_search_carousel_search_queries', array());
  }

  $searches = $form_state['searches'];

  $weight = 0;
  foreach ($searches as $index => $item) {

    $form['reol_zero_search_carousel_search_queries'][$index]['title'] = array(
      '#type' => 'textfield',
      '#title' => t('Title'),
      '#default_value' => isset($item['title']) ? $item['title'] : '',
      '#size' => 16,
      '#title_display' => 'invisible',
    );

    $form['reol_zero_search_carousel_search_queries'][$index]['subtitle'] = array(
      '#type' => 'textfield',
      '#title' => t('Description'),
      '#default_value' => isset($item['subtitle']) ? $item['subtitle'] : '',
      '#size' => 32,
      '#title_display' => 'invisible',
    );

    $form['reol_zero_search_carousel_search_queries'][$index]['query'] = array(
      '#type' => 'textfield',
      '#title' => t('Query'),
      '#maxlength' => 2048,
      '#default_value' => isset($item['query']) ? $item['query'] : '',
      '#title_display' => 'invisible',
    );

    $form['reol_zero_search_carousel_search_queries'][$index]['weight'] = array(
      '#type' => 'weight',
      '#delta' => 50,
      '#default_value' => $weight++,
      '#title_display' => 'invisible',
      '#attributes' => array(
        'class' => array(
          'reol-zero-search-sort',
        ),
      ),
    );

    $form['reol_zero_search_carousel_search_queries'][$index]['remove'] = array(
      '#type' => 'submit',
      '#value' => t('Remove'),
      // Give the button a unique name so Drupal can tell which one was clicked.
      '#name' => 'remove-' . $index,
      '#index' => $index,
      '#submit' => array('reol_zero_search_admin_form_remove'),
      '#ajax' => array(
        'callback' => 'reol_zero_search_admin_form_ajax_callback',
        'wrapper' => 'reol-zero-search-wrapper',
      ),
    );
  }

  $form['add_more'] = array(
    '#type' => 'submit',
    '#value' => t('Add another'),
    '#submit' => array('reol_zero_search_admin_form_add_more'),
    '#ajax' => array(
      'callback' => 'reol_zero_search_admin_form_ajax_callback',
      'wrapper' => 'reol-zero-search-wrapper',
    ),
  );

  // Custom form submit handler.
  $form['#submit'] = array('reol_zero_search_admin_form_submit');
  return system_settings_form($form);
}

/**
 * AJAX callback for adding/removing query.
 *
 * Returns the new form.
 */
function reol_zero_search_admin_form_ajax_callback(array $form, array &$form_state) {
  return $form['reol_zero_search_carousel_search_queries'];
}

/**
 * AJAX submit handler for adding query.
 */
function reol_zero_search_admin_form_add_more(array $form, array &$form_state) {
  // Add an empty new element.
  $form_state['searches'][] = array(
    'title' => '',
    'subtitle' => '',
    'query' => '',
  );
  $form_state['rebuild'] = TRUE;
}

/**
 * AJAX submit handler for removing query.
 */
function reol_zero_search_admin_form_remove(array $form, array &$form_state) {
  $remove = $form_state['clicked_button']['#index'];
  unset($form_state['searches'][$remove]);
  $form_state['rebuild'] = TRUE;
}

/**
 * Theme the queries table.
 *
 * @param array $variables
 *   Theme related variables.
 *
 * @return string
 *   Themed form output.
 */
function theme_reol_zero_search_admin_form_table(array $variables) {
  $elements = $variables['elements'];
  drupal_add_tabledrag('reol-zero-search-admin-sort', 'order', 'sibling', 'reol-zero-search-sort');

  $header = array(
    t('Title'),
    t('Description'),
    t('Search'),
    t('Weight'),
    t('Operations'),
  );
  $rows = array();
  foreach (element_children($elements) as $key) {
    $rows[] = array(
      'data' => array(
        drupal_render($elements[$key]['title']),
        drupal_render($elements[$key]['subtitle']),
        drupal_render($elements[$key]['query']),
        drupal_render($elements[$key]['weight']),
        drupal_render($elements[$key]['remove']),
      ),
      'class' => array('draggable'),
    );
  }

  $table_vars = array(
    'header' => $header,
    'rows' => $rows,
    'attributes' => array('id' => 'reol-zero-search-admin-sort'),
    'empty' => t('No searches configured.'),
  );
  $output = theme('table', $table_vars);

  return $output;
}

/**
 * Submit handler for admin backend queries form.
 *
 * @param array $form
 *   Form.
 * @param array $form_state
 *   Form state.
 */
function reol_zero_search_admin_form_submit(array $form, array &$form_state) {
  $searches = $form_state['values']['reol_zero_search_carousel_search_queries'];
  uasort($searches, 'drupal_sort_weight');

  // Unset weight for saving to variable and weed out empty searches.
  foreach (array_keys($searches) as $key) {
    unset($searches[$key]['weight']);
    if (empty($searches[$key]['title']) &&
      empty($searches[$key]['subtitle']) &&
      empty($searches[$key]['query'])) {
      unset($searches[$key]);
    }
  }

  // Reindex.
  $searches = array_values($searches);

  // Set value for system_settings_form_submit() to save.
  form_set_value($form['reol_zero_search_carousel_search_queries'], $searches, $form_state);

  /*
   * @TODO: Add clear cache button and detect changes in the query input fields
   * so only partial cache can be rebuild. This will slow down the submit but
   * may speed up the presentation for the users by kick starting the cache.
   */

  // Clear carousel search cache.
  cache_clear_all('ting_search_carousel_search_', 'cache', TRUE);
}
