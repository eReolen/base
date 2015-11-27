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
  $handler->name = 'node_view_panel_context';
  $handler->task = 'node_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = -29;
  $handler->conf = array(
    'title' => 'Reol default pages',
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
  $display->layout = 'reol_frontpage';
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
  $display->uuid = '0edb8112-a047-497a-bf51-72720f34dfcb';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-b5e896b9-d6cb-4efa-8b7c-b1d17ac88441';
    $pane->panel = 'left';
    $pane->type = 'node_content';
    $pane->subtype = 'node_content';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'links' => 1,
      'no_extras' => 0,
      'override_title' => 0,
      'override_title_text' => '',
      'identifier' => '',
      'link' => 0,
      'leave_node_title' => 0,
      'build_mode' => 'full',
      'context' => 'argument_entity_id:node_1',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'b5e896b9-d6cb-4efa-8b7c-b1d17ac88441';
    $display->content['new-b5e896b9-d6cb-4efa-8b7c-b1d17ac88441'] = $pane;
    $display->panels['left'][0] = 'new-b5e896b9-d6cb-4efa-8b7c-b1d17ac88441';
    $pane = new stdClass();
    $pane->pid = 'new-64cdf8b7-bc5c-45cc-a97c-7d8796d75ec3';
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
    $pane->uuid = '64cdf8b7-bc5c-45cc-a97c-7d8796d75ec3';
    $display->content['new-64cdf8b7-bc5c-45cc-a97c-7d8796d75ec3'] = $pane;
    $display->panels['right'][0] = 'new-64cdf8b7-bc5c-45cc-a97c-7d8796d75ec3';
    $pane = new stdClass();
    $pane->pid = 'new-a72df90d-33cd-48f8-a072-372e2e9ae617';
    $pane->panel = 'right';
    $pane->type = 'single_review';
    $pane->subtype = 'single_review';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'type' => '',
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
    $pane->uuid = 'a72df90d-33cd-48f8-a072-372e2e9ae617';
    $display->content['new-a72df90d-33cd-48f8-a072-372e2e9ae617'] = $pane;
    $display->panels['right'][1] = 'new-a72df90d-33cd-48f8-a072-372e2e9ae617';
    $pane = new stdClass();
    $pane->pid = 'new-607fb4a8-c190-4aab-a5b2-9e60afec5eb2';
    $pane->panel = 'right';
    $pane->type = 'facebook_likebox';
    $pane->subtype = 'facebook_likebox';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'width' => '270',
      'height' => '424',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '607fb4a8-c190-4aab-a5b2-9e60afec5eb2';
    $display->content['new-607fb4a8-c190-4aab-a5b2-9e60afec5eb2'] = $pane;
    $display->panels['right'][2] = 'new-607fb4a8-c190-4aab-a5b2-9e60afec5eb2';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-b5e896b9-d6cb-4efa-8b7c-b1d17ac88441';
  $handler->conf['display'] = $display;
  $export['node_view_panel_context'] = $handler;

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
  $display->layout = 'reol_site_template';
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
      'top' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '92a45db0-147b-411f-8833-8377a52f5198';
  $display->content = array();
  $display->panels = array();
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
    $pane->css = array(
      'css_id' => '',
      'css_class' => '',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '3c879038-1011-4427-8465-f638e18375e1';
    $display->content['new-3c879038-1011-4427-8465-f638e18375e1'] = $pane;
    $display->panels['branding'][0] = 'new-3c879038-1011-4427-8465-f638e18375e1';
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
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '6ad350ba-6bd8-4e57-8001-6c2c54a7a2a9';
    $display->content['new-6ad350ba-6bd8-4e57-8001-6c2c54a7a2a9'] = $pane;
    $display->panels['branding'][1] = 'new-6ad350ba-6bd8-4e57-8001-6c2c54a7a2a9';
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
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '34bbd87e-b453-4803-9fcd-5d4b4b1c9b79';
    $display->content['new-34bbd87e-b453-4803-9fcd-5d4b4b1c9b79'] = $pane;
    $display->panels['branding'][2] = 'new-34bbd87e-b453-4803-9fcd-5d4b4b1c9b79';
    $pane = new stdClass();
    $pane->pid = 'new-bae52ec8-286d-435c-8d38-eb2e157996ac';
    $pane->panel = 'content';
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
    $display->panels['content'][0] = 'new-bae52ec8-286d-435c-8d38-eb2e157996ac';
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
    $pane->position = 1;
    $pane->locks = '';
    $pane->uuid = '1769a64d-2cbe-490d-87aa-a2c3ee082997';
    $display->content['new-1769a64d-2cbe-490d-87aa-a2c3ee082997'] = $pane;
    $display->panels['content'][1] = 'new-1769a64d-2cbe-490d-87aa-a2c3ee082997';
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
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '76338aa5-3ee9-4256-9414-eab9979db07b';
    $display->content['new-76338aa5-3ee9-4256-9414-eab9979db07b'] = $pane;
    $display->panels['content'][2] = 'new-76338aa5-3ee9-4256-9414-eab9979db07b';
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
    $pane->position = 3;
    $pane->locks = '';
    $pane->uuid = '4637ed6a-8c15-46bb-ae3b-4de4089e860d';
    $display->content['new-4637ed6a-8c15-46bb-ae3b-4de4089e860d'] = $pane;
    $display->panels['content'][3] = 'new-4637ed6a-8c15-46bb-ae3b-4de4089e860d';
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

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'user_edit_panel_context_3';
  $handler->task = 'user_edit';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = -30;
  $handler->conf = array(
    'title' => 'Reol provider profile',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(
      0 => array(
        'identifier' => 'Profile2 type',
        'keyword' => 'user_2',
        'name' => 'profile2',
        'type' => 'select',
        'uid' => '',
        'id' => 1,
      ),
    ),
    'relationships' => array(),
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'external_user',
          'settings' => NULL,
          'context' => array(
            0 => 'argument_user_edit_1',
          ),
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
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
  $display->uuid = '87c1ede8-382a-4c1e-aed4-19f750af7522';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-121673e4-ec13-4123-88da-a3851e600028';
    $pane->panel = 'left_sidebar';
    $pane->type = 'user_menu';
    $pane->subtype = 'user_menu';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => 'argument_user_edit_1',
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
    $pane->uuid = '121673e4-ec13-4123-88da-a3851e600028';
    $display->content['new-121673e4-ec13-4123-88da-a3851e600028'] = $pane;
    $display->panels['left_sidebar'][0] = 'new-121673e4-ec13-4123-88da-a3851e600028';
    $pane = new stdClass();
    $pane->pid = 'new-7a8a1910-8380-44a6-9b6e-6e1fe10cbc2d';
    $pane->panel = 'main_content';
    $pane->type = 'profile2_form';
    $pane->subtype = 'profile2_form';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => array(
        0 => 'argument_user_edit_1',
        1 => 'context_profile2_1',
      ),
      'override_title' => 1,
      'override_title_text' => 'Edit user profile',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '7a8a1910-8380-44a6-9b6e-6e1fe10cbc2d';
    $display->content['new-7a8a1910-8380-44a6-9b6e-6e1fe10cbc2d'] = $pane;
    $display->panels['main_content'][0] = 'new-7a8a1910-8380-44a6-9b6e-6e1fe10cbc2d';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['user_edit_panel_context_3'] = $handler;

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'user_view_panel_context_3';
  $handler->task = 'user_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = -30;
  $handler->conf = array(
    'title' => 'Reol provider profile',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(
      0 => array(
        'identifier' => 'Indlogget bruger',
        'keyword' => 'logged_in_user',
        'name' => 'user',
        'type' => 'current',
        'uid' => '',
        'id' => 1,
      ),
    ),
    'relationships' => array(),
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'external_user',
          'settings' => NULL,
          'context' => array(
            0 => 'argument_entity_id:user_1',
          ),
          'not' => FALSE,
        ),
        1 => array(
          'name' => 'compare_users',
          'settings' => array(
            'equality' => '1',
          ),
          'context' => array(
            0 => 'argument_entity_id:user_1',
            1 => 'logged-in-user',
          ),
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
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
  $display->title = 'Account';
  $display->uuid = 'fe43030e-e78a-44f6-96fe-691a0cfe2a70';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-931a91cb-060f-420e-9e30-0c6730464a2e';
    $pane->panel = 'left_sidebar';
    $pane->type = 'user_menu';
    $pane->subtype = 'user_menu';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'path' => '',
      'context' => 'argument_entity_id:user_1',
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
    $pane->uuid = '931a91cb-060f-420e-9e30-0c6730464a2e';
    $display->content['new-931a91cb-060f-420e-9e30-0c6730464a2e'] = $pane;
    $display->panels['left_sidebar'][0] = 'new-931a91cb-060f-420e-9e30-0c6730464a2e';
    $pane = new stdClass();
    $pane->pid = 'new-f5508570-df28-4583-9acc-59f70b1f1b2d';
    $pane->panel = 'main_content';
    $pane->type = 'library_info';
    $pane->subtype = 'library_info';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => array(
        0 => 'context_user_1',
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
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'f5508570-df28-4583-9acc-59f70b1f1b2d';
    $display->content['new-f5508570-df28-4583-9acc-59f70b1f1b2d'] = $pane;
    $display->panels['main_content'][0] = 'new-f5508570-df28-4583-9acc-59f70b1f1b2d';
    $pane = new stdClass();
    $pane->pid = 'new-9120a9cd-c9fa-47f1-91e8-90b0cfca810d';
    $pane->panel = 'main_content';
    $pane->type = 'reservations';
    $pane->subtype = 'reservations';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => 'argument_entity_id:user_1',
      'reservation_type_list' => array(
        'ready_for_pickup' => 'ready_for_pickup',
        'not_ready_for_pickup' => 0,
        'interlibrary_loans' => 0,
      ),
      'reservation_title' => 'Redeemable reservations',
      'reservation_form_id' => 'ding_reservation_reservations_ready_form',
      'form_build_id' => 'form-4IgdX9lFV0Um3jtKg4JHixkkT4Zyiq4x-rUGltYiNOw',
      'form_token' => 'ZeyaEkUO_YrkKw-kg15e6SkTPPC9H6w95aTL40LpBtg',
      'form_id' => 'ding_reservation_reservations_content_type_edit_form',
      'override_title' => 1,
      'override_title_text' => 'Redeemable reservations',
      'reservation_empty_text' => 'There are no reservations ready.',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '9120a9cd-c9fa-47f1-91e8-90b0cfca810d';
    $display->content['new-9120a9cd-c9fa-47f1-91e8-90b0cfca810d'] = $pane;
    $display->panels['main_content'][1] = 'new-9120a9cd-c9fa-47f1-91e8-90b0cfca810d';
    $pane = new stdClass();
    $pane->pid = 'new-df2e8031-847f-4a40-80c6-1ed5ab31403b';
    $pane->panel = 'main_content';
    $pane->type = 'loans';
    $pane->subtype = 'loans';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => 'argument_entity_id:user_1',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = 'df2e8031-847f-4a40-80c6-1ed5ab31403b';
    $display->content['new-df2e8031-847f-4a40-80c6-1ed5ab31403b'] = $pane;
    $display->panels['main_content'][2] = 'new-df2e8031-847f-4a40-80c6-1ed5ab31403b';
    $pane = new stdClass();
    $pane->pid = 'new-ca0fbda3-dfff-4828-8a16-8166dd7dd5b0';
    $pane->panel = 'main_content';
    $pane->type = 'reservations';
    $pane->subtype = 'reservations';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => 'argument_entity_id:user_1',
      'reservation_type_list' => array(
        'not_ready_for_pickup' => 'not_ready_for_pickup',
        'ready_for_pickup' => 0,
        'interlibrary_loans' => 0,
      ),
      'reservation_title' => 'Reservations',
      'reservation_empty_text' => 'There are no reservations.',
      'reservation_form_id' => 'ding_reservation_reservations_notready_form',
      'form_build_id' => 'form-9xiN3emIaNj9Ybn75gVRCdMJaKafWCbicJY7RhvzcbQ',
      'form_token' => 'ZeyaEkUO_YrkKw-kg15e6SkTPPC9H6w95aTL40LpBtg',
      'form_id' => 'ding_reservation_reservations_content_type_edit_form',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = 'ca0fbda3-dfff-4828-8a16-8166dd7dd5b0';
    $display->content['new-ca0fbda3-dfff-4828-8a16-8166dd7dd5b0'] = $pane;
    $display->panels['main_content'][3] = 'new-ca0fbda3-dfff-4828-8a16-8166dd7dd5b0';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['user_view_panel_context_3'] = $handler;

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
  $display->layout = 'reol_frontpage';
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
    $pane->pid = 'new-338b79a7-00fa-4342-b1c6-f9612e022ede';
    $pane->panel = 'right';
    $pane->type = 'latest';
    $pane->subtype = 'latest';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'type' => '%type:raw',
      'count' => '5',
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
    $pane->uuid = '338b79a7-00fa-4342-b1c6-f9612e022ede';
    $display->content['new-338b79a7-00fa-4342-b1c6-f9612e022ede'] = $pane;
    $display->panels['right'][0] = 'new-338b79a7-00fa-4342-b1c6-f9612e022ede';
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
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = 'a6d6657b-4a1f-4838-9716-ce70c61afb1d';
    $display->content['new-a6d6657b-4a1f-4838-9716-ce70c61afb1d'] = $pane;
    $display->panels['right'][1] = 'new-a6d6657b-4a1f-4838-9716-ce70c61afb1d';
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
  $display->layout = 'reol_frontpage';
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
      'highlight' => NULL,
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
    $pane->pid = 'new-a6e2217a-abee-4a61-aa43-c9428c0e0f39';
    $pane->panel = 'highlight';
    $pane->type = 'nonquota_banner';
    $pane->subtype = 'nonquota_banner';
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
    $pane->uuid = 'a6e2217a-abee-4a61-aa43-c9428c0e0f39';
    $display->content['new-a6e2217a-abee-4a61-aa43-c9428c0e0f39'] = $pane;
    $display->panels['highlight'][0] = 'new-a6e2217a-abee-4a61-aa43-c9428c0e0f39';
    $pane = new stdClass();
    $pane->pid = 'new-55786955-f7e6-4f41-b080-b1285000c8c8';
    $pane->panel = 'highlight';
    $pane->type = 'global_banner';
    $pane->subtype = 'global_banner';
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
    $pane->uuid = '55786955-f7e6-4f41-b080-b1285000c8c8';
    $display->content['new-55786955-f7e6-4f41-b080-b1285000c8c8'] = $pane;
    $display->panels['highlight'][1] = 'new-55786955-f7e6-4f41-b080-b1285000c8c8';
    $pane = new stdClass();
    $pane->pid = 'new-383ae229-0de9-49c6-84d9-0aeebe73f41a';
    $pane->panel = 'left';
    $pane->type = 'views_panes';
    $pane->subtype = 'articles-panel_pane_2';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'arguments' => array(
        'field_reol_entity_type_value' => '',
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
    $pane->uuid = '383ae229-0de9-49c6-84d9-0aeebe73f41a';
    $display->content['new-383ae229-0de9-49c6-84d9-0aeebe73f41a'] = $pane;
    $display->panels['left'][0] = 'new-383ae229-0de9-49c6-84d9-0aeebe73f41a';
    $pane = new stdClass();
    $pane->pid = 'new-93ea4343-2bbe-4c49-9889-b21a20719af2';
    $pane->panel = 'right';
    $pane->type = 'block';
    $pane->subtype = 'mailchimp_signup-newsletter_signup';
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
      'css_class' => 'newsletter-signup',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '93ea4343-2bbe-4c49-9889-b21a20719af2';
    $display->content['new-93ea4343-2bbe-4c49-9889-b21a20719af2'] = $pane;
    $display->panels['right'][0] = 'new-93ea4343-2bbe-4c49-9889-b21a20719af2';
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
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = 'e1c4f8f3-bd51-4c99-b9d7-e4803e54baa2';
    $display->content['new-e1c4f8f3-bd51-4c99-b9d7-e4803e54baa2'] = $pane;
    $display->panels['right'][1] = 'new-e1c4f8f3-bd51-4c99-b9d7-e4803e54baa2';
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
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '7f68e403-8055-4280-bbc7-9535051451b7';
    $display->content['new-7f68e403-8055-4280-bbc7-9535051451b7'] = $pane;
    $display->panels['right'][2] = 'new-7f68e403-8055-4280-bbc7-9535051451b7';
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
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = '5ddf7382-acc9-4abf-a148-fdb67d89b93a';
    $display->content['new-5ddf7382-acc9-4abf-a148-fdb67d89b93a'] = $pane;
    $display->panels['right'][3] = 'new-5ddf7382-acc9-4abf-a148-fdb67d89b93a';
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
