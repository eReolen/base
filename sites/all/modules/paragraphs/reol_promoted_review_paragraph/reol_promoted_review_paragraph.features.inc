<?php
/**
 * @file
 * reol_promoted_review_paragraph.features.inc
 */

/**
 * Implements hook_paragraphs_info().
 */
function reol_promoted_review_paragraph_paragraphs_info() {
  $items = array(
    'promoted_review' => array(
      'name' => 'Fremhævet anmeldelse',
      'bundle' => 'promoted_review',
      'locked' => '1',
    ),
  );
  return $items;
}
