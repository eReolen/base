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
<div class="user-login">
  <?php print $content; ?>
  <?php if(!empty($count)) : ?>
    <span class="notifications__count"><?php print $count; ?></span>
  <?php endif; ?>
</div>
