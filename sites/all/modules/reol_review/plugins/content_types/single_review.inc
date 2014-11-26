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
);

/**
 * Render the content type.
 */
function single_review_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();
  $block->title = '';

  module_load_include('inc', 'reol_review', 'includes/reol_review.reviews');
  $reviews = reol_review_get_reviews();
  $type_reviews = $reviews[array_rand($reviews)];
  $review = $type_reviews[array_rand($type_reviews)];

  // Cover information.
  list($cover) = ting_covers_load(array($review->ding_entity_id => array('image_style' => 'ding_list_medium')));

  $block->content = theme('single_review', array(
    'review_book_title' => $review->title,
    'review_author' => $review->author,
    'review_cover' => $cover['url'],
  ));

  return $block;
}

/**
 * Admin settings form.
 */
function single_review_content_type_edit_form($form, &$form_state) {
  return $form;
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
