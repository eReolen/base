<?php

/**
 * @file
 * reol_frontend.menu_block.inc
 */

/**
 * Implements hook_menu_block_defaults().
 */
function reol_frontend_menu_block_defaults() {
  $export = array();

  $menu_block = new stdClass();
  $menu_block->disabled = FALSE; /* Edit this to true to make a default menu_block disabled initially */
  $menu_block->api_version = 1;
  $menu_block->name = 'main_menu';
  $menu_block->label = 'Main menu (eReolen)';
  $menu_block->description = '';
  $menu_block->depth = 3;
  $menu_block->expanded = 0;
  $menu_block->follow = '0';
  $menu_block->level = 1;
  $menu_block->parent = 'main-menu:0';
  $menu_block->sort = 0;
  $menu_block->title_link = 0;
  $export['main_menu'] = $menu_block;

  return $export;
}
