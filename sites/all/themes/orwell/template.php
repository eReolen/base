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
