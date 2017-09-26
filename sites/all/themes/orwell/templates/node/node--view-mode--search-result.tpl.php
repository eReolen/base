<?php

/**
 * @file
 * Teaser view for articles.
 */
?>
<div class="article article--search-result <?php print $classes; ?>">
  <a href="<?php print $node_url; ?>">
    <div class="article--search-result__left">
      <div class="article--search-result__cover">
        <?php print render($content['field_ding_news_list_image']) ?>
      </div>
    </div>
    <div class="article--search-result__right article--search-result__info">
      <div class="article--search-result__info__inner">
        <h2 class="article--search-result__title"><?php print $title; ?></h2>
        <div class="article--search-result__body desktop-only">
          <?php print render($content['body']); ?>
        </div>
      </div>
    </div>
  </a>
</div>
