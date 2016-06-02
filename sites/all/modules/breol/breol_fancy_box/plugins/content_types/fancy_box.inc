<?php
/**
 * @file
 * Bookmark pane for ctools.
 */

$plugin = array(
  'title' => t('Fancy Box'),
  'description' => t('List of content with fancy theming'),
  'single' => TRUE,
  'category' => t('BReol'),
);

/**
 * Implements hook_content_type_render().
 *
 * Render a list of nodes with fancy themning.
 */
function breol_fancy_box_fancy_box_content_type_render($subtype, $conf, $panel_args, $context) {

  $block = new stdClass();
  $block->content = theme('breol_fancy_box', array());

  return $block;
}

/**
 * Returns an edit form for the content type.
 *
 * We're not actually doing anything here, but we need to have this hook
 * for this content type to work.
 */
function breol_fancy_box_fancy_box_content_type_edit_form($form, &$form_state) {
  return $form;
}
