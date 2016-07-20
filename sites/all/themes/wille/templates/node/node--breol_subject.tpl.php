<?php

/**
 * @file
 * Template for view mode default of Breol Section node type.
 */
dpm($cover_background_color);
?>

<div class="article article--breol-section">
  <div class="article__cover-wrapper article__cover-wrapper--breol-subject" style="background-color: <?php print $cover_background_color; ?>">
    <div class="article__cover article__cover--breol-subject"
    <?php hide($content['field_breol_cover_image']);?>
    <?php if (!empty($file_uri)) : ?>
      style="background-image: url(<?php print $file_uri; ?>);"
    <?php endif; ?>>
    <div class="article__cover__content article__cover__content--breol-section">
      <div class="field-name-field-subtitle">
        <?php print t('Category'); ?>
      </div>
      <h2 class="title"><?php print $node->title; ?></h2>
    </div>
    </div>
  </div>
</div>
