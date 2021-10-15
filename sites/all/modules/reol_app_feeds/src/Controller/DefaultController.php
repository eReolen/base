<?php

namespace Drupal\reol_app_feeds\Controller;

use Drupal\reol_app_feeds\Helper\FeedHelper;

/**
 * Default controller.
 */
class DefaultController {

  /**
   * Render front page data.
   */
  public function frontpage() {
    return $this->deliver('frontpage');
  }

  /**
   * Render front page data (v3).
   */
  public function frontpageV3() {
    return $this->deliver('v3/frontpage');
  }

  /**
   * Render themes data.
   */
  public function themes() {
    return $this->deliver('themes');
  }

  /**
   * Render categories data.
   */
  public function categories() {
    return $this->deliver('categories');
  }

  /**
   * Render Overdrive mappings.
   */
  public function overdriveMapping() {
    return $this->deliver('overdrive/mapping');
  }

  /**
   * Deliver feed content.
   *
   * @param string $name
   *   The feed name.
   */
  private function deliver($name) {
    $result = (new FeedHelper())->deliver($name);

    if (FALSE === $result) {
      return drupal_not_found();
    }

    exit;
  }

}
