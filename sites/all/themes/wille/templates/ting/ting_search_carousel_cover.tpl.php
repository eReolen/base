<?php

/**
 * @file
 * Theming of carousel item.
 */
?>
<?php if ($path): ?>
  <a href="<?php print $path; ?>" class="carousel-item-link">
<?php endif; ?>
<div class="carousel-item-image <?php print $cover_classes; ?>"><?php print render($image); ?></div>
<?php if ($title): ?>
  <div class="carousel-item-title"><?php print $title; ?></div>
<?php endif; ?>
<?php if ($creator): ?>
  <div class="carousel-item-creator"><?php print $creator; ?></div>
<?php endif; ?>
<?php if ($path): ?>
  </a>
<?php endif; ?>
