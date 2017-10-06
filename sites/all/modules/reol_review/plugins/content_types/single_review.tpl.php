<?php

/**
 * @file
 * This template shows a single review.
 */
?>
<div class="<?php print $classes; ?>">
  <a href="<?php echo $review_uri; ?>" target="_blank">
    <div class="review-top">
      <h4><?php print t('We review'); ?></h4>
      <h2><?php print $ting_title; ?></h2>
      <span class="author"><?php print t('By @author', array('@author' => $author)); ?></span>
    </div>
    <div class="review-bottom">
      <?php print render($ting_object); ?>
    </div>
  </a>
</div>
