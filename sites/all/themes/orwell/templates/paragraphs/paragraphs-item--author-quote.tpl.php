<?php

/**
 * @file
 * Render a author quote paragraph.
 */
?>
<div class="author-quote <?php print $classes; ?>"<?php print $attributes; ?>>
  <a href="<?php print $link; ?>">
      <?php print $icons; ?>
    <div class="author-quote__wrapper">
      <div class="author-quote__author"><?php print $author; ?></div>
      <blockquote class="author-quote__quote"><?php print $quote; ?></blockquote>
      <div class="author-quote__attribution"><?php print $attribution; ?></div>
    </div>
  </a>
</div>
