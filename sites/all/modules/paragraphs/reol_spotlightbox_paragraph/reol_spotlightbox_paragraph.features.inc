<?php
/**
 * @file
 * reol_spotlightbox_paragraph.features.inc
 */

/**
 * Implements hook_paragraphs_info().
 */
function reol_spotlightbox_paragraph_paragraphs_info() {
  $items = array(
    'spotlight_box' => array(
      'name' => 'Formidlingsboks',
      'bundle' => 'spotlight_box',
      'locked' => '1',
    ),
  );
  return $items;
}
