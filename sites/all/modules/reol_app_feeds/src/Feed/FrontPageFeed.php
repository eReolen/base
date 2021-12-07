<?php

namespace Drupal\reol_app_feeds\Feed;

use Drupal\reol_app_feeds\Helper\ParagraphHelper;
use EntityFieldQuery;

/**
 * Class FrontPageFeed.
 *
 * @package Drupal\reol_app_feeds\Feed
 */
class FrontPageFeed extends AbstractFeed {
  const NODE_TYPE_INSPIRATION = 'inspiration';

  /**
   * Get front page ids from app feed settings.
   *
   * @return array
   *   The front page ids.
   */
  public static function getFrontPageIds() {
    $group_name = 'reol_app_feeds_frontpage';
    $field_name = 'page_ids';
    $pages = _reol_app_feeds_variable_get($group_name, $field_name, []);
    $included = array_filter($pages, function ($page) {
      return isset($page['included']) && 1 === $page['included'];
    });

    return array_keys($included);
  }

  /**
   * Get front page feed data.
   *
   * @see https://docs.google.com/document/d/1lJ3VPAJf7DAbBWAQclRHfcltzZefUG3iGCec-z97KlA/edit?ts=5c4ef9d5#heading=h.12un1qdppa6x
   * for details on the feed structure.
   *
   * @return array
   *   The feed data.
   */
  public function getData() {
    $frontPageIds = self::getFrontPageIds();
    $paragraphIds = $this->paragraphHelper->getParagraphIds($frontPageIds, self::NODE_TYPE_INSPIRATION, TRUE);

    $data = [
      'carousels' => $this->getCarousels($paragraphIds),
      'themes' => $this->getThemes($paragraphIds),
      'reviews' => $this->getReviews(),
      'editor' => $this->getEditors($paragraphIds),
      'videos' => $this->getVideos($paragraphIds),
      'audio' => $this->getAudios($paragraphIds),
    ];

    return $data;
  }

  /**
   * Get carousels.
   *
   * @param array $paragraphIds
   *   The paragraph ids.
   *
   * @see https://docs.google.com/document/d/1lJ3VPAJf7DAbBWAQclRHfcltzZefUG3iGCec-z97KlA/edit?ts=5c4ef9d5#bookmark=id.51b3v5z38ank
   *
   * @return array
   *   The carousels data.
   */
  protected function getCarousels(array $paragraphIds) {
    return $this->paragraphHelper->getParagraphsData(ParagraphHelper::PARAGRAPH_ALIAS_CAROUSEL, $paragraphIds);
  }

  /**
   * Get themes.
   *
   * @param array $paragraphIds
   *   The paragraph ids.
   *
   * @see https://docs.google.com/document/d/1lJ3VPAJf7DAbBWAQclRHfcltzZefUG3iGCec-z97KlA/edit?ts=5c4ef9d5#bookmark=id.vpgrki5b8gg
   *
   * @return array
   *   The themes data.
   */
  protected function getThemes(array $paragraphIds, bool $includeLatestNews = TRUE) {
    $themes = $this->paragraphHelper->getParagraphsData(ParagraphHelper::PARAGRAPH_ALIAS_THEME_LIST, $paragraphIds);

    if ($includeLatestNews) {
      if (module_exists('breol_news')) {
        $latestNews = $this->getLatestNews();
      }
      else {
        $latestNews = $this->paragraphHelper->getParagraphsData(ParagraphHelper::PARAGRAPH_ARTICLE_CAROUSEL,
        $paragraphIds);
      }

      // Prepend "Latest news".
      if (!empty($latestNews)) {
        $themes = array_merge($latestNews, $themes);
      }
    }

    return array_values(array_filter($themes, function ($theme) {
      return isset($theme['list']) && $theme['list'];
    }));
  }

  /**
   * Get latest news as a theme list.
   */
  private function getLatestNews() {
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'breol_news')
      ->propertyCondition('status', NODE_PUBLISHED)
      ->addTag('published_at')
      ->addMetaData('published_at', [
        'order_by' => [
          'direction' => 'DESC',
        ],
      ])
      ->range(0, (int) _reol_app_feeds_variable_get('reol_app_feeds_frontpage', 'max_news_count', 6));
    $result = $query->execute();
    if (isset($result['node'])) {
      $ids = array_keys($result['node']);
      $nodes = $this->nodeHelper->loadNodes($ids, NODE_PUBLISHED, 'node', 'breol_news');

      return [
        [
          'guid' => ParagraphHelper::VALUE_NONE,
          'type' => 'theme_list',
          'view' => 'dotted',
          'list' => array_values(array_map([$this->paragraphHelper, 'getThemeData'], $nodes)),
        ],
      ];
    }

    return NULL;
  }

  /**
   * Get reviews.
   *
   * @see https://docs.google.com/document/d/1lJ3VPAJf7DAbBWAQclRHfcltzZefUG3iGCec-z97KlA/edit?ts=5c4ef9d5#bookmark=id.qh5qjlx68dde
   *
   * @return array
   *   The reviews data.
   */
  protected function getReviews() {
    return $this->paragraphHelper->getReviewList(5);
  }

  /**
   * Get editors.
   *
   * @param array $paragraphIds
   *   The paragraph ids.
   *
   * @see https://docs.google.com/document/d/1lJ3VPAJf7DAbBWAQclRHfcltzZefUG3iGCec-z97KlA/edit?ts=5c4ef9d5#bookmark=id.isl1hf5mbnf
   *
   * @return array
   *   The editors data.
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
   *
   * @param array $paragraphIds
   *   The paragraph ids.
   *
   * @see https://docs.google.com/document/d/1lJ3VPAJf7DAbBWAQclRHfcltzZefUG3iGCec-z97KlA/edit?ts=5c4ef9d5#bookmark=id.aw3cqhhwfwa0
   *
   * @return array
   *   The videos data.
   */
  protected function getVideos(array $paragraphIds) {
    // Wrap all videos in a fake list element.
    $list = [];
    $paragraphs = $this->paragraphHelper->getParagraphs([
      ParagraphHelper::PARAGRAPH_SPOTLIGHT_BOX,
      ParagraphHelper::PARAGRAPH_TWO_ELEMENTS,
      ParagraphHelper::PARAGRAPH_VIDEO_BUNDLE,
    ], $paragraphIds);

    foreach ($paragraphs as $paragraph) {
      // Don't include video bundle paragraphs in Front page feed v2
      // (Drupal\reol_app_feeds\Feed\FrontPageFeed).
      // Drupal\reol_app_feeds\Feed\V3\FrontPageFeed, which inherits this class,
      // should include the video bundles.
      if (self::class === get_class($this)
        && ParagraphHelper::PARAGRAPH_VIDEO_BUNDLE === $paragraph->bundle()) {
        continue;
      }
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
   *
   * @param array $paragraphIds
   *   The paragraph ids.
   *
   * @see https://docs.google.com/document/d/1lJ3VPAJf7DAbBWAQclRHfcltzZefUG3iGCec-z97KlA/edit?ts=5c4ef9d5#bookmark=id.awje1hlhr91
   *
   * @return array
   *   The audio data.
   */
  protected function getAudios(array $paragraphIds) {
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
