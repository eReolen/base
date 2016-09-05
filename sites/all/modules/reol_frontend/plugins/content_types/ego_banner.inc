<?php
/**
 * @file
 * CTools Content Type for banner about eReolen GO.
 */

$plugin = array(
  'title' => t('eReolen GO banner.'),
  'description' => t('A banner for eReolen GO.'),
  'category' => 'ereolen.dk',
  'single' => TRUE,
  'content type' => 'go_banner',
  'render callback' => 'reol_frontend_go_banner_content_type_render',
  'edit form' => 'reol_frontend_go_banner_content_type_edit_form',
);

/**
 * Render the content type.
 */
function reol_frontend_go_banner_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();

  // We have to implement this as a content type, as a custom panels pane goes
  // through the filter system, which will attempt to clean up the markup to
  // XHTML standard, which wont allow the a element around a block element.
  $block->content = '<a href="http://www.ereolengo.dk" class="frontpage-banner go-banner">
<div class="go-banner">
<img src="/' . drupal_get_path('module', 'reol_frontend') . '/images/ereolengo_logo.png" />
</div>
</a>';

  return $block;
}

/**
 * Admin settings form.
 */
function reol_frontend_go_banner_content_type_edit_form($form, &$form_state) {
  return $form;
}
