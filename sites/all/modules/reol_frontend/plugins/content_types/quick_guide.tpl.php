<?php
/**
 * @file
 * quick_guide.tpl.php
 * This template shows the quick guide.
 */

?>
<div class="quick-guide">
  <h2><?php echo $title; ?></h2>
  <strong><?php echo render($lead); ?></strong>
  <?php echo render($body); ?>
</div>
