<?php

/**
 * @file
 * Default theme implementation for login/profile link.
 *
 * Available variables:
 * - $content: Link to login/profile.
 * - $count: Number of pending notifications.
 *
 * @ingroup themeable
 */
?>
<div>
  <?php print $content; ?>
  <span class="notifications__count"><?php print $count; ?></span>
</div>
