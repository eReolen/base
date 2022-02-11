<?php

/**
 * @file
 * Teaser view for articles.
 */
?>
<div class="article article--teaser <?php print $classes; ?>">
  <?php if (!empty($node_url)): ?>
  <a href="<?php print $node_url; ?>">
  <?php endif; ?>
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

    <div class="article--teaser__right <?php print '#000000' === ($background_contrast_color ?? NULL) ? 'color-dark' : 'color-light' ?>" style="background-color: <?php print $background_color ?? 'none' ?>">
      <?php if (isset($subject)): ?>
        <div class="subject"><?php print $subject; ?></div>
      <?php endif ?>
      <?php if (isset($promoted_materials_covers)): ?>
        <div class="article--teaser__covers">
          <?php foreach ($promoted_materials_covers as $cover): ?>
            <?php print($cover); ?>
          <?php endforeach; ?>
        </div>
      <?php endif; ?>
    </div>
  <?php if (!empty($node_url)): ?>
  </a>
  <?php endif; ?>
</div>
