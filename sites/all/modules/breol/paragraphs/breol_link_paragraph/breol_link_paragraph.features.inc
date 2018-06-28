<?php
/**
 * @file
 * breol_link_paragraph.features.inc
 */

/**
 * Implements hook_paragraphs_info().
 */
function breol_link_paragraph_paragraphs_info() {
  $items = array(
    'breol_linkbox' => array(
      'name' => 'Linkbox',
      'bundle' => 'breol_linkbox',
      'locked' => '1',
    ),
  );
  return $items;
}
