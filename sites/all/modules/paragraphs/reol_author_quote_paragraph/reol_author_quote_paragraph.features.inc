<?php
/**
 * @file
 * reol_author_quote_paragraph.features.inc
 */

/**
 * Implements hook_paragraphs_info().
 */
function reol_author_quote_paragraph_paragraphs_info() {
  $items = array(
    'author_quote' => array(
      'name' => 'Forfattercitat',
      'bundle' => 'author_quote',
      'locked' => '1',
    ),
  );
  return $items;
}
