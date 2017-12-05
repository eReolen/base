<?php
/**
 * @file
 * reol_frontend.pm_existing_pages.inc
 */

/**
 * Implements hook_pm_existing_pages_info().
 */
function reol_frontend_pm_existing_pages_info() {
  $export = array();

  $pm_existing_page = new stdClass();
  $pm_existing_page->api_version = 1;
  $pm_existing_page->name = 'reol_bookmarks';
  $pm_existing_page->label = 'eReolen bookmarks';
  $pm_existing_page->context = 'entity|user|uid';
  $pm_existing_page->paths = 'user/%user/bookmarks';
  $export['reol_bookmarks'] = $pm_existing_page;

  return $export;
}
