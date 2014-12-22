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
  // Remove minified version of scripts we have overridden.
  unset($javascript['profiles/ding2/themes/ddbasic/scripts/ddbasic.topbar.menu.min.js']);
  unset($javascript['profiles/ding2/themes/ddbasic/scripts/ddbasic.search.min.js']);

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
 * Implements hook_ting_view_alter().
 *
 * Fix all fieldgroups to be open.
 */
function brin_ting_view_alter(&$build) {
  foreach ($build['#groups'] as $group) {
    if ($group->format_settings['formatter'] == 'collapsed') {
      $group->format_settings['formatter'] = 'open';
    }
  }
}

/**
 * Implements hook_preprocess_ting_object().
 */
function brin_preprocess_ting_object(&$variables) {
  // Remove the type prefix from the title of the first material of
  // the collection.
  if (!empty($variables['content']['ting_primary_object'][0]['ting_title'][0]['title']['#prefix'])) {
    unset($variables['content']['ting_primary_object'][0]['ting_title'][0]['title']['#prefix']);
  }

  if ($variables['object'] instanceof TingCollection) {
    // Move the availability field into the primary ting object
    // render array to allow it to be printed as part of the object
    // template. It's further processed in the else statement.
    if (isset($variables['content']['ting_collection_types'])) {
      $variables['content']['ting_primary_object'][0]['ting_collection_types'] = $variables['content']['ting_collection_types'];
      unset($variables['content']['ting_collection_types']);
    }

    // Only do this if we only have one entity to look at.
    if (count($variables['object']->entities) == 1) {
      $ting_entity = ding_entity_load($variables['object']->ting_primary_object['und'][0]['id']);
      $variables['content']['ting_primary_object'][0]['ting_cover']['#prefix'] = '<div class="type-icon type-icon-' . reol_base_get_type_name($ting_entity->type) . '">';
      $variables['content']['ting_primary_object'][0]['ting_cover']['#suffix'] = '</div>';
    }
  }
  else {
    // Move the availability field from above into the fieldgroup
    // wrapper, now that fieldgroup has processed it.
    if (isset($variables['content']['ting_collection_types']) && isset($variables['content']['group_ting_right_col_search'])) {

      $variables['content']['group_ting_right_col_search']['ting_collection_types'] = $variables['content']['ting_collection_types'];
      $variables['content']['group_ting_right_col_search']['ting_collection_types']['#weight'] = 100;
      unset($variables['content']['ting_collection_types']);
    }

    $ting_entity = $variables['object'];
    $variables['content']['ting-object']['content']['left_column']['ting_cover']['#prefix'] = '<div class="type-icon type-icon-' . reol_base_get_type_name($ting_entity->type) . '">';
    $variables['content']['ting-object']['content']['left_column']['ting_cover']['#suffix'] = '</div>';
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

/**
 * Theme menu links.
 *
 * Add use ajax to login links.
 */
function brin_menu_link($vars) {
  $element = $vars['element'];

  // Render any sub-links/menus.
  $sub_menu = '';
  if ($element['#below']) {
    $sub_menu = drupal_render($element['#below']);
  }

  // Add default class to a tag.
  $element['#localized_options']['attributes']['class'] = array(
    'menu-item',
  );

  if (isset($element['#original_link'])) {
    // If this element uses ajax, add class and load ajax.
    if (isset($element['#original_link']['delivery_callback']) && $element['#original_link']['delivery_callback'] == "ajax_deliver") {
      drupal_add_library('system', 'drupal.ajax');
      $element['#localized_options']['attributes']['class'][] = 'use-ajax';
    }

    // If element is pointing to /login, and user is logged in, do not show.
    if ($element['#original_link']['link_path'] == 'login' && user_is_logged_in()) {
      return '';
    }
  }

  // Filter classes.
  $element['#attributes']['class'] = ddbasic_remove_default_link_classes($element['#attributes']['class']);

  // Make sure text string is treated as html by l function.
  $element['#localized_options']['html'] = TRUE;

  $link = l('<span>' . $element['#title'] . '</span>', $element['#href'], $element['#localized_options']);

  return '<li' . drupal_attributes($element['#attributes']) . '>' . $link . $sub_menu . "</li>\n";
}

/**
 * Add ajax for all pages.
 */
function brin_preprocess_html(&$variables) {
  drupal_add_library('system', 'drupal.ajax');
}
