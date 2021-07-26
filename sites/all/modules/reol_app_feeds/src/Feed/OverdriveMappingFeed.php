<?php

namespace Drupal\reol_app_feeds\Feed;

/**
 * Overdrive mapping feed.
 *
 * @package Drupal\reol_app_feeds\Feed
 */
class OverdriveMappingFeed extends AbstractFeed {

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
    $triggers = overdrive_triggers_load();

    return array_map(function ($trigger) {
      return [
        'trigger' => $trigger['search_trigger'],
        'query' => $trigger['search_query'],
      ];
    }, $triggers);
  }

}
