<?php

/**
 * @file
 * Administrative functions for breol_news_page.
 */

/**
 * News page settings.
 */
function breol_news_page_settings($form, &$form_state) {
  $form['breol_news_page_image'] = array(
    '#type' => 'media',
    '#title' => t('Header image'),
    '#description' => t('Allowed formats: PNG and JPG.'),
    '#media_options' => array(
      'global' => array(
        'types' => array('image' => 'image'),
        'schemes' => array('public' => 'public'),
        'file_extensions' => 'png jpeg jpg',
        'max_filesize' => '2 MB',
        'file_directory' => 'news_header',
        'enabledPlugins' => array(
          'upload',
          // Probably some "proper" way to discover this plugins name, but...
          'media_default--media_browser_1',
        ),
      ),
    ),
    '#default_value' => variable_get('breol_news_page_image', NULL),
  );

  return system_settings_form($form);
}
