<?php

/**
 * @file
 * Render a linkbox paragraph.
 */
?>
<div class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php if (isset($href)): ?>
    <a href='<?php print $href; ?>'>
  <?php endif; ?>
  <div class="linkbox__container">
    <div class="linkbox__content"<?php print $content_attributes; ?>>
      <?php print $title; ?>
    </div>
  </div>
  <?php if (isset($href)): ?>
    </a>
  <?php endif; ?>
</div>
