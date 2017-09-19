<?php

/**
 * @file
 * ereol_frontend.features.inc
 */

/**
 * Implements hook_image_default_styles().
 */
function ereol_frontend_image_default_styles() {
  $styles = array();

  // Exported image style: ereol_cover_base.
  $styles['ereol_cover_base'] = array(
    'label' => 'eReol cover base',
    'effects' => array(
      1 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 260,
          'height' => 375,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}
