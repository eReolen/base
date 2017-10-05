<?php

/**
 * @file
 * Render field_video_node without any field wrappers.
 */
?>
<?php foreach ($items as $delta => $item): ?>
  <?php print render($item); ?>
<?php endforeach; ?>
