<?php
/**
 * @file
 * reol_news_paragraph.features.inc
 */

/**
 * Implements hook_paragraphs_info().
 */
function reol_news_paragraph_paragraphs_info() {
  $items = array(
    'article_carousel' => array(
      'name' => 'Nyeste nyheds karrusel',
      'bundle' => 'article_carousel',
      'locked' => '1',
    ),
    'picked_article_carousel' => array(
      'name' => 'Nyheds karrusel',
      'bundle' => 'picked_article_carousel',
      'locked' => '1',
    ),
  );
  return $items;
}
