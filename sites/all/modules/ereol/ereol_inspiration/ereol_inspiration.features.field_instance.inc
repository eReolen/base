<?php
/**
 * @file
 * ereol_inspiration.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function ereol_inspiration_field_default_field_instances() {
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
    ),
    'entity_type' => 'node',
    'field_name' => 'field_inspiration_paragraphs',
    'label' => 'Elementer',
    'required' => 0,
    'settings' => array(
      'add_mode' => 'select',
      'allowed_bundles' => array(
        'article_carousel' => 'article_carousel',
        'audio_preview' => -1,
        'author_portrait' => -1,
        'author_quote' => -1,
        'linkbox' => -1,
        'material_carousel' => 'material_carousel',
        'newsletter_signup' => 'newsletter_signup',
        'picked_article_carousel' => 'picked_article_carousel',
        'recommended_material' => -1,
        'newsletter_signup' => 'newsletter_signup',
        'review' => -1,
        'spotlight_box' => 'spotlight_box',
        'video' => -1,
      ),
      'bundle_weights' => array(
        'article_carousel' => 2,
        'audio_preview' => 9,
        'author_portrait' => 10,
        'author_quote' => 11,
        'linkbox' => 3,
        'material_carousel' => 4,
        'newsletter_signup' => 14,
        'picked_article_carousel' => -24,
        'recommended_material' => 15,
        'review' => 5,
        'spotlight_box' => 6,
        'video' => 18,
      ),
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
      'weight' => 41,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Elementer');

  return $field_instances;
}
