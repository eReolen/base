<?php

/**
 * @file
 * ReolCategory class.
 */

/**
 * Category entity.
 */
class ReolCategory extends Entity {
  /**
   * TODO Missing short description in doc comments.
   *
   * @var string
   */
  public $title;
  /**
   * TODO Missing short description in doc comments.
   *
   * @var string
   */
  public $path;
  /**
   * TODO Missing short description in doc comments.
   *
   * @var string
   */
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
