<?php
/**
 * @file
 * reol_author_portrait_paragraph.features.inc
 */

/**
 * Implements hook_paragraphs_info().
 */
function reol_author_portrait_paragraph_paragraphs_info() {
  $items = array(
    'author_portrait' => array(
      'name' => 'Forfatterportræt',
      'bundle' => 'author_portrait',
      'locked' => '1',
    ),
  );
  return $items;
}
