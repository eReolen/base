<?php

/**
 * @file
 * ReolCategory class.
 */

/**
 * Category entity.
 */
class ReolCategory extends Entity {
  public $title;
  public $path;
  public $query;

  /**
   * Get the category path.
   */
  public function categoryPath() {
    return $this->path;
  }

  /**
   * Get the search page path.
   */
  public function targetPath() {
    return 'search/ting/' . $this->query;
  }

}
