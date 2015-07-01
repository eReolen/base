<?php
/**
 * @file
 * CTools Content Type for showing a single review.
 */

$plugin = array(
  'title' => t('Show single review.'),
  'description' => t('Show a single review.'),
  'category' => 'ereolen.dk review',
  'single' => TRUE,
  'content type' => 'single_review',
  'render callback' => 'single_review_content_type_render',
  'hook theme' => 'single_review_content_type_theme',
  'edit form' => 'single_review_content_type_edit_form',
  'all contexts' => TRUE,
);

/**
 * Render the content type.
 */
function single_review_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();
  $block->title = '';

  module_load_include('inc', 'reol_review', 'includes/reol_review.reviews');
  $type = FALSE;
  if (isset($conf['type'])) {
    $type = ctools_context_keyword_substitute($conf['type'], array(), $context);
  }

  // There might be no reviews.
  if ($reviews = reol_review_get_random_reviews(empty($type) ? NULL : $type)) {
    $review = reset($reviews);
    $ting_entity = ding_entity_load($review->ding_entity_id);
    $ting_object_view = ting_object_view($ting_entity, 'review');

    $block->content = theme('single_review', array(
      'ting_title' => $ting_entity->title,
      'ting_object' => drupal_render($ting_object_view),
      'author' => implode($ting_entity->creators, ', '),
      'review_uri' => $review->link,
      'type' => reol_base_get_type_name($ting_entity->type),
      '#object' => $ting_entity,
    ));
  }

  return $block;
}

/**
 * Admin settings form.
 */
function single_review_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];

  $form['type'] = array(
    '#type' => 'textfield',
    '#title' => t('Type'),
    '#description' => t('Select which type to show review for.'),
    '#default_value' => isset($conf['type']) ? $conf['type'] : '',
  );

  return $form;
}

/**
 * Submit handler for content type settings form.
 */
function single_review_content_type_edit_form_submit($form, &$form_state) {
  $form_state['conf']['type'] = $form_state['values']['type'];
}

/**
 * Ctools block theme function.
 */
function single_review_content_type_theme(&$theme, $plugin) {
  $theme['single_review'] = array(
    'variables' => array('vars' => NULL),
    'path' => $plugin['path'],
    'template' => 'single_review',
  );
}
