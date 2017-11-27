<?php

/**
 * @file
 * Render a author_portrait paragraph.
 */
?>
<div class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php if (isset($href)): ?>
    <a href='<?php print $href; ?>'>
  <?php endif; ?>
  <div class="author-portrait__image">
    <?php print $image; ?>
  </div>
  <div class="author-portrait__overlay" <?php print $overlay_attributes; ?>></div>
  <div class="author-portrait__container">
    <div class="author-portrait__content"<?php print $content_attributes; ?>>
      <?php print render($title); ?>
    </div>
  </div>
  <?php if (isset($href)): ?>
    </a>
  <?php endif; ?>
  <?php print $icons; ?>
</div>
