<?php

/**
 * @file
 * Admin functionality for smartbanner.js.
 */

/**
 * Admin form callback.
 */
function smartbanner_admin_form() {
  $wrapper['smartbanner_settings'] = [
    '#type' => 'container',
    '#title' => t('smartbanner.js settings'),
    '#tree' => TRUE,
  ];

  $form = &$wrapper['smartbanner_settings'];

  $settings = _smartbanner_get_settings();

  $default_values = $settings['visibility'] ?? [];
  $form['visibility'] = [
    '#type' => 'fieldset',
    '#title' => t('Show banner on specific pages'),

    'visibility' => [
      '#type' => 'radios',
      '#options' => [
        'exclude' => t('All pages except those listed'),
        'include' => t('Only the listed pages'),
      ],
      '#default_value' => $default_values['visibility'] ?? 'exclude',
    ],

    'pages' => [
      '#type' => 'textarea',
      '#default_value' => $default_values['pages'] ?? '',
      '#description' => t("Specify pages by using their paths. Enter one path per line. The '*' character is a wildcard. Example paths are %blog for the blog page and %blog-wildcard for every personal blog. %front is the front page.",
                          [
                            '%blog' => 'blog',
                            '%blog-wildcard' => 'blog/*',
                            '%front' => '<front>',
                          ]),
    ],
  ];

  $form['platforms'] = [
    '#type' => 'fieldset',
    '#title' => t('Platforms'),

    'enabled_platforms' => [
      '#type' => 'checkboxes',
      '#title' => t('Enabled platforms'),
      '#options' => [
        'android' => t('Android'),
        'ios' => t('iOS'),
      ],
      '#default_value' => $default_values['enabled_platforms'] ?? ['android', 'ios'],
    ],
  ];

  $form['locales'] = [
    '#type' => 'vertical_tabs',
  ];

  foreach (language_list() as $locale => $language) {
    $form[$locale] = [
      '#type' => 'fieldset',
      '#title' => $language->native,
      '#group' => 'smartbanner_settings][locales',
    ];

    $locale_form = &$form[$locale];
    $locale_settings = $settings[$locale] ?? NULL;

    $default_values = $locale_settings['general'] ?? [];
    $locale_form['general'] = [
      '#type' => 'fieldset',
      '#title' => t('General'),
      '#description' => t('General settings'),

      'title' => [
        '#type' => 'textfield',
        '#title' => t('Title'),
        '#required' => TRUE,
        '#default_value' => $default_values['title'] ?? NULL,
      ],

      'author' => [
        '#type' => 'textfield',
        '#title' => t('Author'),
        '#required' => TRUE,
        '#default_value' => $default_values['author'] ?? NULL,
      ],

      'price' => [
        '#type' => 'textfield',
        '#title' => t('Price'),
        '#required' => TRUE,
        '#default_value' => $default_values['price'] ?? NULL,
      ],

      'show_label' => [
        '#type' => 'textfield',
        '#title' => t('Text on show app button'),
        '#required' => TRUE,
        '#default_value' => $default_values['show_label'] ?? NULL,
      ],

      'close_label' => [
        '#type' => 'textfield',
        '#title' => t('Close label'),
        '#required' => TRUE,
        '#default_value' => $default_values['close_label'] ?? NULL,
      ],
    ];

    $platforms = [
      'android' => t('Android'),
      'ios' => t('iOS'),
    ];
    foreach ($platforms as $key => $name) {
      $default_values = $locale_settings[$key] ?? [];
      $locale_form[$key] = [
        '#type' => 'fieldset',
        '#title' => $name,
        '#description' => t('Settings for !name', ['!name' => $name]),
        '#states' => [
          'visible' => [
            ':input[name="smartbanner_settings[platforms][enabled_platforms][' . $key . ']"]' => ['checked' => TRUE],
          ],
        ],

        'price_suffix' => [
          '#type' => 'textfield',
          '#title' => t('Price suffix'),
          '#required' => TRUE,
          '#default_value' => $default_values['price_suffix'] ?? NULL,
        ],

        'icon_url' => [
          '#type' => 'textfield',
          '#title' => t('Icon url'),
          '#description' => t('Local file path, e.g. sites/all/icons/app-icon.png, or an absolute url. Recommended size: 64 px × 64 px.'),
          '#required' => TRUE,
          '#default_value' => $default_values['icon_url'] ?? NULL,
          '#element_validate' => ['_smartbanner_validate_icon_url'],
        ],

        'app_url' => [
          '#type' => 'textfield',
          '#title' => t('App url'),
          '#required' => TRUE,
          '#default_value' => $default_values['app_url'] ?? NULL,
          '#element_validate' => ['_smartbanner_validate_app_url'],
        ],
      ];
    }
  }

  $result = system_settings_form($wrapper);
  $result['#submit'][] = '_smartbanner_settings_form_submit';

  return $result;
}

/**
 *
 */
function _smartbanner_settings_form_submit($form, &$form_state) {
  $clear_cache_url = url('admin/config/development/performance');
  drupal_set_message(
    t(
      'You have to <a href="@clear_cache_url">clear the cache</a> for the changes to take effect.',
      ['@clear_cache_url' => $clear_cache_url]
    ),
    'warning'
  );
}

/**
 *
 */
function _smartbanner_validate_icon_url($element, &$form_state, $form) {
  $value = $element['#value'];
  if (!valid_url($value, TRUE)) {
    if (valid_url($value)) {
      if (!file_exists($value)) {
        // header('content-type: text/plain'); echo var_export(['public://'.$value, $value], true); die(__FILE__.':'.__LINE__.':'.__METHOD__);.
        form_error($element, t('Please enter a valid path.'));
      }
    }
    else {
      form_error($element, t('Please enter a valid url or path.'));
    }
  }
}

/**
 *
 */
function _smartbanner_validate_app_url($element, &$form_state, $form) {
  if (!valid_url($element['#value'], TRUE)) {
    form_error($element, t('Please enter a valid url.'));
  }
}
