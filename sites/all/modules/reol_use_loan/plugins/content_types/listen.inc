<?php
/**
 * @file
 * CTools Content Type for listening to an audiobook.
 */

$plugin = array(
  'title' => t('Listen to audiobook'),
  'description' => t('Listen to an audiobook i have borrowed.'),
  'category' => 'ereolen.dk loans',
  'single' => TRUE,
  'content type' => 'listen',
  'render callback' => 'listen_content_type_render',
  'required context' => array(
    new ctools_context_optional(t('Ting object'), 'ting_object'),
  ),
  'hook theme' => 'listen_content_type_theme',
  'edit form' => 'listen_content_type_edit_form',
);

/**
 * Render the content type.
 */
function listen_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();
  $block->title = t('Listen to your audiobook');
  $block->content = theme('listen', array(
    // TODO Do not hardcode.
    'internal_order_number' => 'bbf27a0c-340c-4120-a36f-0a37f8ae3b88',
  ));

  return $block;
}

/**
 * Admin settings form.
 */
function listen_content_type_edit_form($form, &$form_state) {
  return $form;
}

/**
 * Ctools block theme function.
 */
function listen_content_type_theme(&$theme, $plugin) {
  $theme['listen'] = array(
    'variables' => array('vars' => NULL),
    'path' => $plugin['path'],
    'template' => 'listen',
  );
}
