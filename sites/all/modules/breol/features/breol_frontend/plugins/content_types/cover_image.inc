<?php
/**
 * @file
 * Bookmark pane for ctools.
 */

$plugin = array(
  'title' => t('Breol Cover Image'),
  'description' => t('Display a Cover Image with title and sub-title'),
  'single' => TRUE,
  'category' => 'eReolen for kids',
  'required context' => new ctools_context_required(t('Node'), 'node'),
);

/**
 * Implements hook_content_type_render().
 *
 * Render an image as a Cover Image.
 */
function breol_frontend_cover_image_content_type_render($subtype, $conf, $panel_args, $context) {

  // If there is no context data we will abort.
  if (empty($context->data)) {
    return;
  }

  // Get the node from the context.
  $node = $context->data;

  // Check if we still want to be here,
  if (!in_array($node->type, array(
      'breol_subject',
      'breol_section',
      'breol_news',
      'breol_page',
      )
    )) {
    return;
  }

  // Assign node for view.
  $variables['node'] = $node;

  if (!empty($node->field_breol_cover_image)) {
    $image_entity = !empty($node->field_breol_cover_image) ? $node->field_breol_cover_image[LANGUAGE_NONE][0] : NULL;
    $file_uri = file_create_url($image_entity['uri']);
    $variables['image_uri'] = $file_uri;
  }

  $variables['cover_background_color'] = 'transparant';
  if ($node->type ==='breol_subject' && !empty($node->field_color[LANGUAGE_NONE][0]['rgb'])) {
    $variables['cover_background_color'] = $node->field_color[LANGUAGE_NONE][0]['rgb'];
  } elseif ($node->type ==='breol_section') {
    $variables['cover_background_color'] = 'rgba(235, 235, 235, 0.9)';
  }

  // Get body for breol_news.
  if ($node->type === 'breol_news') {
    $variables['body'] = $node->body[LANGUAGE_NONE][0]['value'];
  }

  // Add wrapper classes.
  $variables['wrapper_class'] = 'cover__regular';

   if ($node->type === 'breol_subject' || $node->type === 'breol_section') {

    // TODO(ts) - This was made last minute before launch. Should be refactored later.
    $variables['wrapper_class'] = 'cover__' . strtolower($node->title);
    if (strtolower($node->title) === 'ebøger' || strtolower($node->title) === 'netlydbøger') {
      $variables['image_uri'] = NULL;
      if (strtolower($node->title) === 'ebøger') {
        $variables['wrapper_class'] = 'cover__ebooks';
      } elseif (strtolower($node->title) === 'netlydbøger') {
        $variables['wrapper_class'] = 'cover__audiobooks';
      }
    }
  } elseif ($node->type === 'breol_page') {
    $variables['wrapper_class'] = 'cover__fallback';
  }

  // Render the block.
  $block = new stdClass();

  // Set title.
  $block->title = '';

  // Set content.
  $block->content = theme('cover_image', $variables);

  return $block;
}

/**
 * Returns an edit form for the content type.
 *
 * We're not actually doing anything here, but we need to have this hook
 * for this content type to work.
 */
function breol_frontend_cover_image_content_type_edit_form($form, &$form_state) {
  return $form;
}
