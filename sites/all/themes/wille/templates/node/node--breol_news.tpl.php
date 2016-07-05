<?php

/**
 * @file
 * Template for view mode default of Breol News node type.
 */

// Start by hiding all content.
;
?>

<div class="article article--breol-news">
  <div class="article__cover"
  <?php if (!empty($file_uri)) : ?>
    style="background-image: url(<?php print $file_uri; ?>)"
  <?php endif; ?>>
    <div class="article__cover__overlay"></div>
    <div class="article__cover__content">
      <h2><?php print $node->title; ?></h2>
      <?php
        print render($content['body']);
        // Hide carousel, we'll render it in its own container.
        hide($content['field_carousels']);
        print render($content); ?>
    </div>
  </div>
  <div class="article__carousel">
    <?php print render($content['field_carousels']); ?>
  </div>
</div>
