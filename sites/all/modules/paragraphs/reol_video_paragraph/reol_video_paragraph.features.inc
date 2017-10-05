<?php
/**
 * @file
 * reol_video_paragraph.features.inc
 */

/**
 * Implements hook_paragraphs_info().
 */
function reol_video_paragraph_paragraphs_info() {
  $items = array(
    'video' => array(
      'name' => 'Video',
      'bundle' => 'video',
      'locked' => '1',
    ),
  );
  return $items;
}
