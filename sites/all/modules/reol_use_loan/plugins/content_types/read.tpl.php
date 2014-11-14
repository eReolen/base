<?php
/**
 * @file
 * read.tpl.php
 * This template shows the read widget for reading
 * to an ebook.
 */

drupal_add_css(drupal_get_path('module', 'reol_use_loan') . '/css/reader.css');
drupal_add_js(drupal_get_path('module', 'reol_use_loan') . '/js/reader.js');
?>
<div class="reader">
  <div class="fullscreen-toggle">
    <div class="icon">
      <div class="arrow left-top"></div>
      <div class="arrow left-bottom"></div>
      <div class="arrow right-top"></div>
      <div class="arrow right-bottom"></div>
    </div>
    <span class="tooltip"><?php echo t('View in fullscreen'); ?></span>
  </div>
  <iframe src="/reol_use_loan/reader/<?php echo $retailer_order_number; ?>"></iframe>
</div>
