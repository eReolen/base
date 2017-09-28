<?php
/**
 * @file
 * reol_spotlightbox_paragraph.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function reol_spotlightbox_paragraph_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance:
  // 'paragraphs_item-spotlight_box-field_spotlight_primary'.
  $field_instances['paragraphs_item-spotlight_box-field_spotlight_primary'] = array(
    'bundle' => 'spotlight_box',
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
      'paragraphs_editor_preview' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'paragraphs_item',
    'field_name' => 'field_spotlight_primary',
    'label' => 'Video',
    'required' => 0,
    'settings' => array(
      'add_mode' => 'select',
      'allowed_bundles' => array(
        'article_carousel' => -1,
        'linkbox' => 'linkbox',
        'material_carousel' => -1,
        'spotlight_box' => -1,
      ),
      'bundle_weights' => array(
        'article_carousel' => 2,
        'linkbox' => 3,
        'material_carousel' => 4,
        'spotlight_box' => 5,
      ),
      'default_edit_mode' => 'open',
      'title' => 'Paragraph',
      'title_multiple' => 'Paragraphs',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'paragraphs',
      'settings' => array(),
      'type' => 'paragraphs_embed',
      'weight' => 0,
    ),
  );

  // Exported field_instance:
  // 'paragraphs_item-spotlight_box-field_spotlight_row_2'.
  $field_instances['paragraphs_item-spotlight_box-field_spotlight_row_2'] = array(
    'bundle' => 'spotlight_box',
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
        'weight' => 2,
      ),
      'paragraphs_editor_preview' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'paragraphs_item',
    'field_name' => 'field_spotlight_row_2',
    'label' => 'Række 2',
    'required' => 0,
    'settings' => array(
      'add_mode' => 'select',
      'allowed_bundles' => array(
        'article_carousel' => -1,
        'linkbox' => 'linkbox',
        'material_carousel' => -1,
        'spotlight_box' => -1,
      ),
      'bundle_weights' => array(
        'article_carousel' => 2,
        'linkbox' => 3,
        'material_carousel' => 4,
        'spotlight_box' => 5,
      ),
      'default_edit_mode' => 'open',
      'title' => 'Paragraph',
      'title_multiple' => 'Paragraphs',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'paragraphs',
      'settings' => array(),
      'type' => 'paragraphs_embed',
      'weight' => 2,
    ),
  );

  // Exported field_instance:
  // 'paragraphs_item-spotlight_box-field_spotlight_row_3'.
  $field_instances['paragraphs_item-spotlight_box-field_spotlight_row_3'] = array(
    'bundle' => 'spotlight_box',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'paragraphs',
        'settings' => array(
          'view_mode' => 'full',
        ),
        'type' => 'paragraphs_view',
        'weight' => 3,
      ),
      'paragraphs_editor_preview' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'paragraphs_item',
    'field_name' => 'field_spotlight_row_3',
    'label' => 'Række 3',
    'required' => 0,
    'settings' => array(
      'add_mode' => 'select',
      'allowed_bundles' => array(
        'article_carousel' => -1,
        'linkbox' => 'linkbox',
        'material_carousel' => -1,
        'spotlight_box' => -1,
      ),
      'bundle_weights' => array(
        'article_carousel' => 2,
        'linkbox' => 3,
        'material_carousel' => 4,
        'spotlight_box' => 5,
      ),
      'default_edit_mode' => 'open',
      'title' => 'Paragraph',
      'title_multiple' => 'Paragraphs',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'paragraphs',
      'settings' => array(),
      'type' => 'paragraphs_embed',
      'weight' => 3,
    ),
  );

  // Exported field_instance:
  // 'paragraphs_item-spotlight_box-field_spotlight_secondary'.
  $field_instances['paragraphs_item-spotlight_box-field_spotlight_secondary'] = array(
    'bundle' => 'spotlight_box',
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
        'weight' => 1,
      ),
      'paragraphs_editor_preview' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'paragraphs_item',
    'field_name' => 'field_spotlight_secondary',
    'label' => 'Anmeldelse',
    'required' => 0,
    'settings' => array(
      'add_mode' => 'select',
      'allowed_bundles' => array(
        'article_carousel' => -1,
        'linkbox' => 'linkbox',
        'material_carousel' => -1,
        'spotlight_box' => -1,
      ),
      'bundle_weights' => array(
        'article_carousel' => 2,
        'linkbox' => 3,
        'material_carousel' => 4,
        'spotlight_box' => 5,
      ),
      'default_edit_mode' => 'open',
      'title' => 'Paragraph',
      'title_multiple' => 'Paragraphs',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'paragraphs',
      'settings' => array(),
      'type' => 'paragraphs_embed',
      'weight' => 1,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Anmeldelse');
  t('Række 2');
  t('Række 3');
  t('Video');

  return $field_instances;
}
