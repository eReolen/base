<?php
/**
 * @file
 * reol_two_element_paragraph.features.inc
 */

/**
 * Implements hook_paragraphs_info().
 */
function reol_two_element_paragraph_paragraphs_info() {
  $items = array(
    'two_elements' => array(
      'name' => 'To elementer',
      'bundle' => 'two_elements',
      'locked' => '1',
    ),
  );
  return $items;
}
