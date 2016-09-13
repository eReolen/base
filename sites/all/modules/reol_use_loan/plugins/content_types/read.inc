<?php
/**
 * @file
 * CTools Content Type for reading an ebook.
 */

$plugin = array(
  'title' => t('Read ebook'),
  'description' => t('Read an ebook i have borrowed.'),
  'category' => 'ereolen.dk loans',
  'single' => TRUE,
  'content type' => 'read',
  'render callback' => 'read_content_type_render',
  'required context' => array(
    new ctools_context_optional(t('Ting object'), 'ting_object'),
  ),
  'hook theme' => 'read_content_type_theme',
  'edit form' => 'read_content_type_edit_form',
);

/**
 * Render the content type.
 */
function read_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();
  $block->title = t('Read your ebook');

  $ting_entity = $context[0]->data;

  $order = reol_use_loan_get_order($ting_entity->localId);

  $vars = array();
  // If there is no order, start player in preview mode.
  if (!$order) {
    $vars['isbn'] = reol_base_get_isbn($ting_entity->localId);
  }
  else {
    $vars['retailer_order_number'] = $order['retailer_order_number'];
  }

  $block->content = theme('read', $vars);

  return $block;
}

/**
 * Admin settings form.
 */
function read_content_type_edit_form($form, &$form_state) {
  return $form;
}

/**
 * Ctools block theme function.
 */
function read_content_type_theme(&$theme, $plugin) {
  $theme['read'] = array(
    'variables' => array('vars' => NULL),
    'path' => $plugin['path'],
    'template' => 'read',
  );
}