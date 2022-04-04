<?php

/**
 * @file
 * Teaser view for articles.
 */
?>
<div class="article--teaser__wrapper" >

  <div class="article--teaser__background-image">
    <?php print render($content['field_ding_news_list_image']); ?>
  </div>

  <?php if (!empty($node_url)): ?>
  <a href="<?php print $node_url; ?>">
  <?php endif; ?>

    <div class="article--teaser <?php print $classes; ?>">

      <div class="article--teaser__cover">
        <?php print render($content['field_ding_news_list_image']); ?>
      </div>

      <div class="article--teaser__subject <?php print '#000000' === ($background_contrast_color ?? NULL) ? 'color-dark' : 'color-light' ?>" style="background-color: <?php print $background_color ?? 'none' ?>">
        <?php if (isset($subject)): ?>
          <div class="subject"><?php print $subject; ?></div>
        <?php endif ?>
      </div>

      <h2 class="article--teaser__title"><?php print $title; ?></h2>

      <div class="article--teaser__body">
        <?php print render($content['body']); ?>
      </div>

      <div class="article--teaser__read-more">
        <button><?php print(t('read article'))?></button>
      </div>

      <?php if (isset($promoted_materials_covers)): ?>
        <div class="article--teaser__promoted-materials <?php if(count($promoted_materials_covers) == 1 ): ?>single<?php endif; ?>">
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
