<?php

/**
 * @file
 * Custom implementation of the cover image on node types.
 */
?>
<?php if ($node->type === 'breol_page' && empty($image_uri)) : ?>
  <div class="user-banner">
    <div class="user-banner__bg"></div>
    <div class="user-banner__overlay"></div>
  </div>
<?php else : ?>
  <div class="article__cover-wrapper article__cover-wrapper--<?php print $node->type; ?> cover <?php print $wrapper_class; ?>" style="background-color: <?php print $cover_background_color; ?>">
    <div class="article__cover article__cover--<?php print $node->type?>">
      <?php if (in_array($node->type, array('breol_news', 'breol_section', 'breol_page'))) : ?>
          <div class="article__cover__overlay"></div>
      <?php endif; ?>
      <div class="article__cover__content article__cover__content--<?php print $node->type?>">
        <?php if ($node->type === 'breol_subject' || $node->type === 'breol_section') : ?>
          <div class="field-name-field-subtitle">
            <?php print t('Category'); ?>
          </div>
        <?php endif; ?>
        <?php if ($node->type !== 'breol_page') : ?>
          <h2 class="title"><?php print $node->title; ?></h2>
        <?php endif; ?>
        <?php if(!empty($body)) : ?>
          <?php print($body); ?>
        <?php endif; ?>
      </div>
      <div class="article__cover__image">
        <?php if (!empty($image)) : ?>
          <?php print $image; ?>
        <?php endif; ?>
      </div>
    </div>
  </div>
<?php endif; ?>
