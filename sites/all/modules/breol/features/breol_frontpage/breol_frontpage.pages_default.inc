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
  $page->admin_title = 'Breol Frontpage';
  $page->admin_description = '';
  $page->path = 'breol_frontpage';
  $page->access = array(
    'type' => 'none',
    'settings' => NULL,
  );
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
  $display->layout = 'stacked_columns';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'middle' => NULL,
      'header' => NULL,
      'before_content' => NULL,
      'main_content' => NULL,
      'after_content' => NULL,
      'bottom' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '2cbec1ba-5a65-4f9f-8403-59356b3cbae6';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-79924abc-b7fc-4ff4-91bf-0d938a1ecfbd';
    $pane->panel = 'after_content';
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
    $pane->uuid = '79924abc-b7fc-4ff4-91bf-0d938a1ecfbd';
    $display->content['new-79924abc-b7fc-4ff4-91bf-0d938a1ecfbd'] = $pane;
    $display->panels['after_content'][0] = 'new-79924abc-b7fc-4ff4-91bf-0d938a1ecfbd';
    $pane = new stdClass();
    $pane->pid = 'new-9282ec55-a017-4fce-b98a-7389859efaf7';
    $pane->panel = 'main_content';
    $pane->type = 'fancy_box';
    $pane->subtype = 'fancy_box';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
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
    $pane->uuid = '9282ec55-a017-4fce-b98a-7389859efaf7';
    $display->content['new-9282ec55-a017-4fce-b98a-7389859efaf7'] = $pane;
    $display->panels['main_content'][0] = 'new-9282ec55-a017-4fce-b98a-7389859efaf7';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-9282ec55-a017-4fce-b98a-7389859efaf7';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['breol_frontpage'] = $page;

  return $pages;

}
