<?php
/**
 * @file
 * reol_app_feeds.features.inc
 */

/**
 * Implements hook_image_default_styles().
 */
function reol_app_feeds_image_default_styles() {
  $styles = array();

  // Exported image style: app_feed_image.
  $styles['app_feed_image'] = array(
    'label' => 'App feed image',
    'effects' => array(
      2 => array(
        'name' => 'manualcrop_crop_and_scale',
        'data' => array(
          'width' => 500,
          'height' => 500,
          'upscale' => 0,
          'respectminimum' => 1,
          'onlyscaleifcrop' => 0,
          'style_name' => 'app_feed_image',
        ),
        'weight' => 0,
      ),
    ),
  );

  return $styles;
}
