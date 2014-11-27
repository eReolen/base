<?php
/**
 * @file
 * CTools Content Type for showing the quick guide.
 */

$plugin = array(
  'title' => t('Show quick guide.'),
  'description' => t('Show the quick quide.'),
  'category' => 'ereolen.dk',
  'single' => TRUE,
  'content type' => 'quick_guide',
  'render callback' => 'quick_guide_content_type_render',
  'hook theme' => 'quick_guide_content_type_theme',
  'edit form' => 'quick_guide_content_type_edit_form',
);

/**
 * Render the content type.
 */
function quick_guide_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();

  // If nid or node is not found, hide this.
  $nid = variable_get('reol_frontend_quick_guide_nid', FALSE);
  if (!$nid) {
    return new StdClass();
  }
  $node = node_load(variable_get('reol_frontend_quick_guide_nid', FALSE));
  if (!$node) {
    return new StdClass();
  }

  $block->content = theme('quick_guide', array(
    'title' => check_plain($node->title),
    'lead' => field_view_field('node', $node, 'field_ding_page_lead', 'full'),
    'body' => field_view_field('node', $node, 'field_ding_page_body', 'full'),
  ));

  return $block;
}

/**
 * Admin settings form.
 */
function quick_guide_content_type_edit_form($form, &$form_state) {
  return $form;
}

/**
 * Ctools block theme function.
 */
function quick_guide_content_type_theme(&$theme, $plugin) {
  $theme['quick_guide'] = array(
    'variables' => array('vars' => NULL),
    'path' => $plugin['path'],
    'template' => 'quick_guide',
  );
}
