<?php

/**
 * @file
 * Template file for the questions section of the FAQ page if set to show
 * categorized questions at the top of the page.
 */
$all_link_shown = &drupal_static('show_all_shown', FALSE);
?>
<?php if (!$all_link_shown) : ?>
  <a href="#" id="faq-show-all"><?php echo t('Show all questions and answers'); ?></a>
  <?php $all_link_shown = TRUE; ?>
<?php endif; ?>
<div class="faq-menu">
  <a class="faq-header-link" href="#category-<?php echo $term->tid; ?>">
    <span class="faq-header">
      <?php print $header_title; ?> (<?php print $question_count; ?>)
    </span>
  </a>
</div>
