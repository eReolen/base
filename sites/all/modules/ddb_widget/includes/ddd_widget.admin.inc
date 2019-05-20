<?php
/**
 * @file
 * Administration UI for the widget module.
 */

/**
 * Implements hook_form().
 *
 * Mostly taken form the core block module.
 */
function ddb_widget_settings_form($form, &$form_state) {
  $form = [
    '#tree' => TRUE,
  ];

  $config =  variable_get('ddb_widget', [
    'path' => [
      'visibility' => BLOCK_VISIBILITY_NOTLISTED,
      'pages' => '',
    ],
    'role' => [
      'roles' => [],
    ],
    'script' => '',
  ]);


  // Script to inject.
  $form['ddb_widget']['script'] = array(
    '#type' => 'fieldset',
    '#title' => t('Widget code'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#group' => 'visibility',
    '#weight' => 0,
  );

  $form['ddb_widget']['script']['code'] = [
    '#type' => 'textarea',
    '#title' => '',
    '#default_value' => $config['script']['code'],
    '#description' => t('Enter the generated JavaScript code block without the script tags.'),
  ];

  // Per-path visibility.
  $form['ddb_widget']['path'] = array(
    '#type' => 'fieldset',
    '#title' => t('Pages'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#group' => 'visibility',
    '#weight' => 0,
  );

  $form['ddb_widget']['path']['visibility'] = [
    '#type' => 'radios',
    '#title' => t('Show block on specific pages'),
    '#options' => [
      BLOCK_VISIBILITY_NOTLISTED => t('All pages except those listed'),
      BLOCK_VISIBILITY_LISTED => t('Only the listed pages'),
    ],
    '#default_value' => $config['path']['visibility'],
  ];
  $form['ddb_widget']['path']['pages'] = [
    '#type' => 'textarea',
    '#title' => '<span class="element-invisible">' . t('Pages') . '</span>',
    '#default_value' => $config['path']['pages'],
    '#description' => t("Specify pages by using their paths. Enter one path per line. The '*' character is a wildcard. Example paths are %blog for the blog page and %blog-wildcard for every personal blog. %front is the front page.", array('%blog' => 'blog', '%blog-wildcard' => 'blog/*', '%front' => '<front>')),
  ];

  // Per-role visibility.
  $role_options = array_map('check_plain', user_roles());
  $form['ddb_widget']['role'] = [
    '#type' => 'fieldset',
    '#title' => t('Roles'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#group' => 'visibility',
    '#weight' => 10,
  ];
  $form['ddb_widget']['role']['roles'] = [
    '#type' => 'checkboxes',
    '#title' => t('Show block for specific roles'),
    '#default_value' => $config['role']['roles'],
    '#options' => $role_options,
    '#description' => t('Show this block only for the selected role(s). If you select no roles, the block will be visible to all users.'),
  ];


  return system_settings_form($form);
}
