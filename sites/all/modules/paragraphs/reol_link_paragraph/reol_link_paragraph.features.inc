<?php

/**
 * @file
 * reol_link_paragraph.features.inc
 */

/**
 * Implements hook_paragraphs_info().
 */
function reol_link_paragraph_paragraphs_info() {
  $items = array(
    'linkbox' => array(
      'name' => 'Linkbox',
      'bundle' => 'linkbox',
      'locked' => '1',
    ),
  );
  return $items;
}
