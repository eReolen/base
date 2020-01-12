<?php

namespace Drupal\reol_app_feeds\Controller;

use Drupal\reol_app_feeds\Feed\CategoriesFeed;
use Drupal\reol_app_feeds\Feed\FrontPageFeed;
use Drupal\reol_app_feeds\Feed\ThemesFeed;

/**
 * Default controller.
 */
class DefaultController {

  /**
   * Render front page data.
   */
  public function frontpage() {
    $feed = new FrontPageFeed();
    $data = $feed->getData();

    drupal_json_output($data);
    drupal_exit();
  }

  /**
   * Render themes data.
   */
  public function themes() {
    $feed = new ThemesFeed();
    $data = $feed->getData();

    drupal_json_output($data);
    drupal_exit();
  }

  /**
   * Render categories data.
   */
  public function categories() {
    $feed = new CategoriesFeed();
    $data = $feed->getData();

    drupal_json_output($data);
    drupal_exit();
  }

  /**
   * Render paragraphs data.
   */
  public function paragraphs($type) {
    $nids = $this->getQueryParameter('nids', FrontPageFeed::getFrontPageIds());

    $feed = new ParagraphsFeed();
    $data = $feed->getData($nids, $type);

    drupal_json_output($data);
    drupal_exit();
  }

  /**
   * Render Overdrive mappings.
   */
  public function overdriveMapping() {
    $triggers = overdrive_triggers_load();

    $data = array_map(function ($trigger) {
      return [
        'trigger' => $trigger['search_trigger'],
        'query' => $trigger['search_query'],
      ];
    }, $triggers);

    drupal_json_output($data);
    drupal_exit();
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
