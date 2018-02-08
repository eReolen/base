<?php
/**
 * @file
 * reol_news_paragraph.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function reol_news_paragraph_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance:
  // 'paragraphs_item-picked_article_carousel-field_picked_articles'.
  $field_instances['paragraphs_item-picked_article_carousel-field_picked_articles'] = array(
    'bundle' => 'picked_article_carousel',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'reol_news_paragraph',
        'settings' => array(),
        'type' => 'reol_article_carousel',
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
    'field_name' => 'field_picked_articles',
    'label' => 'Nyheder',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'entityreference',
      'settings' => array(
        'match_operator' => 'CONTAINS',
        'path' => '',
        'size' => 60,
      ),
      'type' => 'entityreference_autocomplete',
      'weight' => 1,
    ),
  );

  // Exported field_instance:
  // 'paragraphs_item-picked_article_carousel-field_picked_title'.
  $field_instances['paragraphs_item-picked_article_carousel-field_picked_title'] = array(
    'bundle' => 'picked_article_carousel',
    'default_value' => array(
      0 => array(
        'value' => 'Udvalgte temaer',
      ),
    ),
    'deleted' => 0,
    'description' => 'Overskrift til karrusel.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
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
    'field_name' => 'field_picked_title',
    'label' => 'Overskrift',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 40,
      ),
      'type' => 'text_textfield',
      'weight' => 0,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Nyheder');
  t('Overskrift');
  t('Overskrift til karrusel.');

  return $field_instances;
}
