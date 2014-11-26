<?php
/**
 * @file
 * single_review.tpl.php
 * This template shows a single review.
 */

?>

<div class="single-review">
  <div class="top">
    <h3><?php echo t('We review'); ?></h2>
    <h2><?php echo $review_book_title; ?></h2>
    <span class="author"><?php echo t('By @author', array('@author' => $review_author)); ?></div>
  </div>
  <div class="bottom">
    <?php echo $review_cover; ?>
  </div>
</div>
