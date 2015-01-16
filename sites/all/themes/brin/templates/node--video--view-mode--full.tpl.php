<?php

/**
 * @file
 * Template for view mode full of Video node type.
 */
?>
<div class="video-full">
  <div class="video"><?php echo render($content['field_video']); ?></div>
  <span class="title"><?php echo $title; ?></span>
  <span class="description"><?php echo render($content['body']); ?></span>
</div>
