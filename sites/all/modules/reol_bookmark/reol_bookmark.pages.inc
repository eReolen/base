<?php

/**
 * @file
 * Reol bookmark pages.
 */

/**
 * Menu callback; Display user bookmark items.
 */
function reol_bookmark_user_bookmark_page($account) {
  // Try to load all bookmarks for the user.
  $bookmarks = reol_bookmark_get_bookmarks($account);
  if (!empty($bookmarks)) {
    // Bookmarks found, so render them as a material list form.
    $bookmark_form = drupal_get_form('reol_bookmark_bookmarks_form', $bookmarks);
    $output = drupal_render($bookmark_form);
  }
  else {
    $output = t('You do not have any bookmarks yet.');
  }

  return $output;
}

/**
 * Bookmark manage form.
 */
function reol_bookmark_bookmarks_form($form, &$form_state, $bookmarks) {
  $per_page = 10;
  $pager_id = 0;

  $form['bookmarks'] = array(
    '#tree' => TRUE,
  );

  // Add select all title.
  $form['title'] = array(
    '#type' => 'checkbox',
    '#title' => t('Select all bookmarks'),
    '#prefix' => '<div class="select-all bookmarks">',
    '#suffix' => '</div>',
    '#attached' => array(
      'js' => array(
        drupal_get_path('module', 'reol_bookmark') . '/js/bookmarks_form.js',
      ),
    ),
    '#weight' => -10,
  );

  $page = pager_default_initialize(count($bookmarks), $per_page, $pager_id);
  $bookmarks = array_slice($bookmarks, $page * $per_page, $per_page);
  $ting_objects = ding_entity_load_multiple(reol_base_ding_entity_get_ids($bookmarks));

  // Sort ting objects by order of bookmarks (ISBNs).
  uasort($ting_objects, static fn (TingEntity $a, TingEntity $b) => array_search($a->getIsbn()[0] ?? NULL, $bookmarks) <=> array_search($b->getIsbn()[0] ?? NULL, $bookmarks));

  foreach ($ting_objects as $ting_object) {
    // Create title that links to the object.
    $uri = entity_uri('ting_object', $ting_object);
    $title = l($ting_object->getTitle(), $uri['path']);

    // Create basic information.
    $author = field_view_field('ting_object', $ting_object, 'ting_author', 'user_list');
    $type = field_view_field('ting_object', $ting_object, 'ting_type', 'user_list');

    // Build the material item element.
    $item = array(
      '#type' => 'material_item',
      '#id' => $ting_object->id,
      '#title' => $title,
      '#cover' => field_view_field('ting_object', $ting_object, 'ting_cover', 'user_list'),
      '#information' => array(
        'author' => array(
          'label' => t('Author'),
          'data' => drupal_render($author),
          'class' => 'author',
          '#weight' => 2,
        ),
      ),
    );

    // Add the reservation to the form.
    $form['bookmarks'][$ting_object->id] = $item;
  }

  $form['bookmarks']['pager'] = array(
    '#markup' => theme('pager', array('element' => $pager_id)),
  );

  // Add action buttons to the top of the form.
  $form['actions_top'] = array(
    '#prefix' => '<div class="action-buttons">',
    '#suffix' => '</div>',
    '#weight' => -20,
  );

  // Add action buttons to the bottom of the form.
  $form['actions_bottom'] = array(
    '#prefix' => '<div class="action-buttons">',
    '#suffix' => '</div>',
    '#weight' => 10,
  );

  // Add the delete button to both top and bottom.
  $form['actions_top']['delete'] = array(
    '#prefix' => '<div class="delete-bookmarks">',
    '#suffix' => '</div>',
    '#type' => 'submit',
    '#value' => t('Delete selected (@count)', array('@count' => 0)),
  );
  $form['actions_bottom']['delete'] = $form['actions_top']['delete'];

  return $form;
}

/**
 * Submit handler.
 */
function reol_bookmark_bookmarks_form_submit($form, &$form_state) {
  // Filter selected items.
  foreach ($form_state['values']['bookmarks'] as $item) {
    $id = array_pop($item);
    if ($id) {
      reol_bookmark_bookmark($id, TRUE);
    }
  }
}
