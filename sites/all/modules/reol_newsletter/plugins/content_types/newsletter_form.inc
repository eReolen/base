<?php
/**
 * @file
 * CTools Content Type for showing the newsletter form for a user.
 */

$plugin = array(
  'title' => t('Show newsletter status form.'),
  'description' => t('Show the status form for the newsletter, for a user.'),
  'category' => 'ereolen.dk',
  'single' => TRUE,
  'content type' => 'newsletter_form',
  'render callback' => 'newsletter_form_content_type_render',
  'edit form' => 'newsletter_form_content_type_edit_form',
  'required context' => array(
    new ctools_context_required(t('User'), 'user'),
  ),
);

/**
 * Render the content type.
 */
function newsletter_form_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();
  $block->title = t('Newsletter signup status');

  $form = drupal_get_form('reol_newsletter_status_form', $context[0]->data->uid);
  $block->content = $form;

  return $block;
}

/**
 * Admin settings form.
 */
function newsletter_form_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];

  return $form;
}

/**
 * Submit handler for content type settings form.
 */
function newsletter_form_content_type_edit_form_submit($form, &$form_state) {
  $form_state['conf']['type'] = $form_state['values']['type'];
}
