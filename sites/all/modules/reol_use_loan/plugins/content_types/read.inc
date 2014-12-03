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

  global $user;
  $order = ding_provider_invoke('loan', 'get', $user, $ting_entity->localId);
  if (!$order) {
    return new StdClass();
  }

  $block->content = theme('read', array(
    // TODO Do not hardcode.
    'retailer_order_number' => $order['retailer_order_number'],
  ));

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
