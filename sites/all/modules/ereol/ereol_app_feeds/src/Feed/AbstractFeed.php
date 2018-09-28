<?php

namespace Drupal\ereol_app_feeds\Feed;

use Drupal\ereol_app_feeds\Helper\ParagraphHelper;

/**
 * Abstract feed.
 */
class AbstractFeed {
  /**
   * The paragraph helper.
   *
   * @var \Drupal\ereol_app_feeds\Helper\ParagraphHelper*/
  protected $paragraphHelper;

  /**
   * Constructor.
   */
  public function __construct() {
    $this->paragraphHelper = new ParagraphHelper();
  }

}
