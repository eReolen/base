<?php

/**
 * @file
 * Gets permissions of a user role for displaying by secure_permissions hook.
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
