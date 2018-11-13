<?php

/**
 * @file
 * Template for view mode teaser of Author portrait node type.
 */
?>
<div class="author-portrait-teaser <?php print $classes; ?>">
  <a href="<?php echo $link; ?>" target=_blank">
    <div class="portrait"><?php echo render($content['field_portrait']); ?></div>
    <h2><?php echo $title; ?></h2>
    <span class="portrait-link"><?php echo t('Author portrait'); ?> >></span>
  </a>
</div>
