<?php

/**
 * @file
 * Template for view mode teaser of Video node type.
 */
?>
<div class="video-teaser<?php if (isset($type)) : echo ' type-icon type-icon-' . $type; endif; ?>">
  <a href="<?php echo $link; ?>" class="use-ajax">
    <div class="video-thumb"><?php echo render($content['field_video']); ?></div>
    <span class="title"><?php echo $title; ?></span>
    <div class="play"></div>
  </a>
</div>
