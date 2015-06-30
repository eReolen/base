<?php
/**
 * @file
 * CTools Content Type for banner about eReolen global.
 */

$plugin = array(
  'title' => t('eReolen Global banner.'),
  'description' => t('A banner for eReolen Global.'),
  'category' => 'ereolen.dk',
  'single' => TRUE,
  'content type' => 'global_banner',
  'render callback' => 'reol_frontend_global_banner_content_type_render',
  'edit form' => 'reol_frontend_global_banner_content_type_edit_form',
);

/**
 * Render the content type.
 */
function reol_frontend_global_banner_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();

  // We have to implement this as a content type, as a custom panels pane goes
  // through the filter system, which will attempt to clean up the markup to
  // XHTML standard, which wont allow the a element around a block element.
  $block->content = '<a href="http://www.ereolenglobal.dk" class="frontpage-banner global-banner">
<div class="global-banner">
<h3>Udenlandsk litteratur</h3>
<img src="/' . path_to_theme() . '/images/ereolen-global-logo.png" />
</div>
</a>';

  return $block;
}

/**
 * Admin settings form.
 */
function reol_frontend_global_banner_content_type_edit_form($form, &$form_state) {
  return $form;
}
