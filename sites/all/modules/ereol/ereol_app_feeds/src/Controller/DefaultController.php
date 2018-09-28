<?php

namespace Drupal\ereol_app_feeds\Controller;

use Drupal\ereol_app_feeds\Feed\CategoriesFeed;
use Drupal\ereol_app_feeds\Feed\FrontPageFeed;
use Drupal\ereol_app_feeds\Feed\ParagraphsFeed;

/**
 * Default controller.
 */
class DefaultController {

  /**
   * Render frontpage data.
   */
  public function frontpage() {
    $feed = new FrontPageFeed();
    $data = $feed->getData();

    drupal_json_output($data);
  }

  /**
   * Render categories data.
   */
  public function categories() {
    $feed = new CategoriesFeed();
    $data = $feed->getData();

    drupal_json_output($data);
  }

  /**
   * Render paragraphs data.
   */
  public function paragraphs($type) {
    $nids = $this->getQueryParameter('nids', FrontPageFeed::getFrontPageIds());

    $feed = new ParagraphsFeed();
    $data = $feed->getData($nids, $type);

    drupal_json_output($data);
  }

  /**
   * Get a query parameter.
   */
  protected function getQueryParameter($name, $defaultValue = NULL) {
    $query_parameters = drupal_get_query_parameters();
    $value = isset($query_parameters[$name]) ? $query_parameters[$name] : NULL;

    // Normalize "nids" to be an array of integers.
    if ('nids' === $name) {
      if (empty($value)) {
        $value = [];
      }
      elseif (!is_array($value)) {
        $value = preg_split('/\s*,\s*/', $value, -1, PREG_SPLIT_NO_EMPTY);
      }
      $value = array_unique(array_map('intval', $value));
    }

    return !empty($value) ? $value : $defaultValue;
  }

}
