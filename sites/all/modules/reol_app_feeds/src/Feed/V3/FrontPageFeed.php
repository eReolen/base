<?php

namespace Drupal\reol_app_feeds\Feed\V3;

use Drupal\reol_app_feeds\Feed\FrontPageFeed as FrontPageFeedV2;
use Drupal\reol_app_feeds\Feed\CategoriesFeed;

/**
 * Class FrontPageFeed.
 *
 * Same structure as the category feed, but with other source pages.
 */
class FrontPageFeed extends CategoriesFeed {

  /**
   * {@inheritdoc}
   */
  protected function getNodes() {
    $ids = FrontPageFeedV2::getFrontPageIds();

    return $this->nodeHelper->loadNodes($ids);
  }

  /**
   * {@inheritdoc}
   */
  public function getData() {
    $data = parent::getData();

    // Extract and merge subcategories
    $data = array_column($data, 'subcategories');
    $data = array_merge(...$data);

    return $data;
  }

}
