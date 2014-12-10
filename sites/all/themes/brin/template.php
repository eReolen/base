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
