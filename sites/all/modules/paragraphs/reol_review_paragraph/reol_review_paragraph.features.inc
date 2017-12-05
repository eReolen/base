<?php
/**
 * @file
 * reol_review_paragraph.features.inc
 */

/**
 * Implements hook_paragraphs_info().
 */
function reol_review_paragraph_paragraphs_info() {
  $items = array(
    'review' => array(
      'name' => 'Litteratursiden anmeldelse',
      'bundle' => 'review',
      'locked' => '1',
    ),
  );
  return $items;
}
