<?php

namespace Drupal\reol_app_feeds\Feed;

use Drupal\reol_app_feeds\Helper\NodeHelper;
use EntityFieldQuery;

/**
 * Themes feed.
 *
 * @package Drupal\reol_app_feeds\Feed
 */
class ThemesFeed extends AbstractFeed {

  /**
   * Get themes feed data.
   *
   * @see https://docs.google.com/document/d/1lJ3VPAJf7DAbBWAQclRHfcltzZefUG3iGCec-z97KlA/edit?ts=5c4ef9d5#heading=h.ewzbsz8i5way
   * for details on the feed structure.
   *
   * @return array
   *   The feed data.
   */
  public function getData() {
    $max_number_of_items = (int) _reol_app_feeds_variable_get('reol_app_feeds_themes', 'max_number_of_items', 50);

    $entity_type = NodeHelper::ENTITY_TYPE_NODE;
    $bundle = 'article';
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', $entity_type)
      ->entityCondition('bundle', $bundle)
      ->propertyCondition('status', NODE_PUBLISHED)
      ->fieldCondition('field_show_in_app', 'value', 1)
      ->propertyOrderBy('created', 'DESC')
      ->range(0, $max_number_of_items);
    $result = $query->execute();

    if (isset($result[$entity_type])) {
      $nodes = node_load_multiple(array_keys($result[$entity_type]));
      return array_values(array_map(function ($node) {
        return $this->paragraphHelper->getThemeData($node);
      }, $nodes));
    }

    return [];
  }

}
