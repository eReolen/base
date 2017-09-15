<?php

/**
 * @file
 * Teaser view for articles.
 */
?>
<div class="article article--teaser <?php print $classes; ?>">
  <a href="<?php print $node_url; ?>">
    <div class="article--teaser__cover">
      <?php print render($content['field_article_image']); ?>
    </div>
    <div class="article--teaser__left article--teaser__info">
      <div class="article--teaser__info__inner">
        <h2 class="article--teaser__title"><?php print $title; ?></h2>
        <div class="article--teaser__body">
          <?php print render($content['body']); ?>
        </div>
        <button class="article--teaser__read-more">
          <?php print(t('read article'))?>
        </button>
      </div>
    </div>
    <div class="article--teaser__right">
      <div class="article--teaser__covers">
        <?php foreach ($covers as $cover): ?>
          <?php print($cover); ?>
        <?php endforeach; ?>
      </div>
    </div>
  </a>
</div>
