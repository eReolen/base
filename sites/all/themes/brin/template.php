<?php

/**
 * @file
 * Preprocess and Process Functions.
 */

/**
 * Implements hook_form_alter().
 */
function brin_form_alter(&$form, &$form_state, $form_id) {
  switch ($form_id) {
    case 'search_block_form':
      // Undo the un-hiding ddbasic does.
      $form['search_block_form']['#title_display'] = 'invisible';

      // Remove the standard search icon.
      unset($form['search_block_form']['#field_prefix']);
      break;
  }
}

/**
 * Implements hook_js_alter().
 */
function brin_js_alter(&$javascript) {
  // Remove minified version of script we have overridden.
  unset($javascript['profiles/ding2/themes/ddbasic/scripts/ddbasic.topbar.menu.min.js']);
}

/**
 * Implements hook_preprocess_node().
 */
function brin_preprocess_node(&$variables, $hook) {
  // Add tpl suggestions for node view modes on node type.
  if (isset($variables['view_mode'])) {
    $variables['theme_hook_suggestions'][] = 'node__' . $variables['node']->type . '__view_mode__' . $variables['view_mode'];
  }
}

/**
 * Implements theme_menu_tree().
 */
function brin_menu_tree__menu_block__main_menu($vars) {
  return '<ul class="main-menu">' . $vars['tree'] . '</ul>';
}

/**
 * Implements theme_faq_page().
 */
function brin_faq_page($variables) {
  $content = $variables['content'];
  $answers = $variables['answers'];
  $description = $variables['description'];
  $output = '<div class="faq-content"><div class="faq">';
  if (!empty($description)) {
    $output .= '<div class="faq-description">' . $description . "</div>\n";
  }
  if (variable_get('faq_show_expand_all', FALSE)) {
    $output .= '<div id="faq-expand-all">';
    $output .= '<a class="faq-expand-all-link" href="#faq-expand-all-link">[' . t('expand all') . ']</a>';
    $output .= '<a class="faq-collapse-all-link" href="#faq-collapse-all-link">[' . t('collapse all') . ']</a>';
    $output .= "</div>\n";
  }

  $output .= '<div class="faq-questions">' . $content . '</div>';
  $output .= '<div class="faq-answers">' . $answers . "</div></div></div>\n";
  return $output;
}

/**
 * Returns HTML for a textfield form element.
 *
 * Basically theme_textfield with the size attribute removed.
 */
function brin_textfield($variables) {
  $element = $variables['element'];
  $element['#attributes']['type'] = 'text';
  element_set_attributes($element, array('id', 'name', 'value', 'maxlength'));
  _form_set_class($element, array('form-text'));

  $extra = '';
  if ($element['#autocomplete_path'] && drupal_valid_path($element['#autocomplete_path'])) {
    drupal_add_library('system', 'drupal.autocomplete');
    $element['#attributes']['class'][] = 'form-autocomplete';

    $attributes = array();
    $attributes['type'] = 'hidden';
    $attributes['id'] = $element['#attributes']['id'] . '-autocomplete';
    $attributes['value'] = url($element['#autocomplete_path'], array('absolute' => TRUE));
    $attributes['disabled'] = 'disabled';
    $attributes['class'][] = 'autocomplete';
    $extra = '<input' . drupal_attributes($attributes) . ' />';
  }

  $output = '<input' . drupal_attributes($element['#attributes']) . ' />';

  return $output . $extra;
}

/**
 * Theme function to render an webform email component.
 *
 * Basically theme_webform_email with the size attribute removed.
 */
function brin_webform_email($variables) {
  $element = $variables['element'];

  // This IF statement is mostly in place to allow our tests to set type="text"
  // because SimpleTest does not support type="email".
  if (!isset($element['#attributes']['type'])) {
    $element['#attributes']['type'] = 'email';
  }

  // Convert properties to attributes on the element if set.
  foreach (array('id', 'name', 'value') as $property) {
    if (isset($element['#' . $property]) && $element['#' . $property] !== '') {
      $element['#attributes'][$property] = $element['#' . $property];
    }
  }
  _form_set_class($element, array('form-text', 'form-email'));

  return '<input' . drupal_attributes($element['#attributes']) . ' />';
}
