<?php

namespace Drupal\ereol_app_feeds\Feed;

use Drupal\ereol_app_feeds\Helper\ParagraphHelper;

/**
 * Frontpage helper.
 */
class FrontPageFeed extends AbstractFeed {
  const NODE_TYPE_INSPIRATION = 'inspiration';

  /**
   * {@inheritdoc}
   *
   * Load only paragraphs on "inspiration" pages.
   */
  public static function getFrontPageIds() {
    return array_filter(array_values(variable_get('ereol_app_feeds_frontpage_ids', [])));
  }

  /**
   * Get frontpage data.
   */
  public function getData() {
    $frontPageIds = self::getFrontPageIds();
    $paragraphIds = $this->paragraphHelper->getParagraphIds($frontPageIds, self::NODE_TYPE_INSPIRATION, TRUE);

    $data = [
      'carousels' => $this->getCarousels($paragraphIds),
      'themes' => $this->getThemes($paragraphIds),
      'reviews' => $this->getReviews($paragraphIds),
      'editor' => $this->getEditors($paragraphIds),
      'videos' => $this->getVideos($paragraphIds),
      'audio' => $this->getAudios($paragraphIds),
    ];

    return $data;
  }

  /**
   * Get carousels.
   */
  private function getCarousels(array $paragraphIds) {
    return $this->paragraphHelper->getParagraphsData(ParagraphHelper::PARAGRAPH_ALIAS_CAROUSEL, $paragraphIds);
  }

  /**
   * Get themes.
   */
  private function getThemes(array $paragraphIds) {
    $themes = $this->paragraphHelper->getParagraphsData(ParagraphHelper::PARAGRAPH_ALIAS_THEME_LIST, $paragraphIds);

    // Preprend "Latest news".
    $latestNews = $this->paragraphHelper->getParagraphsData(ParagraphHelper::PARAGRAPH_ARTICLE_CAROUSEL, $paragraphIds);
    $themes = array_merge($latestNews, $themes);

    return array_values(array_filter($themes, function ($theme) {
      return isset($theme['list']) && $theme['list'];
    }));
  }

  /**
   * Get links.
   */
  private function getLinks(array $paragraphIds) {
    return $this->paragraphHelper->getParagraphsData(ParagraphHelper::PARAGRAPH_ALIAS_LINK, $paragraphIds);
  }

  /**
   * Get reviews.
   */
  private function getReviews(array $paragraphIds) {
    return $this->paragraphHelper->getParagraphsData(ParagraphHelper::PARAGRAPH_REVIEW, $paragraphIds);
  }

  /**
   * Get editors.
   */
  protected function getEditors(array $paragraphIds) {
    $data = [];

    $paragraphs = $this->paragraphHelper->getParagraphs(ParagraphHelper::PARAGRAPH_SPOTLIGHT_BOX, $paragraphIds);

    foreach ($paragraphs as $paragraph) {
      $item = $this->paragraphHelper->getEditor($paragraph);
      if ($item['list']) {
        $item['type'] = 'editor_recommends_list';
        $data[] = $item;
      }
    }

    return $data;
  }

  /**
   * Get videos.
   */
  private function getVideos(array $paragraphIds) {
    // Wrap all videos in a fake list element.
    $list = [];
    $paragraphs = $this->paragraphHelper->getParagraphs(ParagraphHelper::PARAGRAPH_SPOTLIGHT_BOX, $paragraphIds);

    foreach ($paragraphs as $paragraph) {
      $item = $this->paragraphHelper->getVideoList($paragraph);
      if (!empty($item)) {
        $list[] = $item;
      }
    }
    if (count($list) > 0) {
      $list = array_merge(...$list);
    }

    return empty($list) ? [] : [
      [
        'guid' => ParagraphHelper::VALUE_NONE,
        'type' => 'video_list',
        'view' => ParagraphHelper::VIEW_DOTTED,
        'list' => $list,
      ],
    ];
  }

  /**
   * Get audio.
   */
  private function getAudios(array $paragraphIds) {
    // Wrap all videos audio samples in a fake list element.
    $list = $this->paragraphHelper->getParagraphsData(ParagraphHelper::PARAGRAPH_ALIAS_AUDIO, $paragraphIds);

    return empty($list) ? [] : [
      [
        'guid' => ParagraphHelper::VALUE_NONE,
        'type' => 'audio_sample_list',
        'view' => ParagraphHelper::VIEW_DOTTED,
        'list' => $list,
      ],
    ];
  }

}
