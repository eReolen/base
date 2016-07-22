<?php
/**
 * @file
 * breol_subject.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function breol_subject_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'node_view__panel_context_3acb8dd5-d3f0-42e6-ba3c-336f66ff568d';
  $handler->task = 'node_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = -100;
  $handler->conf = array(
    'title' => 'Theme page',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(
      0 => array(
        'identifier' => 'Search string from node',
        'keyword' => 'string',
        'name' => 'search_string_from_node',
        'context' => 'argument_entity_id:node_1',
        'id' => 1,
      ),
    ),
    'name' => '',
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'breol_subject' => 'breol_subject',
            ),
          ),
          'context' => 'argument_entity_id:node_1',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
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
  $display->uuid = 'bbce12ef-9e16-48e3-a5e9-c2ef848f6036';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-7fcb4ff3-cb9a-45fb-a763-73739210062e';
    $pane->panel = 'main_content';
    $pane->type = 'node_content';
    $pane->subtype = 'node_content';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'links' => 0,
      'no_extras' => 1,
      'override_title' => 1,
      'override_title_text' => '',
      'identifier' => '',
      'link' => 0,
      'leave_node_title' => 1,
      'build_mode' => 'full',
      'context' => 'argument_entity_id:node_1',
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
    $pane->uuid = '7fcb4ff3-cb9a-45fb-a763-73739210062e';
    $display->content['new-7fcb4ff3-cb9a-45fb-a763-73739210062e'] = $pane;
    $display->panels['main_content'][0] = 'new-7fcb4ff3-cb9a-45fb-a763-73739210062e';
    $pane = new stdClass();
    $pane->pid = 'new-1b4e53f5-464a-4347-8b57-3bec0f66a346';
    $pane->panel = 'main_content';
    $pane->type = 'panels_mini';
    $pane->subtype = 'search';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => array(
        0 => 'relationship_search_string_from_node_1',
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
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '1b4e53f5-464a-4347-8b57-3bec0f66a346';
    $display->content['new-1b4e53f5-464a-4347-8b57-3bec0f66a346'] = $pane;
    $display->panels['main_content'][1] = 'new-1b4e53f5-464a-4347-8b57-3bec0f66a346';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['node_view__panel_context_3acb8dd5-d3f0-42e6-ba3c-336f66ff568d'] = $handler;

  return $export;
}
