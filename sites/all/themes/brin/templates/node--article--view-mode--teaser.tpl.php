<?php

/**
 * @file
 * Template for view mode teaser of Article node type.
 */
?>

<div class="article-teaser">
  <div class="article-left">
    <?php echo render($content['field_ding_news_list_image']); ?>
  </div>
  <div class="article-right">
    <div class="article-background">
      <?php echo render($image_background); ?>
    </div>
    <h2><?php echo $title; ?></h2>
    <div class="article-body"><?php echo render($content['body']); ?></div>
    <div class="read-more"><?php echo render($content['links']); ?></div>
  </div>
</div>
