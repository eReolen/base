<?php
/**
 * @file
 * overdrive.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function overdrive_taxonomy_default_vocabularies() {
  return array(
    'overdrive_mapping' => array(
      'name' => 'Overdrive mapping',
      'machine_name' => 'overdrive_mapping',
      'description' => 'Mapping of searches',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
