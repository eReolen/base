<?php
/**
 * @file
 * Menu Block UI class.
 */

class menu_block_ui extends ctools_export_ui {
  /**
   * Deletes exportable items from the database.
   */
  function delete_form_submit(&$form_state) {
    $item = $form_state['item'];

    // Remove block placement from Block module.
    if (module_exists('block')) {
      db_delete('block')
        ->condition('module', 'menu_block')
        ->condition('delta', $item->name)
        ->execute();
    }

    ctools_export_crud_delete($this->plugin['schema'], $item);
    $export_key = $this->plugin['export']['key'];
    $message = str_replace('%title', check_plain($item->{$export_key}), $this->plugin['strings']['confirmation'][$form_state['op']]['success']);
    drupal_set_message($message);
  }
}
