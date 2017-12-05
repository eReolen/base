<?php

/**
 * @file
 * Render ting_cover without any field wrappers.
 */
?>
<?php foreach ($items as $delta => $item): ?>
  <?php print render($item); ?>
<?php endforeach; ?>
