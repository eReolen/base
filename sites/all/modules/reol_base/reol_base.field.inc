<?php
/**
 * @file
 * Defines the extra field for the ting entities and formatters for the fields.
 */

/**
 * Implements hook_field_info().
 */
function reol_base_field_info() {
  return array(
    'ting_details_ebook_format' => array(
      'label' => t('E-book format'),
      'description' => t('The digital format of the E-book'),
      'default_widget' => 'hidden',
      'default_formatter' => 'reol_base_ebook_format',
      'no_ui' => TRUE,
    ),
  );
}

/**
 * Implements hook_field_formatter_info().
 */
function reol_base_field_formatter_info() {
  return array(
    'reol_base_ebook_format' => array(
      'label' => t('Default'),
      'field types' => array(
        'ting_details_ebook_format',
      ),
    ),
  );
}

/**
 * Implements hook_field_formatter_view().
 */
function reol_base_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  foreach ($items as $delta => $items) {
    $pub_prod = publizon_load($entity->localId);
    // If not on publizon, do nothing.
    if (!$pub_prod) {
      continue;
    }

    switch ($display['type']) {
      case 'reol_base_ebook_format':
        // Only add on ebooks.
        if (reol_base_get_type_name($entity->type) == 'ebook') {
          $element[$delta] = array(
            '#markup' => t($pub_prod->format->name),
          );
        }
        break;
    }
  }

  return $element;
}

/**
 * Implements hook_field_load().
 */
function reol_base_field_load($entity_type, $entities, $field, $instances, $langcode, &$items, $age) {
  foreach ($entities as $id => $entity) {
    $items[$id][0] = array(
      'id' => $id,
    );
  }
}
