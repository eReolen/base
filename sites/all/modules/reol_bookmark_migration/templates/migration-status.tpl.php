<?php
/**
 * @file
 * migration-status.tpl.php
 * Contains the theme of the status page.
 */
?>
<div class="migration-status">
  <h2><?php echo t('Bookmark migration status'); ?></h2>

  <?php echo $migrated_users_progress; ?>
  <p><?php echo t('Note: Total is total for both sites, and all users might be present on both, adding 2 to the count.'); ?></p>
  <div>&nbsp;</div>
  <?php echo $migrated_isbns_progress; ?>
</div>
