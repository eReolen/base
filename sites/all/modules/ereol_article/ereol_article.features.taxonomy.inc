<?php
/**
 * @file
 * ereol_article.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function ereol_article_taxonomy_default_vocabularies() {
  return array(
    'article_subject' => array(
      'name' => 'Article subject',
      'machine_name' => 'article_subject',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
