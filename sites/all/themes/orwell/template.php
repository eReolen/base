<?php

/**
 * Implements THEME_panels_default_style_render_region().
 *
 * Remove panel seprator markup from panels.
 */
function orwell_panels_default_style_render_region($vars) {
  $output = '';
  $output .= implode('', $vars['panes']);
  return $output;
}

/**
 * Implements hook_form_FORM_ID_alter();
 */
function orwell_form_search_block_form_alter(&$form, &$form_state, $form_id) {
  // HTML5 placeholder attribute
  $form['search_block_form']['#attributes']['placeholder'] = t('Søg efter');

  // Hide submit button.
  $form['actions']['#attributes']['class'][] = 'element-invisible';
}
