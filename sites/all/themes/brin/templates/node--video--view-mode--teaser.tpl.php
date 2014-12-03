<?php

/**
 * @file
 * Template for view mode teaser of Video node type.
 */
?>
<div class="video-teaser">
  <div class="video-thumb"><?php echo render($content['field_video']); ?></div>
  <span class="title"><?php echo $title; ?></span>
  <div class="play"></div>
</div>
