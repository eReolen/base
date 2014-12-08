<?php
/**
 * @file
 * Administrative pages for reol_category.
 */

/**
 * Form for adding/editing categories.
 */
function reol_category_form($form, &$form_state, $category, $op = 'edit') {
  if ($op == 'clone') {
    $category->path .= '_new';
    $category->title .= ' (cloned)';
  }

  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#default_value' => $category->title,
    '#description' => t('Title of category.'),
    '#maxlength' => 255,
  );

  $form['path'] = array(
    '#type' => 'textfield',
    '#title' => t('Path'),
    '#default_value' => $category->path,
    '#description' => t('Path of the category page.'),
    '#maxlength' => 255,
  );

  $form['query'] = array(
    '#type' => 'textarea',
    '#title' => t('Search'),
    '#default_value' => $category->query,
    '#description' => t('The Ting query to perform.'),
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 40,
  );

  $form['actions']['delete'] = array(
    '#type' => 'submit',
    '#value' => t('Delete'),
    '#weight' => 45,
    '#limit_validation_errors' => array(),
    '#submit' => array('reol_category_form_submit_delete'),
  );

  return $form;
}

/**
 * Form API validate callback for the category form.
 */
function reol_category_form_validate(&$form, &$form_state) {
  // Path must be unique.
  $existing = entity_load('reol_category', FALSE, array('path' => $form_state['values']['path']));
  if ($existing && ($existing = reset($existing)) && ($existing->rcid != $form_state['reol_category']->rcid)) {
    form_error($form['path'], t('Path must be unique.'));
  }
}

/**
 * Form API submit callback for the category form.
 */
function reol_category_form_submit(&$form, &$form_state) {
  $category = entity_ui_form_submit_build_entity($form, $form_state);
  // Save and go back.
  $category->save();
  menu_rebuild();
  $form_state['redirect'] = 'admin/structure/reol_category';
}

/**
 * Form API submit callback for the delete button.
 */
function reol_category_form_submit_delete(&$form, &$form_state) {
  menu_rebuild();
  $form_state['redirect'] = 'admin/structure/reol_category/manage/' . $form_state['reol_category']->name . '/delete';
}

/**
 * Feed settings form.
 */
function reol_category_feed_settings($form, &$form_settings) {
  $options = menu_parent_options(array('main-menu' => t('Main menu')), '');

  $form['reol_category_ebook_mlid'] = array(
    '#type' => 'select',
    '#title' => t('EBook menu'),
    '#default_value' => variable_get('reol_category_ebook_mlid', NULL),
    '#options' => $options,
  );

  $form['reol_category_audiobook_mlid'] = array(
    '#type' => 'select',
    '#title' => t('Audiobook menu'),
    '#default_value' => variable_get('reol_category_audiobook_mlid', NULL),
    '#options' => $options,
  );

  return system_settings_form($form);
}
