<?php
/**
 * @file
 * CTools Content Type for banner about free materials.
 */

$plugin = array(
  'title' => t('Free materials banner.'),
  'description' => t('A banner for free materials.'),
  'category' => 'ereolen.dk',
  'single' => TRUE,
  'content type' => 'nonquota_banner',
  'render callback' => 'reol_frontend_nonquota_banner_content_type_render',
  'edit form' => 'reol_frontend_nonquota_banner_content_type_edit_form',
);

/**
 * Render the content type.
 */
function reol_frontend_nonquota_banner_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();

  // We have to implement this as a content type, as a custom panels pane goes
  // through the filter system, which will attempt to clean up the markup to
  // XHTML standard, which wont allow the a element around a block element.
  $block->content = '<a href="/search/ting/%2A?facets[]=facet.extraTitles%3Aekstra%20titler" class="frontpage-banner nonquota-banner">
<div class="nonquota-banner">
<h3>Ekstra lån</h3>
<p>Titler du altid kan låne</p>
</div>
</a>';

  return $block;
}

/**
 * Admin settings form.
 */
function reol_frontend_nonquota_banner_content_type_edit_form($form, &$form_state) {
  return $form;
}
