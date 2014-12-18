<?php
/**
 * @file
 * reol_base.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function reol_base_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'ting_object-ting_object-ting_details_audiobook_reader'
  $field_instances['ting_object-ting_object-ting_details_audiobook_reader'] = array(
    'bundle' => 'ting_object',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'ding_entity_type' => 'ding_entity',
    'display' => array(
      'collection_list' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'collection_primary' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'inline',
        'module' => 'reol_base',
        'settings' => array(),
        'type' => 'reol_base_audiobook_reader',
        'weight' => 70,
      ),
      'review' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'search_result' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'ting_reference_preview' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'user_list' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'ting_object',
    'field_name' => 'ting_details_audiobook_reader',
    'label' => 'Reader',
    'required' => FALSE,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'hidden',
      'weight' => 15,
    ),
  );

  // Exported field_instance: 'ting_object-ting_object-ting_details_ebook_format'
  $field_instances['ting_object-ting_object-ting_details_ebook_format'] = array(
    'bundle' => 'ting_object',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'ding_entity_type' => 'ding_entity',
    'display' => array(
      'collection_list' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'collection_primary' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'inline',
        'module' => 'reol_base',
        'settings' => array(),
        'type' => 'reol_base_ebook_format',
        'weight' => 69,
      ),
      'review' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'search_result' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'ting_reference_preview' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'user_list' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'ting_object',
    'field_name' => 'ting_details_ebook_format',
    'label' => 'E-book format',
    'required' => FALSE,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'hidden',
      'weight' => 14,
    ),
  );

  // Exported field_instance: 'ting_object-ting_object-ting_details_publizon_genre'
  $field_instances['ting_object-ting_object-ting_details_publizon_genre'] = array(
    'bundle' => 'ting_object',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'ding_entity_type' => 'ding_entity',
    'display' => array(
      'collection_list' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'collection_primary' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'inline',
        'module' => 'reol_base',
        'settings' => array(),
        'type' => 'reol_base_genre',
        'weight' => 76,
      ),
      'review' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'search_result' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'ting_reference_preview' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'user_list' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'ting_object',
    'field_name' => 'ting_details_publizon_genre',
    'label' => 'Genre',
    'required' => FALSE,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'hidden',
      'weight' => 21,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('E-book format');
  t('Genre');
  t('Reader');

  return $field_instances;
}
