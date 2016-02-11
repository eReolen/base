<?php

/**
 * React to a change in the maintenance mode of the site.
 *
 * @param Boolean $maintenance_mode
 * TRUE if the site is being set into maintenance mode.
 * FALSE if maintenance mode is being deactivated.
 */
function hook_change_maintenance_mode($maintenance_mode) {
  // Log when the mainenance mode is changed.
  global $user;
  if ($maintenance_mode) {
    watchdog('Maintenance mode', 'Site switched to maintenance mode by @username.', array('@username' => $user->name));
  }
  else {
    watchdog('Maintenance mode', 'Site switched to normal mode by @username.', array('@username' => $user->name));
  }
}
