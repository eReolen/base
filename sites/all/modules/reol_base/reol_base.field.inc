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
    'ting_details_audiobook_reader' => array(
      'label' => t('Reader'),
      'description' => t('The reader of the audiobook'),
      'default_widget' => 'hidden',
      'default_formatter' => 'reol_base_audiobook_reader',
      'no_ui' => TRUE,
    ),
    'ting_details_publizon_genre' => array(
      'label' => t('Genre'),
      'description' => t('The genre of the title'),
      'default_widget' => 'hidden',
      'default_formatter' => 'reol_base_genre',
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
    'reol_base_audiobook_reader' => array(
      'label' => t('Default'),
      'field types' => array(
        'ting_details_audiobook_reader',
      ),
    ),
    'reol_base_genre' => array(
      'label' => t('Default'),
      'field types' => array(
        'ting_details_publizon_genre',
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
    switch ($display['type']) {
      case 'reol_base_ebook_format':
        // Only add on ebooks.
        if (reol_base_get_type_name($entity->type) == 'ebook') {
          $pub_prod = publizon_load($entity->localId);
          // If not on publizon, do nothing.
          if (!$pub_prod) {
            continue;
          }

          $element[$delta] = array(
            '#markup' => t($pub_prod->format->name),
          );
        }
        break;

      case 'reol_base_audiobook_reader':
        // Only add on audiobooks.
        if (reol_base_get_type_name($entity->type) == 'audiobook' && $entity->reply->record['dc:contributor']['dkdcplus:dkind']) {
          $element[$delta] = array(
            '#markup' => $entity->reply->record['dc:contributor']['dkdcplus:dkind'][0],
          );
        }
        break;

      case 'reol_base_genre':
        $pub_prod = publizon_load($entity->localId);
        // If not on publizon, do nothing.
        if (!$pub_prod) {
          continue;
        }
        if (empty($pub_prod->category)) {
          continue;
        }
        $element[$delta] = array(
          '#markup' => $pub_prod->category,
        );
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
