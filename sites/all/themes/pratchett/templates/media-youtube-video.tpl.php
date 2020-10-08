<?php

/**
 * @file
 * Template file for theme('media_youtube_video').
 *
 * Variables available:
 *  $uri - The media uri for the YouTube video (e.g., youtube://v/xsy7x8c9).
 *  $video_id - The unique identifier of the YouTube video (e.g., xsy7x8c9).
 *  $id - The file entity ID (fid).
 *  $url - The full url including query options for the Youtube iframe.
 *  $options - An array containing the Media Youtube formatter options.
 *  $api_id_attribute - An id attribute if the Javascript API is enabled;
 *  otherwise NULL.
 *  $width - The width value set in Media: Youtube file display options.
 *  $height - The height value set in Media: Youtube file display options.
 *  $title - The Media: YouTube file's title.
 *  $alternative_content - Text to display for browsers that don't support
 *  iframes.
 */
?>

<div class="<?php print $classes; ?> media-youtube-<?php print $id; ?>">
  <div class="expand-parent-to expand-parent-to--16-9"">
    <span class="media-youtube-video--disabled">
      <span><?php print t('To show this video you must allow marketing cookies.');?></span>
      <a href="javascript:CookieConsent.renew()"><?php print t("Change cookie consent"); ?></a>
    </span>
  </div>
  <iframe class="media-youtube-player"<?php print $api_id_attribute; ?>width="<?php print $width; ?>" height="<?php print $height; ?>" title="<?php print $title; ?>" data-category-consent="cookie_cat_marketing" data-consent-src="<?php print $url; ?>" src="" frameborder="0" allowfullscreen><?php print $alternative_content; ?></iframe>
</div>
