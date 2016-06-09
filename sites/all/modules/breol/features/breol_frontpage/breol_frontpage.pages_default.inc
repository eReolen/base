<?php
/**
 * @file
 * breol_frontpage.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function breol_frontpage_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'breol_frontpage';
  $page->task = 'page';
  $page->admin_title = 'BReol Frontpage';
  $page->admin_description = '';
  $page->path = 'frontpage';
  $page->access = array();
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_breol_frontpage__panel';
  $handler->task = 'page';
  $handler->subtask = 'breol_frontpage';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => 'panel',
  );
  $display = new panels_display();
  $display->layout = 'onecol';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'middle' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '2a3c812e-559f-4dd6-9cdf-d09f7d0b528b';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-8c751b38-ed52-45ea-a0f0-bebe552612fd';
    $pane->panel = 'middle';
    $pane->type = 'carousel';
    $pane->subtype = 'carousel';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '8c751b38-ed52-45ea-a0f0-bebe552612fd';
    $display->content['new-8c751b38-ed52-45ea-a0f0-bebe552612fd'] = $pane;
    $display->panels['middle'][0] = 'new-8c751b38-ed52-45ea-a0f0-bebe552612fd';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-8c751b38-ed52-45ea-a0f0-bebe552612fd';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['breol_frontpage'] = $page;

  return $pages;

}
