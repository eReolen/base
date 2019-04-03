<?php
/**
 * @{inherited} from default theme implementation to wrap menu blocks.
 *
 * Adds element to toggle mobile menu-items
 *
 */
?>
<div class="<?php print $classes; ?>">
  <div class="menu-toggle"><span class="menu-toggle-show"><?php print t('Show menu'); ?></span><span class="menu-toggle-hide"><?php print t('Hide menu'); ?></span></div>
  <?php print render($content); ?>
</div>
