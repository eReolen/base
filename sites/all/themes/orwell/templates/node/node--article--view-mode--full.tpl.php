<?php

/**
 * @file
 * Article full view mode.
 */
?>
<div class="article <?php print $classes; ?>">
  <div class="article__image content-wrapper">
    <?php print render($content['field_ding_news_list_image']); ?>
  </div>
  <div class="article__content content-wrapper">
    <div class="article__byline">
      <span class="article__byline__date">D. <?php print $created_formatted; ?></span>
      <span class="article__byline__author"><?php print $author->name; ?>, eReolen</span>
    </div>
    <h2 class="article__title"><span class="highlight">Tema</span> / <?php print $title; ?></h2>
    <div class="article__body text">
      <?php print render($content['body']); ?>
    </div>
  </div>
  <div class="article__materials">
    <div class="content-wrapper">
      <?php print render($content['field_ding_news_materials']); ?>
    </div>
  </div>
</div>
