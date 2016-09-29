<?php
/**
 * @file
 * Bookmark pane for ctools.
 */

$plugin = array(
  'title' => t('Fancy Box'),
  'description' => t('List of content with fancy theming'),
  'single' => TRUE,
  'category' => t('eReolen for kids'),
);

/**
 * Implements hook_content_type_render().
 *
 * Render a list of nodes with fancy themning.
 */
function breol_fancy_box_fancy_box_content_type_render($subtype, $conf, $panel_args, $context) {

  // Get the queue by its machine so we can extract the id.
  $queue = nodequeue_load_queue_by_name('ereol_frontpage_queue');

  if (empty($queue)) {
    return;
  }

  // Get all nodes in the queue.
  $nodes = nodequeue_load_nodes($queue->qid, FALSE, 0, $queue->size);

  // Get the layout structure.
  $layout = breol_fancy_box_get_layout();

  // Render the block.
  $block = new stdClass();

  $output = theme('breol_fancy_box', array('nodes' => $nodes, 'layout' => $layout));
  $output .= l(t('See all news'), 'nyheder', array('attributes' => array('class' => array('more-link btn'))));

  // Set title.
  $block->title = t('Nyt og spændende');

  // Set content.
  $block->content = $output;

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
