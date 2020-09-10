<?php

/**
 * @file
 * ReolCategoryController.
 */

/**
 * Controller for ReolCategory objects.
 */
class ReolCategoryController extends EntityAPIController {

  /**
   * Implements EntityAPIControllerInterface.
   *
   * We need to override this to reset the menu item before deleting
   * the entity. Else menu_reset_item() ends up calling our own
   * hook_menu(), which by then doesn't know about the item as the
   * entity has been deleted.
   */
  public function delete($ids, DatabaseTransaction $transaction = NULL) {
    $entities = $ids ? $this->load($ids) : FALSE;
    foreach ($entities as $category) {
      $menu_link = menu_link_get_preferred($category->categoryPath());
      if ($menu_link && ($menu_link['page_callback'] == 'reol_category_page')) {
        menu_reset_item($menu_link);
      }
    }
    parent::delete($ids, $transaction);
    menu_rebuild();
  }

  /**
   * Implements EntityAPIControllerInterface.
   *
   * Rebuild the menu when saving categories.
   */
  public function save($entity, DatabaseTransaction $transaction = NULL) {
    parent::save($entity, $transaction);
    menu_rebuild();
  }

}
