<?php
/**
 * @file
 * breol_search_frontend.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function breol_search_frontend_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'search_ting_search__panel_context_8c346371-2680-4304-84f1-211870159d30';
  $handler->task = 'search';
  $handler->subtask = 'ting_search';
  $handler->handler = 'panel_context';
  $handler->weight = -30;
  $handler->conf = array(
    'title' => 'BReol search',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => '',
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
  $display->uuid = '1ca095a8-2f66-4488-bd64-911ec2f14399';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-4e846570-83d2-4a19-9e21-9eea5286ca80';
    $pane->panel = 'main_content';
    $pane->type = 'panels_mini';
    $pane->subtype = 'search';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => array(
        0 => 'argument_string_1',
      ),
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
    $pane->uuid = '4e846570-83d2-4a19-9e21-9eea5286ca80';
    $display->content['new-4e846570-83d2-4a19-9e21-9eea5286ca80'] = $pane;
    $display->panels['main_content'][0] = 'new-4e846570-83d2-4a19-9e21-9eea5286ca80';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = 'new-4e846570-83d2-4a19-9e21-9eea5286ca80';
  $handler->conf['display'] = $display;
  $export['search_ting_search__panel_context_8c346371-2680-4304-84f1-211870159d30'] = $handler;

  return $export;
}
