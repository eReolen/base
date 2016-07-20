<?php

/**
 * @file
 * Template for view mode default of Breol Section node type.
 */
?>

<div class="article article--breol-section">
  <div class="article__cover-wrapper">

    <div class="article__cover__overlay">
      <div class="article__cover__content article__cover__content--breol-section">
      <?php if (!empty($content['field_subtitle'])) : ?>
        <?php print drupal_render($content['field_subtitle']) ?>
      <?php endif; ?>
      <h2 class="title"><?php print $node->title; ?></h2>
    </div>
    </div>
    <div class="article__cover article__cover--breol-section"
    <?php hide($content['field_breol_cover_image']);?>
    <?php if (!empty($file_uri)) : ?>
      style="background-image: url(<?php print $file_uri; ?>)"
    <?php endif; ?>>
    </div>
  </div>
  <div class="article__carousel">
    <?php print render($content['field_carousels']); ?>
  </div>
</div>
