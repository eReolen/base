<?php

/**
 * @file
 * Default theme implementation for Notifications.
 *
 * Available variables:
 * - $uri: Path to profile page.
 * - $messages: Number of pending messages.
 * - $reservations: Number of ready reservations.
 * - $debts: Number of debts.
 * - $total: Total.
 *
 * @ingroup themeable
 */
?>
<div>
  <a href="<?php print $uri; ?>">
    <span class="notifications__label">Notifications</span>
    <span class="notifications__count"><?php print $total; ?></span>
  </a>
</div>
