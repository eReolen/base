<?php

/**
 * @file
 * Admin form for reol_app_feeds.
 */

use Drupal\reol_app_feeds\Feed\FrontPageFeed;

/**
 * The administration form for this module.
 *
 * @param array $form
 *   The form input.
 * @param array $form_state
 *   The state of the form.
 *
 * @return array
 *   The finished form.
 */
function reol_app_feeds_admin_form(array $form, array &$form_state) {
  $inspiration_pages = [];
  $inspiration_pages_options = [];

  $form['#theme'] = 'reol_app_feeds_admin_form';

  // Find all inspiration pages.
  $query = db_select('node', 'n')
    ->condition('type', 'inspiration')
    ->condition('status', NODE_PUBLISHED)
    ->fields('n', ['nid', 'title']);
  $result = $query->execute();
  foreach ($result as $record) {
    $inspiration_pages[$record->nid] = $record;
  }

  $inspiration_pages_options = array_combine(array_keys($inspiration_pages), array_map(function ($node) {
    return $node->title;
  }, $inspiration_pages));

  $group_name = 'reol_app_feeds_frontpage';
  $form[$group_name] = [
    '#type' => 'fieldset',
    '#title' => t('Frontpage feed'),
    '#tree' => TRUE,
  ];

  $form[$group_name]['frontpage_ids'] = [
    '#type' => 'checkboxes',
    '#title' => t('Front pages'),
    '#default_value' => FrontPageFeed::getFrontPageIds(),
    '#options' => $inspiration_pages_options,
    '#multiple' => TRUE,
    '#description' => t('Frontpages used in feeds'),
    '#required' => TRUE,
  ];

  $form[$group_name]['link_button_text'] = [
    '#type' => 'textfield',
    '#title' => t('Link button text'),
    '#default_value' => _reol_app_feeds_variable_get($group_name, 'link_button_text'),
    '#description' => t('Link button text'),
    '#required' => TRUE,
  ];

  $form[$group_name]['theme_list_max_length'] = [
    '#type' => 'textfield',
    '#title' => t('Max number of themes in lists'),
    '#default_value' => _reol_app_feeds_variable_get($group_name, 'theme_list_max_length', 6),
    '#element_validate' => ['element_validate_integer_positive'],
    '#description' => t('The maximum number of themes in theme lists'),
    '#required' => TRUE,
  ];

  $form[$group_name]['max_news_count'] = [
    '#type' => 'textfield',
    '#title' => t('Max number items in latest news'),
    '#default_value' => _reol_app_feeds_variable_get($group_name, 'max_news_count', 6),
    '#element_validate' => ['element_validate_integer_positive'],
    '#description' => t('The maximum number of items in the latest news list'),
    '#required' => TRUE,
  ];

  $group_name = 'reol_app_feeds_category';
  $field_name = 'page_ids';

  $form[$group_name] = [
    '#type' => 'fieldset',
    '#title' => t('Category feed'),
    '#tree' => TRUE,
    '#description' => t('Select pages to include in category feed and specify order.'),
  ];

  $form[$group_name][$field_name]['#tree'] = TRUE;

  // The max weight used when sorting pages.
  $max_weight = count($inspiration_pages);

  // Get info on pages that have been included in the feed.
  $category_feed_pages = _reol_app_feeds_variable_get($group_name, $field_name, []);

  // Add any new/missing inspiration pages to category feed pages.
  foreach ($inspiration_pages as $nid => $page) {
    if (!isset($category_feed_pages[$nid])) {
      $category_feed_pages[$nid] = [
        'included' => 0,
        'weight' => $max_weight,
      ];
    }
  }

  foreach ($category_feed_pages as $nid => $data) {
    $node = $inspiration_pages[$nid];
    $form[$group_name][$field_name][$nid] = [
      'name' => [
        '#markup' => check_plain($node->title),
      ],

      'included' => [
        '#type' => 'checkbox',
        '#default_value' => isset($data['included']) && 1 === $data['included'],
      ],

      'weight' => [
        '#type' => 'weight',
        '#title' => t('Weight'),
        '#default_value' => isset($data['weight']) ? $data['weight'] : $max_weight,
        '#delta' => $max_weight,
        '#title_display' => 'invisible',
      ],
    ];
  }

  $form[$group_name]['default_color'] = [
    '#type' => 'textfield',
    '#title' => t('Default color'),
    '#default_value' => _reol_app_feeds_variable_get($group_name, 'default_color'),
    '#description' => t('The default color (Format: #RRGGBB).'),
    '#element_validate' => ['_reol_app_feeds_admin_validate_color_rgb'],
  ];

  $group_name = 'reol_app_feeds_themes';
  $form[$group_name] = [
    '#type' => 'fieldset',
    '#title' => t('Themes feed'),
    '#tree' => TRUE,
  ];

  $form[$group_name]['max_number_of_items'] = [
    '#type' => 'textfield',
    '#title' => t('Max number of themes'),
    '#default_value' => _reol_app_feeds_variable_get($group_name, 'max_number_of_items', 50),
    '#element_validate' => ['element_validate_integer_positive'],
    '#description' => t('The maximum number of themes'),
    '#required' => TRUE,
  ];

  $form['reol_app_feeds_feeds'] = [
    '#type' => 'fieldset',
    '#title' => t('Feeds'),
    'content' => [
      '#markup' => implode('', [
        '<ul>',
        '<li>' . l(t('Frontpage'), '/app/feed/frontpage') . '</li>',
        '<li>' . l(t('Themes'), '/app/feed/themes') . '</li>',
        '<li>' . l(t('Categories'), '/app/feed/categories') . '</li>',
        '<li>' . l(t('Overdrive mapping'), '/app/feed/overdrive/mapping') . '</li>',
        '</ul>',
      ]),
    ],
  ];

  return system_settings_form($form);
}

/**
 * Default theme function for reol_app_feeds_admin_form.
 */
function theme_reol_app_feeds_admin_form($variables) {
  $form = $variables['form'];

  // Initialize the variable which will store our table rows.
  $rows = [];

  $group_name = 'reol_app_feeds_category';
  foreach (element_children($form[$group_name]['page_ids']) as $id) {
    $form[$group_name]['page_ids'][$id]['weight']['#attributes']['class'] = [$group_name . '-item-weight'];

    // We are now ready to add each element of our $form data to the $rows
    // array, so that they end up as individual table cells when rendered
    // in the final table.  We run each element through the drupal_render()
    // function to generate the final html markup for that element.
    $rows[] = [
      'data' => [
        drupal_render($form[$group_name]['page_ids'][$id]['name']),
        drupal_render($form[$group_name]['page_ids'][$id]['included']),
        drupal_render($form[$group_name]['page_ids'][$id]['weight']),
      ],
      'class' => ['draggable'],
    ];
  }

  // We now define the table header values.  Ensure that the 'header' count
  // matches the final column count for your table.
  $header = [
    t('Name'),
    t('Included'),
    t('Weight'),
  ];

  $table_id = $group_name;

  $form['reol_app_feeds_category']['page_ids'] = [
    '#markup' => theme('table', [
      'header' => $header,
      'rows' => $rows,
      'attributes' => ['id' => $table_id],
    ]),
  ];

  drupal_add_tabledrag($table_id, 'order', 'sibling', $group_name . '-item-weight');

  return drupal_render_children($form);
}

/**
 * Validate handler for the administration form.
 *
 * Sort 'reol_app_feeds_category' array by weight before it's saved to the
 * database in the submit handler.
 *
 * @param array $form
 *   The form input.
 * @param array $form_state
 *   The state of the form.
 */
function reol_app_feeds_admin_form_validate(array $form, array &$form_state) {
  $items = &$form_state['values']['reol_app_feeds_category']['page_ids'];
  foreach ($items as &$item) {
    if (1 !== $item['included']) {
      $item['weight'] = 1000;
    }
  }

  uasort($items, function ($a, $b) {
    return $a['weight'] - $b['weight'];
  });
}

/**
 * Validation function for rgb color in the hexadecimal format (#RRGGBB).
 *
 * @param array $element
 *   The element.
 * @param array $form_state
 *   The form state.
 */
function _reol_app_feeds_admin_validate_color_rgb(array $element, array &$form_state) {
  $value = $element['#value'];
  if ($value !== '' && !preg_match('@^#[0-9a-fA-F]{6}$@', $value)) {
    form_error($element, t('%name must be a valid color in the hexadecimal format (#RRGGBB).', ['%name' => $element['#title']]));
  }
}
