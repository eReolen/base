<?php

namespace Drupal\reol_app_feeds\Feed;

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
   * @see https://docs.google.com/document/d/1RNBH_mJFX9pQRVQBBr2-8JZlU0zXTiLyAt92GmgTnfE/edit
   * for details on the feed structure.
   *
   * @return array
   *   The feed data.
   *
   * @throws \TingClientException
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
            $themes = [];
            foreach ($wrapper->field_picked_articles->value() as $article) {
              $themes[] = $this->paragraphHelper->getThemeData($article);
            }
            if (!empty($themes)) {
              $subcategories[] = [
                'type' => 'theme_list',
                'view' => ParagraphHelper::VIEW_DOTTED,
                'list' => $themes,
              ];
            }
            break;

          case ParagraphHelper::PARAGRAPH_MATERIAL_CAROUSEL:
            // @TODO: Can we use entity_metadata_wrapper to get the list of
            // carousels?
            if (isset($paragraph->field_carousel[LANGUAGE_NONE]) && is_array($paragraph->field_carousel[LANGUAGE_NONE])) {
              foreach ($paragraph->field_carousel[LANGUAGE_NONE] as $carousel) {
                $query = trim($carousel['search']);
                if (!empty($query)) {
                  $subcategories[] = [
                    'title' => $carousel['title'],
                    'type' => 'carousel',
                    'query' => trim($carousel['search']),
                  ];
                }
              }
            }
            break;

          case ParagraphHelper::PARAGRAPH_TWO_ELEMENTS:
          case ParagraphHelper::PARAGRAPH_VIDEO_BUNDLE:
            $videoList = $this->paragraphHelper->getVideoList($paragraph);
            if (!empty($videoList)) {
              $subcategories[] = reset($videoList);
            }

            if (ParagraphHelper::PARAGRAPH_TWO_ELEMENTS === $paragraph->bundle()) {
              $subcategories = array_merge($subcategories, $this->paragraphHelper->getLinkBoxes($paragraph));
            }
            break;

          case ParagraphHelper::PARAGRAPH_SPOTLIGHT_BOX:
            $subcategories = array_merge($subcategories, $this->paragraphHelper->getLinkBoxes($paragraph));
            break;
        }
      }

      if (!empty($subcategories)) {
        $wrapper = entity_metadata_wrapper('node', $node);
        $query = ParagraphHelper::VALUE_NONE;
        if (isset($wrapper->field_category_query)) {
          $query = trim($wrapper->field_category_query->value());
        }
        $color = _reol_app_feeds_variable_get('reol_app_feeds_category', 'default_color');
        if (isset($wrapper->field_app_feed_color)) {
          $value = $wrapper->field_app_feed_color->value();
          if (isset($value['rgb'])) {
            $color = $value['rgb'];
          }
        }
        $imageUrl = ParagraphHelper::VALUE_NONE;
        if (isset($wrapper->field_app_feed_image)) {
          $imageUrl = $this->nodeHelper->getImage($wrapper->field_app_feed_image->value(), 'app_feed_image');
        }
        $data[] = [
          'guid' => $node->nid,
          'type' => 'category',
          'title' => $node->title,
          'color' => $color,
          'imageUrl' => $imageUrl,
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
  protected function getNodes() {
    $group_name = 'reol_app_feeds_category';
    $field_name = 'page_ids';
    $pages = _reol_app_feeds_variable_get($group_name, $field_name, []);
    $included = array_filter($pages, function ($page) {
      return isset($page['included']) && 1 === $page['included'];
    });

    return $this->nodeHelper->loadNodes(array_keys($included));
  }

}
