<?php

namespace Drupal\reol_app_feeds\Helper;

use Drupal\reol_app_feeds\Feed\CategoriesFeed;
use Drupal\reol_app_feeds\Feed\FrontPageFeed;
use Drupal\reol_app_feeds\Feed\V3\FrontPageFeed as FrontPageFeedV3;
use Drupal\reol_app_feeds\Feed\OverdriveMappingFeed;
use Drupal\reol_app_feeds\Feed\ThemesFeed;

/**
 * Feed helper.
 */
class FeedHelper {

  /**
   * All feed names.
   *
   * @var string[]
   */
  public static $feedNames = [
    'frontpage',
    'themes',
    'categories',
    'overdrive/mapping',
  ];

  /**
   * Deliver feed content.
   *
   * @param string $name
   *   The feed name.
   *
   * @return int|bool
   *   The number of bytes sent or false on failure.
   */
  public function deliver($name) {
    $filepath = $this->getFeedFilepath($name);
    $file = drupal_realpath($filepath);
    if (file_exists($file)) {
      header('content-type: application/json; charset=utf-8');
      header('expires: 0');
      header('cache-control: must-revalidate');
      header('content-length: ' . filesize($file));

      return readfile($file);
    }

    return FALSE;
  }

  /**
   * Generate feed content.
   *
   * @param string $name
   *   The feed name.
   *
   * @return bool|int
   *   The number of bytes written to the feed content file or false on failure.
   */
  public function generate($name) {
    $filepath = $this->getFeedFilepath($name);
    $dirname = dirname($filepath);
    if (!file_exists($dirname)) {
      drupal_mkdir($dirname, NULL, TRUE);
    }

    $feedClass = [
      'frontpage' => FrontPageFeed::class,
      'v3/frontpage' => FrontPageFeedV3::class,
      'themes' => ThemesFeed::class,
      'categories' => CategoriesFeed::class,
      'overdrive/mapping' => OverdriveMappingFeed::class,
    ][$name] ?? NULL;

    if (NULL === $feedClass) {
      throw new \RuntimeException(sprintf('Invalid feed: %s', $name));
    }

    $data = (new $feedClass())->getData();

    if (empty($data)) {
      throw new \RuntimeException(sprintf('Feed %s generated no data', $name));
    }

    $file = drupal_realpath($filepath);

    return file_put_contents($file, json_encode($data));
  }

  /**
   * Get feed filepath.
   *
   * @param string $feed
   *   The feed name.
   */
  private function getFeedFilepath($feed) {
    return 'public://reol_app_feed/feed/' . $feed . '.json';
  }

}
