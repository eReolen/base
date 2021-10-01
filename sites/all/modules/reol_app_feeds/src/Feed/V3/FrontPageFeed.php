<?php

namespace Drupal\reol_app_feeds\Feed\V3;

use Drupal\reol_app_feeds\Feed\FrontPageFeed as FrontPageFeedV2;

/**
 * Class FrontPageFeed.
 */
class FrontPageFeed extends FrontPageFeedV2 {

  /**
   * Get front page feed data.
   *
   * FrontPageFeedV2 groups content by type, but in this extension we list
   * elements in the order they appear in the included pages.
   *
   * @return array
   *   The feed data.
   */
  public function getData() {
    $frontPageIds = self::getFrontPageIds();
    $paragraphIds = $this->paragraphHelper->getParagraphIds($frontPageIds, self::NODE_TYPE_INSPIRATION, TRUE);

    $data = [];

    foreach ($paragraphIds as $paragraphId) {
      $data[] = $this->getCarousels([$paragraphId]);
      $data[] = $this->getThemes([$paragraphId]);
      $data[] = $this->getEditors([$paragraphId]);
      $data[] = $this->getVideos([$paragraphId]);
      $data[] = $this->getAudios([$paragraphId]);
    }

    // Remove empty lists.
    $data = array_filter($data);

    // Flatten data.
    if (!empty($data)) {
      $data = array_merge(...$data);
    }

    return $data;
  }

}
