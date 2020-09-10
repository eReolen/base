<?php

/**
 * @file
 * Theme ting_collection_types field.
 */
?>
<div class="availability search-result--availability">
  <?php if (!$label_hidden): ?>
      <strong><?php print $label ?>:</strong>
  <?php endif; ?>
  <?php foreach ($items as $delta => $item): ?>
    <?php print render($item); ?>
  <?php endforeach; ?>
</div>
