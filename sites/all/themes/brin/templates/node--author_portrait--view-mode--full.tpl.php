<?php

/**
 * @file
 * Template for view mode full of Author portrait node type.
 */
?>
<div class="author-portrait">
  <a href="<?php echo $link; ?>" target=_blank">
    <?php echo render($content['field_portrait']); ?>
  </a>
  <a href="<?php echo $link; ?>" target="_blank" class="button arrow-right"><?php echo t('Go to the author portrait on Forfatterweb.dk'); ?></a>
</div>
