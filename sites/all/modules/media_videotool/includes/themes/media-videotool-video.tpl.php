<?php

/**
 * @file
 * Media_videotool/includes/themes/media-videotool-video.tpl.php.
 *
 * Template file for theme('media_videotool_video').
 *
 * Variables available:
 *  $uri - The media uri for the VideoTool video (e.g., videotool://v/xsy7x8c9).
 *  $video_id - The unique identifier of the VideoTool video (e.g., xsy7x8c9).
 *  $id - The file entity ID (fid).
 *  $url - The full url including query options for the VideoTool iframe.
 *  $options - An array containing the Media VideoTool formatter options.
 *  $api_id_attribute - An id attribute if the Javascript API is enabled;
 *  otherwise NULL.
 *  $width - The width value set in Media: VideoTool file display options.
 *  $height - The height value set in Media: VideoTool file display options.
 *  $title - The Media: VideoTool file's title.
 *  $alternative_content - Text to display for browsers that don't support
 *  iframes.
 */
?>
<div class="<?php print $classes; ?> media-videotool-<?php print $id; ?>">
  <iframe class="media-videotool-player" <?php print $api_id_attribute; ?>width="<?php print $width; ?>" height="<?php print $height; ?>" title="<?php print $title; ?>" src="<?php print $url; ?>" frameborder="0" allowfullscreen allow="autoplay; fullscreen"><?php print $alternative_content; ?></iframe>
</div>
