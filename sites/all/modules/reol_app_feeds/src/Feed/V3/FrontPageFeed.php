<?php

namespace Drupal\reol_app_feeds\Feed\V3;

use Drupal\reol_app_feeds\Feed\FrontPageFeed as FrontPageFeedV2;
use Drupal\reol_app_feeds\Helper\ParagraphHelper;

/**
 * The FrontPageFeed v3.
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
      $data[] = $this->getThemes([$paragraphId], FALSE);
      $data[] = $this->getVideos([$paragraphId]);
      $data[] = $this->getEditors([$paragraphId]);
      $data[] = $this->getAudios([$paragraphId]);
      // "Latest news"
      $data[] = $this->paragraphHelper->getParagraphsData(ParagraphHelper::PARAGRAPH_ARTICLE_CAROUSEL, [$paragraphId]);
      $data[] = $this->getBlueTitlesInfo([$paragraphId]);
      $data[] = $this->getReviewsData([$paragraphId]);
      $data[] = $this->getLinkBoxes([$paragraphId]);
    }

    // Remove empty lists.
    $data = array_filter($data);

    // Flatten data.
    if (!empty($data)) {
      $data = array_merge(...$data);
    }

    return $data;
  }

  /**
   * Get blue titles info.
   */
  private function getBlueTitlesInfo(array $paragraphIds): array {
    return $this->paragraphHelper->getParagraphsData(ParagraphHelper::PARAGRAPH_BLUE_TITLES_INFO, $paragraphIds);
  }

  /**
   * Get reviews data.
   */
  private function getReviewsData(array $paragraphIds): array {
    $paragraphs = $this->paragraphHelper->getParagraphs(ParagraphHelper::PARAGRAPH_REVIEW, $paragraphIds);

    return count($paragraphs) > 0 ? $this->paragraphHelper->getReviewList(5) : [];
  }

  /**
   * Get link boxes.
   */
  private function getLinkBoxes(array $paragraphIds): array {
    $data = [];

    $paragraphs = paragraphHelper::isBreol()
      ? $this->paragraphHelper->getParagraphs(ParagraphHelper::PARAGRAPH_TWO_ELEMENTS, $paragraphIds)
      : $this->paragraphHelper->getParagraphs(ParagraphHelper::PARAGRAPH_SPOTLIGHT_BOX, $paragraphIds);

    foreach ($paragraphs as $paragraph) {
      $data[] = $this->paragraphHelper->getLinkBoxes($paragraph);
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
