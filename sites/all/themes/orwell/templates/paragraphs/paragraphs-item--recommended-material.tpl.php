<?php

/**
 * @file
 * Render a recomended material paragraph.
 */
?>
<div class="recommended-material <?php print $classes; ?>"<?php print $attributes; ?>>
  <a href="<?php print $link; ?>" target="_blank">
    <div class="recommended-material__wrapper">
      <?php print render($cover); ?>
      <div class="recommended-material__details">
        <?php print render($content['field_rec_title']); ?>
        <div class="recommended-material__meta">
          <?php print render($title); ?>
          <?php print render($author); ?>
        </div>
      </div>
    </div>
  </a>
</div>
