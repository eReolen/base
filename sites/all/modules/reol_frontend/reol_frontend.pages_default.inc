<?php
/**
 * @file
 * reol_frontend.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function reol_frontend_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'site_template_panel_context_2';
  $handler->task = 'site_template';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = -30;
  $handler->conf = array(
    'title' => 'eReolen site template',
    'no_blocks' => 1,
    'pipeline' => 'standard',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'access' => array(
      'plugins' => array(),
      'logic' => 'and',
    ),
    'panels_breadcrumbs_state' => 0,
    'panels_breadcrumbs_titles' => '',
    'panels_breadcrumbs_paths' => '',
    'panels_breadcrumbs_home' => 1,
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
  );
  $display = new panels_display();
  $display->layout = 'ding2_site_template';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'branding_top' => NULL,
      'header' => NULL,
      'content' => NULL,
      'footer' => NULL,
      'branding_bottom' => NULL,
      'branding' => NULL,
      'bottom' => NULL,
      'navigation' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '92a45db0-147b-411f-8833-8377a52f5198';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-bae52ec8-286d-435c-8d38-eb2e157996ac';
    $pane->panel = 'branding';
    $pane->type = 'announcement';
    $pane->subtype = 'announcement';
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
    $pane->uuid = 'bae52ec8-286d-435c-8d38-eb2e157996ac';
    $display->content['new-bae52ec8-286d-435c-8d38-eb2e157996ac'] = $pane;
    $display->panels['branding'][0] = 'new-bae52ec8-286d-435c-8d38-eb2e157996ac';
    $pane = new stdClass();
    $pane->pid = 'new-3c879038-1011-4427-8465-f638e18375e1';
    $pane->panel = 'branding';
    $pane->type = 'pane_header';
    $pane->subtype = 'pane_header';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
      'style' => 'naked',
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '3c879038-1011-4427-8465-f638e18375e1';
    $display->content['new-3c879038-1011-4427-8465-f638e18375e1'] = $pane;
    $display->panels['branding'][1] = 'new-3c879038-1011-4427-8465-f638e18375e1';
    $pane = new stdClass();
    $pane->pid = 'new-6ad350ba-6bd8-4e57-8001-6c2c54a7a2a9';
    $pane->panel = 'branding';
    $pane->type = 'block';
    $pane->subtype = 'menu-menu-tabs-menu';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => '',
    );
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '6ad350ba-6bd8-4e57-8001-6c2c54a7a2a9';
    $display->content['new-6ad350ba-6bd8-4e57-8001-6c2c54a7a2a9'] = $pane;
    $display->panels['branding'][2] = 'new-6ad350ba-6bd8-4e57-8001-6c2c54a7a2a9';
    $pane = new stdClass();
    $pane->pid = 'new-34bbd87e-b453-4803-9fcd-5d4b4b1c9b79';
    $pane->panel = 'branding';
    $pane->type = 'block';
    $pane->subtype = 'menu_block-main_menu';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'js-topbar-menu',
    );
    $pane->extras = array();
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = '34bbd87e-b453-4803-9fcd-5d4b4b1c9b79';
    $display->content['new-34bbd87e-b453-4803-9fcd-5d4b4b1c9b79'] = $pane;
    $display->panels['branding'][3] = 'new-34bbd87e-b453-4803-9fcd-5d4b4b1c9b79';
    $pane = new stdClass();
    $pane->pid = 'new-1769a64d-2cbe-490d-87aa-a2c3ee082997';
    $pane->panel = 'content';
    $pane->type = 'page_messages';
    $pane->subtype = 'page_messages';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
      'style' => 'default',
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'system-messages',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = '';
    $pane->uuid = '1769a64d-2cbe-490d-87aa-a2c3ee082997';
    $display->content['new-1769a64d-2cbe-490d-87aa-a2c3ee082997'] = $pane;
    $display->panels['content'][0] = 'new-1769a64d-2cbe-490d-87aa-a2c3ee082997';
    $pane = new stdClass();
    $pane->pid = 'new-76338aa5-3ee9-4256-9414-eab9979db07b';
    $pane->panel = 'content';
    $pane->type = 'page_tabs';
    $pane->subtype = 'page_tabs';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(
        1 => array(
          'name' => 'external_user',
          'settings' => NULL,
          'context' => array(
            0 => 'logged-in-user',
          ),
          'not' => TRUE,
        ),
        2 => array(
          'name' => 'path_visibility',
          'settings' => array(
            'visibility_setting' => '1',
            'paths' => 'user/*',
          ),
          'context' => 'empty',
          'not' => TRUE,
        ),
      ),
      'logic' => 'or',
    );
    $pane->configuration = array(
      'type' => 'both',
      'id' => 'tabs',
      'override_title' => 1,
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
    $pane->uuid = '76338aa5-3ee9-4256-9414-eab9979db07b';
    $display->content['new-76338aa5-3ee9-4256-9414-eab9979db07b'] = $pane;
    $display->panels['content'][1] = 'new-76338aa5-3ee9-4256-9414-eab9979db07b';
    $pane = new stdClass();
    $pane->pid = 'new-4637ed6a-8c15-46bb-ae3b-4de4089e860d';
    $pane->panel = 'content';
    $pane->type = 'page_content';
    $pane->subtype = 'page_content';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => 'argument_page_content_1',
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = '';
    $pane->uuid = '4637ed6a-8c15-46bb-ae3b-4de4089e860d';
    $display->content['new-4637ed6a-8c15-46bb-ae3b-4de4089e860d'] = $pane;
    $display->panels['content'][2] = 'new-4637ed6a-8c15-46bb-ae3b-4de4089e860d';
    $pane = new stdClass();
    $pane->pid = 'new-fd6dbb4f-c7b5-4881-96d2-769a6c16bfc2';
    $pane->panel = 'footer';
    $pane->type = 'block';
    $pane->subtype = 'menu-menu-footer-menu-1';
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
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'attachment-first',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = '';
    $pane->uuid = 'fd6dbb4f-c7b5-4881-96d2-769a6c16bfc2';
    $display->content['new-fd6dbb4f-c7b5-4881-96d2-769a6c16bfc2'] = $pane;
    $display->panels['footer'][0] = 'new-fd6dbb4f-c7b5-4881-96d2-769a6c16bfc2';
    $pane = new stdClass();
    $pane->pid = 'new-3a72e819-3274-4d12-8fe3-414c0cbc3151';
    $pane->panel = 'footer';
    $pane->type = 'block';
    $pane->subtype = 'menu-menu-footer-menu-2';
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
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'attachment-second',
    );
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = '';
    $pane->uuid = '3a72e819-3274-4d12-8fe3-414c0cbc3151';
    $display->content['new-3a72e819-3274-4d12-8fe3-414c0cbc3151'] = $pane;
    $display->panels['footer'][1] = 'new-3a72e819-3274-4d12-8fe3-414c0cbc3151';
    $pane = new stdClass();
    $pane->pid = 'new-d9877e3c-cae9-4067-99af-305cb0e70bf9';
    $pane->panel = 'footer';
    $pane->type = 'block';
    $pane->subtype = 'menu-menu-footer-menu-3';
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
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'attachment-third',
    );
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = '';
    $pane->uuid = 'd9877e3c-cae9-4067-99af-305cb0e70bf9';
    $display->content['new-d9877e3c-cae9-4067-99af-305cb0e70bf9'] = $pane;
    $display->panels['footer'][2] = 'new-d9877e3c-cae9-4067-99af-305cb0e70bf9';
    $pane = new stdClass();
    $pane->pid = 'new-d59734fe-4c31-4b3c-af53-5c2bad02f9cf';
    $pane->panel = 'footer';
    $pane->type = 'block';
    $pane->subtype = 'menu-menu-footer-menu-4';
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
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'attachment-fourth',
    );
    $pane->extras = array();
    $pane->position = 3;
    $pane->locks = '';
    $pane->uuid = 'd59734fe-4c31-4b3c-af53-5c2bad02f9cf';
    $display->content['new-d59734fe-4c31-4b3c-af53-5c2bad02f9cf'] = $pane;
    $display->panels['footer'][3] = 'new-d59734fe-4c31-4b3c-af53-5c2bad02f9cf';
    $pane = new stdClass();
    $pane->pid = 'new-f06a4c37-1ed2-4a64-8502-7b8d4d0619b0';
    $pane->panel = 'header';
    $pane->type = 'block';
    $pane->subtype = 'search-form';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
      'style' => 'default',
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'f06a4c37-1ed2-4a64-8502-7b8d4d0619b0';
    $display->content['new-f06a4c37-1ed2-4a64-8502-7b8d4d0619b0'] = $pane;
    $display->panels['header'][0] = 'new-f06a4c37-1ed2-4a64-8502-7b8d4d0619b0';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['site_template_panel_context_2'] = $handler;

  return $export;
}

/**
 * Implements hook_default_page_manager_pages().
 */
function reol_frontend_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'reol_frontpage';
  $page->task = 'page';
  $page->admin_title = 'Frontpage';
  $page->admin_description = '';
  $page->path = 'reol_frontpage/!type';
  $page->access = array(
    'type' => 'none',
    'settings' => NULL,
  );
  $page->menu = array();
  $page->arguments = array(
    'type' => array(
      'id' => 1,
      'identifier' => 'Type',
      'name' => 'string',
      'settings' => array(
        'use_tail' => 0,
      ),
    ),
  );
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_reol_frontpage_panel_context_2';
  $handler->task = 'page';
  $handler->subtask = 'reol_frontpage';
  $handler->handler = 'panel_context';
  $handler->weight = -30;
  $handler->conf = array(
    'title' => 'Type frontpage',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'access' => array(
      'logic' => 'and',
      'plugins' => array(
        0 => array(
          'name' => 'context_exists',
          'settings' => array(
            'exists' => '1',
          ),
          'context' => 'argument_string_1',
          'not' => FALSE,
        ),
      ),
    ),
  );
  $display = new panels_display();
  $display->layout = 'flexible:reol_frontpage_layout';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'top' => NULL,
      'left' => NULL,
      'right' => NULL,
      'bottom' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '29b1eda2-6ba2-4b0b-8107-b07b49415d10';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-ac463184-769d-4149-9d46-b4f2d8f3c4e7';
    $pane->panel = 'bottom';
    $pane->type = 'views_panes';
    $pane->subtype = 'author_portraits-panel_pane_2';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'arguments' => array(
        'field_reol_entity_type_value' => '%type:raw',
      ),
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'ac463184-769d-4149-9d46-b4f2d8f3c4e7';
    $display->content['new-ac463184-769d-4149-9d46-b4f2d8f3c4e7'] = $pane;
    $display->panels['bottom'][0] = 'new-ac463184-769d-4149-9d46-b4f2d8f3c4e7';
    $pane = new stdClass();
    $pane->pid = 'new-ebc6be3d-c779-43f8-bf16-9556f90c5ff9';
    $pane->panel = 'bottom';
    $pane->type = 'views_panes';
    $pane->subtype = 'videos-panel_pane_1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'arguments' => array(
        'field_reol_entity_type_value' => '%type:raw',
      ),
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = 'ebc6be3d-c779-43f8-bf16-9556f90c5ff9';
    $display->content['new-ebc6be3d-c779-43f8-bf16-9556f90c5ff9'] = $pane;
    $display->panels['bottom'][1] = 'new-ebc6be3d-c779-43f8-bf16-9556f90c5ff9';
    $pane = new stdClass();
    $pane->pid = 'new-bddea60b-3c78-4338-8ac3-4caf87e5a482';
    $pane->panel = 'left';
    $pane->type = 'views_panes';
    $pane->subtype = 'articles-panel_pane_1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'arguments' => array(
        'field_reol_entity_type_value' => '%type:raw',
      ),
      'exposed' => array(
        'filter-field_reol_entity_type_value' => array(
          'field_reol_entity_type_value' => '',
        ),
      ),
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'bddea60b-3c78-4338-8ac3-4caf87e5a482';
    $display->content['new-bddea60b-3c78-4338-8ac3-4caf87e5a482'] = $pane;
    $display->panels['left'][0] = 'new-bddea60b-3c78-4338-8ac3-4caf87e5a482';
    $pane = new stdClass();
    $pane->pid = 'new-a6d6657b-4a1f-4838-9716-ce70c61afb1d';
    $pane->panel = 'right';
    $pane->type = 'single_review';
    $pane->subtype = 'single_review';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '',
      'type' => '%type:raw',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'a6d6657b-4a1f-4838-9716-ce70c61afb1d';
    $display->content['new-a6d6657b-4a1f-4838-9716-ce70c61afb1d'] = $pane;
    $display->panels['right'][0] = 'new-a6d6657b-4a1f-4838-9716-ce70c61afb1d';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_reol_frontpage_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'reol_frontpage';
  $handler->handler = 'panel_context';
  $handler->weight = -29;
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
  $display->layout = 'flexible:reol_frontpage_layout';
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
      'top' => NULL,
      'left' => NULL,
      'right' => NULL,
      'bottom' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '693dca14-4273-4397-8a34-ae7384d8fbf2';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-55e54c4d-81d0-4c89-b764-cb03d72f575e';
    $pane->panel = 'bottom';
    $pane->type = 'views_panes';
    $pane->subtype = 'author_portraits-panel_pane_1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '55e54c4d-81d0-4c89-b764-cb03d72f575e';
    $display->content['new-55e54c4d-81d0-4c89-b764-cb03d72f575e'] = $pane;
    $display->panels['bottom'][0] = 'new-55e54c4d-81d0-4c89-b764-cb03d72f575e';
    $pane = new stdClass();
    $pane->pid = 'new-523f8d67-78fd-4cc7-957b-6c7bf7fb08fc';
    $pane->panel = 'left';
    $pane->type = 'views_panes';
    $pane->subtype = 'articles-panel_pane_1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '523f8d67-78fd-4cc7-957b-6c7bf7fb08fc';
    $display->content['new-523f8d67-78fd-4cc7-957b-6c7bf7fb08fc'] = $pane;
    $display->panels['left'][0] = 'new-523f8d67-78fd-4cc7-957b-6c7bf7fb08fc';
    $pane = new stdClass();
    $pane->pid = 'new-e1c4f8f3-bd51-4c99-b9d7-e4803e54baa2';
    $pane->panel = 'right';
    $pane->type = 'quick_guide';
    $pane->subtype = 'quick_guide';
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
    $pane->uuid = 'e1c4f8f3-bd51-4c99-b9d7-e4803e54baa2';
    $display->content['new-e1c4f8f3-bd51-4c99-b9d7-e4803e54baa2'] = $pane;
    $display->panels['right'][0] = 'new-e1c4f8f3-bd51-4c99-b9d7-e4803e54baa2';
    $pane = new stdClass();
    $pane->pid = 'new-7f68e403-8055-4280-bbc7-9535051451b7';
    $pane->panel = 'right';
    $pane->type = 'single_review';
    $pane->subtype = 'single_review';
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
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '7f68e403-8055-4280-bbc7-9535051451b7';
    $display->content['new-7f68e403-8055-4280-bbc7-9535051451b7'] = $pane;
    $display->panels['right'][1] = 'new-7f68e403-8055-4280-bbc7-9535051451b7';
    $pane = new stdClass();
    $pane->pid = 'new-5ddf7382-acc9-4abf-a148-fdb67d89b93a';
    $pane->panel = 'right';
    $pane->type = 'facebook_likebox';
    $pane->subtype = 'facebook_likebox';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '',
      'width' => '270',
      'height' => '424',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '5ddf7382-acc9-4abf-a148-fdb67d89b93a';
    $display->content['new-5ddf7382-acc9-4abf-a148-fdb67d89b93a'] = $pane;
    $display->panels['right'][2] = 'new-5ddf7382-acc9-4abf-a148-fdb67d89b93a';
    $pane = new stdClass();
    $pane->pid = 'new-7e3d15e0-e9cf-40f9-89ab-658161b063e0';
    $pane->panel = 'top';
    $pane->type = 'carousel';
    $pane->subtype = 'carousel';
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
    $pane->uuid = '7e3d15e0-e9cf-40f9-89ab-658161b063e0';
    $display->content['new-7e3d15e0-e9cf-40f9-89ab-658161b063e0'] = $pane;
    $display->panels['top'][0] = 'new-7e3d15e0-e9cf-40f9-89ab-658161b063e0';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-7e3d15e0-e9cf-40f9-89ab-658161b063e0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['reol_frontpage'] = $page;

  return $pages;

}
