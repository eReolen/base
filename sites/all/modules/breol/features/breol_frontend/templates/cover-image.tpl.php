<?php
/**
 * @File
 *
 * Custom implementation of the cover image on node types.
 */
?>
<?php if ($node->type === 'breol_section') : ?>
  <div class="article__cover-wrapper">
    <div class="article__cover__overlay">
      <div class="article__cover__content article__cover__content--breol_section">
      <div class="field-name-field-subtitle">
        <?php print t('Category'); ?>
      </div>
      <h2 class="title"><?php print $node->title; ?></h2>
    </div>
    </div>
    <div class="article__cover article__cover--breol_section"
    <?php if (!empty($image_uri)) : ?>
      style="background-image: url(<?php print $image_uri; ?>)"
    <?php endif; ?>>
    </div>
  </div>
<?php elseif ($node->type === 'breol_page') : ?>
  <div class="user-banner">
    <div class="user-banner__bg"></div>
    <div class="user-banner__overlay"></div>
  </div>
<?php else : ?>
  <div class="article__cover-wrapper article__cover-wrapper--<?php print $node->type?> cover <?php print $wrapper_class?>" style="background-color: <?php print $cover_background_color; ?>">
    <div class="article__cover article__cover--<?php print $node->type?>"
      <?php if (!empty($image_uri)) : ?>
        style="background-image: url(<?php print $image_uri; ?>);"
      <?php endif; ?>>
      <?php if (in_array($node->type, array('breol_news', 'breol_section',))) : ?>
          <div class="article__cover__overlay"></div>
      <?php endif; ?>
      <div class="article__cover__content article__cover__content--<?php print $node->type?>">
        <?php if ($node->type === 'breol_subject') : ?>
          <div class="field-name-field-subtitle">
            <?php print t('Category'); ?>
          </div>
        <?php endif; ?>
        <h2 class="title"><?php print $node->title; ?></h2>
        <?php if(!empty($body)) : ?>
          <?php print($body); ?>
        <?php endif; ?>
      </div>
    </div>
  </div>
<?php endif; ?>

