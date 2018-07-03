<?php
/**
 * @file
 * breol_see_all_news_button_paragraph.features.inc
 */

/**
 * Implements hook_paragraphs_info().
 */
function breol_see_all_news_button_paragraph_paragraphs_info() {
  $items = array(
    'see_all_news_button' => array(
      'name' => 'Se alle nyheder link',
      'bundle' => 'see_all_news_button',
      'locked' => '1',
    ),
  );
  return $items;
}
