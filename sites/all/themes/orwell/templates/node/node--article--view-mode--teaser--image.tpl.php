<?php

/**
 * @file
 * Teaser view for articles with cover image as background.
 */
?>
<div class="article--teaser--image <?php print $classes; ?>">
  <a href="<?php print $node_url; ?>">
    <div class="article--teaser--image__cover">
      <?php print render($content['field_ding_news_list_image']); ?>
    </div>
    <div class="article--teaser--image__info">
      <div class="article--teaser--image__info__inner">
        <h2 class="article--teaser--image__title"><?php print $title; ?></h2>
        <button class="article--teaser--image__read-more">
          <?php print(t('read more'))?>
        </button>
      </div>
    </div>
  </a>
</div>
