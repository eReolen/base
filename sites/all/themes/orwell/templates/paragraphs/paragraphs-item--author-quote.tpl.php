<?php

/**
 * @file
 * Render a author quote paragraph.
 */
?>
<div class="author-quote <?php print $classes; ?>"<?php print $attributes; ?>>
  <a href="<?php print $link; ?>">
    <div class="author-quote__wrapper">
      <?php print $icons; ?>
      <div class="author-quote__author"><?php print $author; ?></div>
      <blockquote class="author-quote__quote"><q><?php print $quote; ?></q></blockquote>
      <div class="author-quote__attribution"><?php print $attribution; ?></div>
    </div>
  </a>
</div>
