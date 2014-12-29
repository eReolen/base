<?php
/**
 * @file
 * CTools Content Type for showing back button.
 */

$plugin = array(
  'title' => t('Show back button.'),
  'description' => t('Show back button.'),
  'category' => 'ereolen.dk',
  'single' => TRUE,
  'content type' => 'back',
  'render callback' => 'back_content_type_render',
  'hook theme' => 'back_content_type_theme',
  'edit form' => 'back_content_type_edit_form',
);

/**
 * Render the content type.
 */
function back_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();

  $block->content = theme('back', array());

  return $block;
}

/**
 * Admin settings form.
 */
function back_content_type_edit_form($form, &$form_state) {
  return $form;
}

/**
 * Ctools block theme function.
 */
function back_content_type_theme(&$theme, $plugin) {
  $theme['back'] = array(
    'variables' => array('vars' => NULL),
    'path' => $plugin['path'],
    'template' => 'back',
  );
}
