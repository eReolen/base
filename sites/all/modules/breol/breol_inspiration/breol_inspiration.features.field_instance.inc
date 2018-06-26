<?php
/**
 * @file
 * breol_inspiration.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function breol_inspiration_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-inspiration-field_inspiration_paragraphs'.
  $field_instances['node-inspiration-field_inspiration_paragraphs'] = array(
    'bundle' => 'inspiration',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'paragraphs',
        'settings' => array(
          'view_mode' => 'full',
        ),
        'type' => 'paragraphs_view',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 1,
      ),
      'teaser_medium' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 1,
      ),
      'teaser_small' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_inspiration_paragraphs',
    'label' => 'Elementer',
    'required' => 0,
    'settings' => array(
      'add_mode' => 'select',
      'allowed_bundles' => array(),
      'bundle_weights' => array(),
      'default_edit_mode' => 'open',
      'title' => 'Element',
      'title_multiple' => 'Elementer',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'paragraphs',
      'settings' => array(),
      'type' => 'paragraphs_embed',
      'weight' => 5,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Elementer');

  return $field_instances;
}
