<?php

/**
 * @file
 * Defoult carousel template.
 *
 * Available variables:
 * - $title: Title of carousel.
 * - $items: individual items of the carousel.
 * - $offset: Ajax callback offset to start at. -1 for no ajax.
 * - $path: Ajax path for getting more content.
 */
?>
<div class="<?php print $classes; ?>"
  data-title="<?php print $title ?>"
  data-offset="<?php print $offset; ?>"
  data-path="<?php print $path; ?>"
  data-settings="<?php print htmlentities(json_encode($slick_settings)); ?>"
  >
  <h2 class="carousel__header">
    <?php if (!empty($carousel['#more_link'])): ?>
      <span class="carousel__more-link">
        <?php print($carousel['#more_link']); ?>
      </span>
    <?php endif; ?>
    <?php
      // A hack for handling carousel with empty title.
      print $title ?: '&nbsp';
    ?>
  </h2>
  <ul class="carousel"><?php print render($items); ?></ul>
</div>
