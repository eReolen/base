<?php

/**
 * @file
 * Template for the news page.
 *<div><?php print $image; ?></div>
 */
?>
<div class="news-page">
  <div class="news-page__cover-wrapper">
    <div class="news-page__cover" style="background-image: url(<?php print $image_file_uri ?>);">
    <div class="news-page__overlay"></div>
    <div class="news-page__cover__content">
      <div class="field-name-field-subtitle">eReolenGO</div>
      <h2 class="title"><?php print t('Nyheder'); ?></h2>
    </div>
    </div>
  </div>
  <div class="organic-element organic-element--page-news">
    <?php print $organic_svg ?>
  </div>
  <div><?php print $fancy_box; ?></div>
  <div><?php print $pager; ?></div>
</div>
