<?php

namespace Drupal\ereol_app_feeds\Feed;

use Drupal\ereol_app_feeds\Helper\ParagraphHelper;

/**
 * Paragraphs feed.
 */
class ParagraphsFeed extends AbstractFeed {

  /**
   * Get feed data.
   */
  public function getData($nids, $type) {
    $helper = new ParagraphHelper();
    $type = $helper->getParagraphType($type);
    $ids = $helper->getParagraphIds($nids);

    $data = $helper->getParagraphsData($type, $ids);

    // HACK!
    if (ParagraphHelper::PARAGRAPH_ALIAS_THEME_LIST === $type) {
      $lists = array_column(array_filter($data, function (array $item) {
        return isset($item['list']);
      }), 'list');
      $data = array_merge(...$lists);
      // Remove items with no identifiers.
      $data = array_filter($data, function (array $item) {
        return isset($item['identifiers']);
      });
    }

    return $data;
  }

}
