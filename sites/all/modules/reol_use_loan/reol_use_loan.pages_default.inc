<?php
/**
 * @file
 * reol_use_loan.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function reol_use_loan_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'listen_to_audiobook';
  $page->task = 'page';
  $page->admin_title = 'Listen to audiobook';
  $page->admin_description = '';
  $page->path = 'ting/object/%ting_object/listen';
  $page->access = array();
  $page->menu = array();
  $page->arguments = array(
    'ting_object' => array(
      'id' => 1,
      'identifier' => 'Ting object: ID',
      'name' => 'ting_object_id',
      'settings' => array(),
    ),
  );
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_listen_to_audiobook_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'listen_to_audiobook';
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
  );
  $display = new panels_display();
  $display->layout = '25_50_25';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'middle' => NULL,
      'left_sidebar' => NULL,
      'main_content' => NULL,
      'right_sidebar' => NULL,
      'attachment_4_1' => NULL,
      'attachment_4_2' => NULL,
      'attachment_4_3' => NULL,
      'attachment_4_4' => NULL,
      'attachment_3_1' => NULL,
      'attachment_3_2' => NULL,
      'attachment_3_3' => NULL,
      'attachment_2_1' => NULL,
      'attachment_2_2' => NULL,
      'attachment_1_1' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = 'bfd457ee-a785-4700-b450-4f09a4c5acab';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-d333ce66-d379-4e8d-baf5-6d17a5725c67';
    $pane->panel = 'main_content';
    $pane->type = 'back';
    $pane->subtype = 'back';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'd333ce66-d379-4e8d-baf5-6d17a5725c67';
    $display->content['new-d333ce66-d379-4e8d-baf5-6d17a5725c67'] = $pane;
    $display->panels['main_content'][0] = 'new-d333ce66-d379-4e8d-baf5-6d17a5725c67';
    $pane = new stdClass();
    $pane->pid = 'new-5e585727-e262-4dfc-94bc-56e099fcc4f5';
    $pane->panel = 'main_content';
    $pane->type = 'listen';
    $pane->subtype = 'listen';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => array(
        0 => 'argument_ting_object_id_1',
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
    $pane->uuid = '5e585727-e262-4dfc-94bc-56e099fcc4f5';
    $display->content['new-5e585727-e262-4dfc-94bc-56e099fcc4f5'] = $pane;
    $display->panels['main_content'][1] = 'new-5e585727-e262-4dfc-94bc-56e099fcc4f5';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-5e585727-e262-4dfc-94bc-56e099fcc4f5';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['listen_to_audiobook'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'read_ebook';
  $page->task = 'page';
  $page->admin_title = 'Read ebook';
  $page->admin_description = '';
  $page->path = 'ting/object/%ting_object/read';
  $page->access = array(
    'type' => 'none',
    'settings' => NULL,
  );
  $page->menu = array();
  $page->arguments = array(
    'ting_object' => array(
      'id' => 1,
      'identifier' => 'Ting object: ID',
      'name' => 'ting_object_id',
      'settings' => array(),
    ),
  );
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_read_ebook_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'read_ebook';
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
  );
  $display = new panels_display();
  $display->layout = '25_50_25';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'left_sidebar' => NULL,
      'main_content' => NULL,
      'right_sidebar' => NULL,
      'attachment_4_1' => NULL,
      'attachment_4_2' => NULL,
      'attachment_4_3' => NULL,
      'attachment_4_4' => NULL,
      'attachment_3_1' => NULL,
      'attachment_3_2' => NULL,
      'attachment_3_3' => NULL,
      'attachment_2_1' => NULL,
      'attachment_2_2' => NULL,
      'attachment_1_1' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '297cd660-d945-4b5b-b9b4-59aa4b50f4ce';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-eb7c169a-cb25-473c-8e39-831968696db4';
    $pane->panel = 'main_content';
    $pane->type = 'back';
    $pane->subtype = 'back';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'eb7c169a-cb25-473c-8e39-831968696db4';
    $display->content['new-eb7c169a-cb25-473c-8e39-831968696db4'] = $pane;
    $display->panels['main_content'][0] = 'new-eb7c169a-cb25-473c-8e39-831968696db4';
    $pane = new stdClass();
    $pane->pid = 'new-30f9510c-9fc5-4465-9e8a-fb1a619a6d23';
    $pane->panel = 'main_content';
    $pane->type = 'read';
    $pane->subtype = 'read';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => array(
        0 => 'argument_ting_object_id_1',
      ),
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '30f9510c-9fc5-4465-9e8a-fb1a619a6d23';
    $display->content['new-30f9510c-9fc5-4465-9e8a-fb1a619a6d23'] = $pane;
    $display->panels['main_content'][1] = 'new-30f9510c-9fc5-4465-9e8a-fb1a619a6d23';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-30f9510c-9fc5-4465-9e8a-fb1a619a6d23';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['read_ebook'] = $page;

  return $pages;

}
