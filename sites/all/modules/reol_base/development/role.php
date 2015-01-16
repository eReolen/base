<?php
/**
 * @file
 * This file gets the current permissions of a user role, and displays
 * them in a way that can be used in secure_permissions hook.
 */

// The role id to get for.
$rid = 9;

// Get permissions.
$perms = user_role_permissions(array($rid => ''));

// Echo them as array structure.
echo "array(\n";
foreach ($perms[$rid] as $perm => $access) {
  if ($access) {
    echo "  '$perm',\n";
  }
}
echo ");\n";
