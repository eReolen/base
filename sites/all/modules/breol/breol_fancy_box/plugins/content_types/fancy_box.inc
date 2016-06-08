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
  $block->content = theme('breol_fancy_box', array(
    'nodes' => $nodes,
    'layout' => $layout,
  ));

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

function breol_fancy_box_render_node($node, $layout) {

  $view_mode = 'teaser_' . $layout['type'];

  $rendered_node = node_view($node, $view_mode);

  return drupal_render($rendered_node);
}

/**
 * Get the layout structure of the fancy box.
 *
 * For now this is hardcoded, but in the feature this array might be editable
 * from the admin interface somehow.
 *
 * @return array
 */
function breol_fancy_box_get_layout() {
  return array(
    array(
      'type' => 'medium',
      'attributes' => array(
        'class' => array(
        ),
      ),
    ),
    array(
      'type' => 'small',
      'attributes' => array(
        'class' => array(
        ),
      ),
    ),
    array(
      'type' => 'small',
      'attributes' => array(
        'class' => array(
          'fancy-box__push-right',
        ),
      ),
    ),
    array(
      'type' => 'medium',
      'attributes' => array(
        'class' => array(
        ),
      ),
    ),
    array(
      'type' => 'medium',
      'attributes' => array(
        'class' => array(
          'fancy-box__push-left',
        ),
      ),
    ),
    array(
      'type' => 'small',
      'attributes' => array(
        'class' => array(
        ),
      ),
    ),
  );
}
