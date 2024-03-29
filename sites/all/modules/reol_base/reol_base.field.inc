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
    'reol_base_lix' => array(
      'label' => t('Material Lix number'),
      'description' => t('The Lix number of the material'),
      'default_widget' => 'hidden',
      'default_formatter' => 'reol_base_lix',
      'virtual_field' => array(
        'entity_types' => array('ting_object'),
        'add_widget' => TRUE,
      ),
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
    'reol_base_author_plain' => array(
      'label' => t('Plain author'),
      'field types' => array(
        'ting_author',
      ),
    ),
    'reol_base_lix' => array(
      'label' => t('Default'),
      'field types' => array(
        'reol_base_lix',
      ),
    ),
    'reol_base_series' => array(
      'label' => t('Reol base series'),
      'field types' => array(
        'ting_series',
      ),
    ),
  );
}

/**
 * Implements hook_field_formatter_view().
 */
function reol_base_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  foreach ($items as $delta => $item) {
    switch ($display['type']) {
      case 'reol_base_ebook_format':
        // Only add on ebooks.
        if (reol_base_get_type_name($entity->type) == 'ebook') {
          $pub_prod = publizon_load($entity->localId);
          // If not on publizon, do nothing.
          if (!$pub_prod) {
            break;
          }

          $element[$delta] = array(
            // phpcs:ignore
            '#markup' => t($pub_prod->format->name),
          );
        }
        break;

      case 'reol_base_audiobook_reader':
        // Only add on audiobooks.
        if (reol_base_get_type_name($entity->type) == 'audiobook' && !empty($entity->reply->record['dc:contributor']['dkdcplus:dkind'])) {
          $items = $entity->reply->record['dc:contributor']['dkdcplus:dkind'];
          // @todo When/if DDF figures out how to search for a narrator we
          // should map the names to a search link, i.e.
          //
          // $items = array_map(
          //   static function ($value) {
          //     return l($value, 'search/ting/phrase.narrator="' . $value . '"');
          //   },
          //   $entity->reply->record['dc:contributor']['dkdcplus:dkind']
          // );
          $element[$delta] = array(
            '#markup' => implode(', ', $items),
          );
        }
        break;

      case 'reol_base_genre':
        $pub_prod = publizon_load($entity->localId);
        // If not on publizon, do nothing.
        if (!$pub_prod) {
          break;
        }
        if (empty($pub_prod->category)) {
          break;
        }
        $element[$delta] = array(
          '#markup' => $pub_prod->category,
        );
        break;

      case 'reol_base_author_plain':
        $element[$delta] = array(
          '#markup' => check_plain(implode(', ', $entity->creators)),
        );
        break;

      case 'reol_base_lix':
        if ($entity->reply->lix) {
          $element[$delta] = array(
            '#markup' => check_plain($entity->reply->lix),
          );
        }
        break;

      case 'reol_base_series':
        $data = reol_base_get_series_data($entity);
        if (NULL !== $data) {
          // This is almost as ugly as the stuff in ting_field_formatter_view.
          $element[$delta] = array(
            '#markup' => '<span class="material__series-number">' . $data['number'] . '</span>'
            . '<span class="material__series-series" title="' . $data['series'] . '">' . $data['series'] . '</span>',
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
