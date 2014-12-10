<?php
/**
 * @file
 * reol_help.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function reol_help_taxonomy_default_vocabularies() {
  return array(
    'faq_category' => array(
      'name' => 'FAQ Category',
      'machine_name' => 'faq_category',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
