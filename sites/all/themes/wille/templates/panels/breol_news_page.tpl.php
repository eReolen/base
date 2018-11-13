<?php

/**
 * @file
 * Template for the news page.
 */
?>
<div class="news-page">
  <div class="news-page__cover-wrapper">
    <div class="news-page__cover" <?php print drupal_attributes($cover_attributes)?>>
    <div class="news-page__overlay"></div>
    <div class="news-page__cover__content">
      <div class="field-name-field-subtitle">eReolenGO</div>
      <h2 class="title"><?php print t('Nyheder'); ?></h2>
    </div>
    </div>
  </div>
  <div class="organic-element organic-element--page-news"></div>
  <div class="news-page__content"><?php print render($content); ?></div>
  <div class="news-page__pager"><?php print render($pager); ?></div>
</div>
