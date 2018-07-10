<?php

/**
 * @file
 * Render linkbox paragraph.
 */
?>

<a href="<?php print $href ?>" class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <div class="linkbox__content"<?php print $content_attributes; ?> <?php print $attributes; ?>>
    <?php if (!empty($header)): ?>
      <h3 class="linkbox__header"><?php print $header; ?></h3>
    <?php endif; ?>
    <?php if (!empty($title)): ?>
      <h2 class="linkbox__title"><?php print $title; ?></h2>
    <?php endif; ?>
  </div>
  <?php if (!empty($image)): ?>
    <div class="linkbox__image"><?php print $image; ?></div>
  <?php endif; ?>
</a>
