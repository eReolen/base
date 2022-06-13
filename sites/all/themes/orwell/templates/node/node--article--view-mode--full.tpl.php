<?php

/**
 * @file
 * Article full view mode.
 */
?>
<div class="article <?php print $classes; ?>">
  <div class="content-wrapper">
    <div class="article__image">
      <?php print render($content['field_ding_news_list_image']); ?>
    </div>
    <div class="article__content">
      <div class="article__byline">
        <span class="article__byline__date">D. <?php print $created_formatted; ?></span>
        <span class="article__byline__author"><?php print $author->name; ?>, eReolen</span>
      </div>
      <h1 class="article__title"><span class="highlight">Tema</span> / <?php print $title; ?></h1>
      <div class="article__body text">
        <?php print render($content['body']); ?>
      </div>
    </div>
  </div>

  <?php $rendered_content = render($content['field_ding_news_materials']); ?>
  <?php if (!empty($rendered_content)): ?>
    <div class="article__materials">
      <div class="content-wrapper">
        <?php print $rendered_content; ?>
      </div>
    </div>
  <?php endif ?>

  <?php $rendered_content = render($content['field_carousel']); ?>
  <?php if (!empty($rendered_content)): ?>
    <div class="article__carousel">
      <div class="content-wrapper">
        <?php print $rendered_content; ?>
      </div>
    </div>
  <?php endif ?>

  <div class="article__other-articles">
    <?php print render($other_articles); ?>
  </div>
</div>
