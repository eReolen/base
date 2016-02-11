<?php
/**
 * Integrate with Drush to detect control of maintenance mode via Drush.
 */

/**
 * Implements drush_hook_pre_command().
 */
function drush_maintenance_mode_api_pre_variable_set($variable_name, $value) {
  if ($variable_name == 'maintenance_mode') {
    // User is setting the 'maintenance_mode' variable: record the initial
    // state.
    _drush_maintenance_mode_api__pre_state(variable_get('maintenance_mode', 0));
  }
}

/**
 * Implements drush_hook_post_command().
 */
function drush_maintenance_mode_api_post_variable_set($variable_name, $value) {
  if ($variable_name == 'maintenance_mode') {
    // Check the pre-state and compare with the new state.
    $pre_state = _drush_maintenance_mode_api__pre_state();
    $new_state = (bool) $value;
    if ($pre_state != $new_state) {
      module_invoke_all('change_maintenance_mode', $new_state);
    }
  }
}

/**
 * Static cache to track pre-state in order to detect state change.
 */
function _drush_maintenance_mode_api__pre_state($state = NULL) {
  static $pre_state = NULL;
  if (!is_null($state)) {
    $pre_state = $state;
  }
  return $pre_state;
}
