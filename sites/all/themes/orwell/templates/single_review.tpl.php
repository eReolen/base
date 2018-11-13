<?php

/**
 * @file
 * This template shows a single review.
 */
?>
<div class="review <?php print $classes; ?>">
  <a href="<?php print $review_uri; ?>" target="_blank">
    <div class="review__wrapper">
      <div class="review__cover">
        <?php print render($ting_object['ting_cover']); ?>
      </div>
      <div class="review__content">
        <div class="review__head">
          <h4><?php print t('Review'); ?></h4>
          <div class="review__subhead">fra &mdash;<span class="review__highlight">Litteratursiden.dk</span></div>
        </div>
        <?php print render($ting_object['ting_cover']); ?>
        <div class="review__meta">
          <?php print render($ting_object['ting_title']); ?>
          <?php print render($ting_object['ting_author']); ?>
        </div>
      </div>
    </div>
    <?php print $icons; ?>
  </a>
</div>
