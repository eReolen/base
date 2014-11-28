<?php
/**
 * @file
 * CTools Content Type for showing the facebook likebox.
 */

$plugin = array(
  'title' => t('Show Facebook likebox.'),
  'description' => t('Show the likebox from Facebook.'),
  'category' => 'ereolen.dk',
  'single' => TRUE,
  'content type' => 'facebook_likebox',
  'render callback' => 'facebook_likebox_content_type_render',
  'hook theme' => 'facebook_likebox_content_type_theme',
  'edit form' => 'facebook_likebox_content_type_edit_form',
);

/**
 * Render the content type.
 */
function facebook_likebox_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();

  $facebook_url = variable_get('reol_frontend_facebook_url', FALSE);
  // If facebook url is not defined, hide this.
  if (!$facebook_url) {
    return new StdClass();
  }

  drupal_add_js(drupal_get_path('module', 'reol_frontend') . '/js/facebook.sdk.js');
  $block->content = theme('facebook_likebox', array(
    'facebook_url' => $facebook_url,
    'width' => $conf['width'],
    'height' => $conf['height'],
  ));

  return $block;
}

/**
 * Admin settings form.
 */
function facebook_likebox_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];

  $form['width'] = array(
    '#type' => 'textfield',
    '#size' => 4,
    '#title' => t('Width'),
    '#description' => t('The width of the likebox plugin'),
    '#default_value' => isset($conf['width']) ? $conf['width'] : 270,
  );
  $form['height'] = array(
    '#type' => 'textfield',
    '#size' => 4,
    '#title' => t('Height'),
    '#description' => t('The height of the likebox plugin'),
    '#default_value' => isset($conf['height']) ? $conf['height'] : 424,
  );

  return $form;
}

/**
 * Submit handler for content type settings from.
 */
function facebook_likebox_content_type_edit_form_submit($form, &$form_state) {
  $form_state['conf']['width'] = $form_state['values']['width'];
  $form_state['conf']['height'] = $form_state['values']['height'];
}

/**
 * Ctools block theme function.
 */
function facebook_likebox_content_type_theme(&$theme, $plugin) {
  $theme['facebook_likebox'] = array(
    'variables' => array('vars' => NULL),
    'path' => $plugin['path'],
    'template' => 'facebook_likebox',
  );
}
