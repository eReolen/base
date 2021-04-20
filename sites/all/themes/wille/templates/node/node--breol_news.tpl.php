<?php

/**
 * @file
 * Template for view mode default of Breol News node type.
 */
?>

<div class="article article--breol-news">
  <div class="article--breol_news--content article__lead">
    <?php print render($content['field_lead']); ?>
  </div>
  <div class="article__carousel">
    <?php print render($content['field_carousels']); ?>
  </div>
  <div class="article--breol_news--content article__body">
    <?php print render($content['body']); ?>
  </div>
</div>
