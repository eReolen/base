<?php

namespace Drupal\reol_app_feeds\Feed;

use Drupal\reol_app_feeds\Helper\NodeHelper;
use Drupal\reol_app_feeds\Helper\ParagraphHelper;

/**
 * Categories feed.
 *
 * @package Drupal\reol_app_feeds\Feed
 */
class CategoriesFeed extends AbstractFeed {

  /**
   * Get categories feed data.
   *
   * @see https://docs.google.com/document/d/1lJ3VPAJf7DAbBWAQclRHfcltzZefUG3iGCec-z97KlA/edit?ts=5c4ef9d5#heading=h.r3okoat4q87f
   * for details on the feed structure.
   *
   * @return array
   *   The feed data.
   */
  public function getData() {
    $data = [];

    $nodes = $this->getNodes();

    foreach ($nodes as $node) {
      $subcategories = [];

      $paragraphs = $this->nodeHelper->getParagraphs($node);
      foreach ($paragraphs as $paragraph) {
        $wrapper = entity_metadata_wrapper($paragraph->entityType(), $paragraph);

        switch ($paragraph->bundle()) {
          case ParagraphHelper::PARAGRAPH_PICKED_ARTICLE_CAROUSEL:
            $paragraphData = $this->paragraphHelper->getParagraphData($paragraph);
            $attachment = ParagraphHelper::VALUE_NONE;
            if (!empty($paragraphData['list'])) {
              $attachment = [
                'view' => ParagraphHelper::VIEW_DOTTED,
                'elements' => $paragraphData['list'],
              ];
            }
            $subcategories[] = [
              'title' => $wrapper->field_picked_title->value(),
              'view' => ParagraphHelper::VIEW_SCROLL,
              'type' => 'sub_category',
              'query' => ParagraphHelper::VALUE_NONE,
              'attachment' => $attachment,
            ];
            break;

          case ParagraphHelper::PARAGRAPH_MATERIAL_CAROUSEL:
            // @TODO: Can we use entity_metadata_wrapper to get the list of carousels?
            foreach ($paragraph->field_carousel[LANGUAGE_NONE] as $carousel) {
              $subcategories[] = [
                'title' => $carousel['title'],
                'type' => 'sub_category',
                'query' => $carousel['search'],
                'attachment' => ParagraphHelper::VALUE_NONE,
              ];
            }
            break;

          case ParagraphHelper::PARAGRAPH_SPOTLIGHT_BOX:
            // @TODO: Do something clever with "author portraits"?
        }
      }

      if (!empty($subcategories)) {
        $wrapper = entity_metadata_wrapper('node', $node);
        $query = ParagraphHelper::VALUE_NONE;
        if (!empty($wrapper->field_category_query->value())) {
          $query = $wrapper->field_category_query->value();
        }
        $data[] = [
          'title' => $node->title,
          'guid' => $node->nid,
          'type' => 'category',
          'query' => $query,
          'subcategories' => $subcategories,
        ];
      }
    }

    return $data;
  }

  /**
   * Get the nodes to include in the categories feed.
   *
   * @return array
   *   The nodes.
   */
  private function getNodes() {
    $group_name = 'reol_app_feeds_category';
    $field_name = 'page_ids';
    $pages = _reol_app_feeds_variable_get($group_name, $field_name, []);
    $included = array_filter($pages, function ($page) {
      return isset($page['included']) && 1 === $page['included'];
    });

    return $this->nodeHelper->loadNodes(array_keys($included));
  }

}
