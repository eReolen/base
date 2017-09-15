<?php

/**
 * @file
 * Teaser view for articles with cover image as baclground.
 */
?>
<div class="article article--teaser article--teaser--image <?php print $classes; ?>">
  <a href="<?php print $node_url; ?>">
    <div class="article--teaser__cover">
      <?php print render($content['field_article_image']); ?>
    </div>
    <div class="article--teaser__info">
      <div class="article--teaser__info__inner">
        <p class="article--teaser__label"><?php print('Article'); ?></p>
        <h2 class="article--teaser__title"><?php print $title; ?></h2>
        <button class="article--teaser__read-more">
          <?php print(t('read article'))?>
        </button>
      </div>
    </div>
  </a>
</div>
