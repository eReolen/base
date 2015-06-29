<?php
/**
 * @file
 * single_review.tpl.php
 * This template shows a single review.
 */
?>
<div class="<?php print $classes; ?>">
  <a href="<?php echo $review_uri; ?>" target="_blank">
    <div class="review-top">
      <h4><?php echo t('We review'); ?></h4>
      <h2><?php echo $ting_title; ?></h2>
      <span class="author"><?php echo t('By @author', array('@author' => $author)); ?></span>
    </div>
    <div class="review-bottom">
      <?php echo $ting_object; ?>
    </div>
  </a>
</div>
