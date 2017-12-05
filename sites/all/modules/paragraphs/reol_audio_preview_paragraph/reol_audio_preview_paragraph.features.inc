<?php
/**
 * @file
 * reol_audio_preview_paragraph.features.inc
 */

/**
 * Implements hook_paragraphs_info().
 */
function reol_audio_preview_paragraph_paragraphs_info() {
  $items = array(
    'audio_preview' => array(
      'name' => 'Lydprøve',
      'bundle' => 'audio_preview',
      'locked' => '1',
    ),
  );
  return $items;
}
