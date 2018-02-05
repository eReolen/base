<?php
/**
 * @file
 * ereol_frontend.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function ereol_frontend_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'search_node__ereolen-search-nodes';
  $handler->task = 'search';
  $handler->subtask = 'node';
  $handler->handler = 'panel_context';
  $handler->weight = -100;
  $handler->conf = array(
    'title' => 'eReolen search nodes',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'panels_breadcrumbs_state' => 1,
    'panels_breadcrumbs_titles' => 'Search
Website',
    'panels_breadcrumbs_paths' => 'search
search/node',
    'metatag_panels' => array(
      'enabled' => 1,
      'metatags' => array(
        'title' => array(
          'value' => 'Search Content | %keywords:html_safe | [current-page:pager][site:name]',
        ),
      ),
    ),
    'name' => 'ereolen-search-nodes',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
  );
  $display = new panels_display();
  $display->layout = 'onecol';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'middle' => NULL,
      'left' => NULL,
      'right' => NULL,
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
  $display->uuid = '1e811334-76b6-4702-b0bc-7d315e6b4b2e';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-06e03f81-aacd-462e-be56-7cd9bcd2e5dc';
    $pane->panel = 'middle';
    $pane->type = 'search_backends';
    $pane->subtype = 'search_backends';
    $pane->shown = FALSE;
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
    $pane->uuid = '06e03f81-aacd-462e-be56-7cd9bcd2e5dc';
    $display->content['new-06e03f81-aacd-462e-be56-7cd9bcd2e5dc'] = $pane;
    $display->panels['middle'][0] = 'new-06e03f81-aacd-462e-be56-7cd9bcd2e5dc';
    $pane = new stdClass();
    $pane->pid = 'new-241962fe-b059-4363-92cf-42080da67029';
    $pane->panel = 'middle';
    $pane->type = 'views';
    $pane->subtype = 'ereol_search';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 1,
      'nodes_per_page' => '0',
      'pager_id' => '0',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 1,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'default',
      'context' => array(
        0 => 'argument_string_1.raw',
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
    $pane->uuid = '241962fe-b059-4363-92cf-42080da67029';
    $display->content['new-241962fe-b059-4363-92cf-42080da67029'] = $pane;
    $display->panels['middle'][1] = 'new-241962fe-b059-4363-92cf-42080da67029';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['search_node__ereolen-search-nodes'] = $handler;

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'search_ting_search__ereolen-search';
  $handler->task = 'search';
  $handler->subtask = 'ting_search';
  $handler->handler = 'panel_context';
  $handler->weight = -30;
  $handler->conf = array(
    'title' => 'eReolen search',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'panels_breadcrumbs_state' => 1,
    'panels_breadcrumbs_titles' => 'Search
Well
%keywords:html_safe',
    'panels_breadcrumbs_paths' => 'search
search/ting
<none>
',
    'name' => 'ereolen-search',
  );
  $display = new panels_display();
  $display->layout = 'twocol_stacked';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'middle' => NULL,
      'left' => NULL,
      'right' => NULL,
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
      'bottom' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = 'caa15777-4cfc-4926-8c39-6af276f23582';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-f3a42372-e2fb-45e6-a62b-79c707f0a35d';
    $pane->panel = 'left';
    $pane->type = 'search_result_count';
    $pane->subtype = 'search_result_count';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => 'argument_string_1',
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
    $pane->uuid = 'f3a42372-e2fb-45e6-a62b-79c707f0a35d';
    $display->content['new-f3a42372-e2fb-45e6-a62b-79c707f0a35d'] = $pane;
    $display->panels['left'][0] = 'new-f3a42372-e2fb-45e6-a62b-79c707f0a35d';
    $pane = new stdClass();
    $pane->pid = 'new-f5097d22-b99c-49be-a0df-6b45a7d0d83c';
    $pane->panel = 'left';
    $pane->type = 'ding_facetbrowser';
    $pane->subtype = 'ding_facetbrowser';
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
    $pane->position = 1;
    $pane->locks = '';
    $pane->uuid = 'f5097d22-b99c-49be-a0df-6b45a7d0d83c';
    $display->content['new-f5097d22-b99c-49be-a0df-6b45a7d0d83c'] = $pane;
    $display->panels['left'][1] = 'new-f5097d22-b99c-49be-a0df-6b45a7d0d83c';
    $pane = new stdClass();
    $pane->pid = 'new-7c02f708-c47f-4eb5-8958-d6279de6ade4';
    $pane->panel = 'right';
    $pane->type = 'search_result';
    $pane->subtype = 'search_result';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'type' => 'ting_search',
      'log' => 0,
      'override_empty' => 0,
      'empty_title' => '',
      'empty' => '',
      'empty_format' => 'plain_text',
      'override_no_key' => 0,
      'no_key_title' => '',
      'no_key' => '',
      'no_key_format' => 'plain_text',
      'context' => 'argument_string_1',
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = '';
    $pane->uuid = '7c02f708-c47f-4eb5-8958-d6279de6ade4';
    $display->content['new-7c02f708-c47f-4eb5-8958-d6279de6ade4'] = $pane;
    $display->panels['right'][0] = 'new-7c02f708-c47f-4eb5-8958-d6279de6ade4';
    $pane = new stdClass();
    $pane->pid = 'new-5929c0c7-25f7-4d61-8829-81a740e6f77e';
    $pane->panel = 'top';
    $pane->type = 'search_backends';
    $pane->subtype = 'search_backends';
    $pane->shown = FALSE;
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
    $pane->uuid = '5929c0c7-25f7-4d61-8829-81a740e6f77e';
    $display->content['new-5929c0c7-25f7-4d61-8829-81a740e6f77e'] = $pane;
    $display->panels['top'][0] = 'new-5929c0c7-25f7-4d61-8829-81a740e6f77e';
    $pane = new stdClass();
    $pane->pid = 'new-07d2c562-f846-4241-b93f-7c1d723ff29d';
    $pane->panel = 'top';
    $pane->type = 'campaign';
    $pane->subtype = 'campaign';
    $pane->shown = FALSE;
    $pane->access = array();
    $pane->configuration = array(
      'ding_campaign_count' => 3,
      'ding_campaign_offset' => 0,
      'context' => array(
        0 => 'empty',
        1 => 'empty',
        2 => 'argument_string_1',
        3 => 'empty',
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
    $pane->locks = '';
    $pane->uuid = '07d2c562-f846-4241-b93f-7c1d723ff29d';
    $display->content['new-07d2c562-f846-4241-b93f-7c1d723ff29d'] = $pane;
    $display->panels['top'][1] = 'new-07d2c562-f846-4241-b93f-7c1d723ff29d';
    $pane = new stdClass();
    $pane->pid = 'new-47206bf0-1031-456c-9aab-96b659e54d89';
    $pane->panel = 'top';
    $pane->type = 'search_per_page';
    $pane->subtype = 'search_per_page';
    $pane->shown = FALSE;
    $pane->access = array();
    $pane->configuration = array(
      'select_type' => 'dropdown',
      'context' => 'argument_string_1',
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
    $pane->uuid = '47206bf0-1031-456c-9aab-96b659e54d89';
    $display->content['new-47206bf0-1031-456c-9aab-96b659e54d89'] = $pane;
    $display->panels['top'][2] = 'new-47206bf0-1031-456c-9aab-96b659e54d89';
    $pane = new stdClass();
    $pane->pid = 'new-dd50ebf9-a0f1-499b-b389-49f178f5e242';
    $pane->panel = 'top';
    $pane->type = 'block';
    $pane->subtype = 'ting_search-sort_form';
    $pane->shown = FALSE;
    $pane->access = array();
    $pane->configuration = array(
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
    $pane->uuid = 'dd50ebf9-a0f1-499b-b389-49f178f5e242';
    $display->content['new-dd50ebf9-a0f1-499b-b389-49f178f5e242'] = $pane;
    $display->panels['top'][3] = 'new-dd50ebf9-a0f1-499b-b389-49f178f5e242';
    $pane = new stdClass();
    $pane->pid = 'new-4068f188-91e2-474e-a160-3deb53f8636f';
    $pane->panel = 'top';
    $pane->type = 'search_query';
    $pane->subtype = 'search_query';
    $pane->shown = FALSE;
    $pane->access = array(
      'plugins' => array(
        0 => array(
          'name' => 'external_user',
          'settings' => NULL,
          'context' => array(
            0 => 'logged-in-user',
          ),
          'not' => FALSE,
        ),
      ),
    );
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 4;
    $pane->locks = array();
    $pane->uuid = '4068f188-91e2-474e-a160-3deb53f8636f';
    $display->content['new-4068f188-91e2-474e-a160-3deb53f8636f'] = $pane;
    $display->panels['top'][4] = 'new-4068f188-91e2-474e-a160-3deb53f8636f';
    $pane = new stdClass();
    $pane->pid = 'new-7281f66a-4813-462c-a9b3-02e804941eb2';
    $pane->panel = 'top';
    $pane->type = 'zero_search_carousel';
    $pane->subtype = 'zero_search_carousel';
    $pane->shown = FALSE;
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
    $pane->position = 5;
    $pane->locks = array();
    $pane->uuid = '7281f66a-4813-462c-a9b3-02e804941eb2';
    $display->content['new-7281f66a-4813-462c-a9b3-02e804941eb2'] = $pane;
    $display->panels['top'][5] = 'new-7281f66a-4813-462c-a9b3-02e804941eb2';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['search_ting_search__ereolen-search'] = $handler;

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'site_template_panel_context_2';
  $handler->task = 'site_template';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = -28;
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
    $pane->pid = 'new-2703a01e-83e1-4344-aa75-91d3ba70f2ff';
    $pane->panel = 'branding';
    $pane->type = 'menu_tree';
    $pane->subtype = 'main-menu';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'parent' => 'main-menu:0',
      'title_link' => 0,
      'admin_title' => NULL,
      'level' => '1',
      'follow' => 0,
      'depth' => '1',
      'depth_relative' => NULL,
      'expanded' => 0,
      'sort' => 0,
      'menu_name' => 'main-menu',
      'parent_mlid' => '0',
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
    $pane->uuid = '2703a01e-83e1-4344-aa75-91d3ba70f2ff';
    $display->content['new-2703a01e-83e1-4344-aa75-91d3ba70f2ff'] = $pane;
    $display->panels['branding'][1] = 'new-2703a01e-83e1-4344-aa75-91d3ba70f2ff';
    $pane = new stdClass();
    $pane->pid = 'new-8c79c7df-e311-4af4-965f-50d239f6ecec';
    $pane->panel = 'branding';
    $pane->type = 'reol_profile_link';
    $pane->subtype = 'reol_profile_link';
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
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '8c79c7df-e311-4af4-965f-50d239f6ecec';
    $display->content['new-8c79c7df-e311-4af4-965f-50d239f6ecec'] = $pane;
    $display->panels['branding'][2] = 'new-8c79c7df-e311-4af4-965f-50d239f6ecec';
    $pane = new stdClass();
    $pane->pid = 'new-76338aa5-3ee9-4256-9414-eab9979db07b';
    $pane->panel = 'content';
    $pane->type = 'page_tabs';
    $pane->subtype = 'page_tabs';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(
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
      'logic' => 'and',
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
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '76338aa5-3ee9-4256-9414-eab9979db07b';
    $display->content['new-76338aa5-3ee9-4256-9414-eab9979db07b'] = $pane;
    $display->panels['content'][0] = 'new-76338aa5-3ee9-4256-9414-eab9979db07b';
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
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = 'bae52ec8-286d-435c-8d38-eb2e157996ac';
    $display->content['new-bae52ec8-286d-435c-8d38-eb2e157996ac'] = $pane;
    $display->panels['content'][2] = 'new-bae52ec8-286d-435c-8d38-eb2e157996ac';
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
    $pane->pid = 'new-b200fc05-2e44-40a0-a5a1-5f59cf864f2d';
    $pane->panel = 'header';
    $pane->type = 'block';
    $pane->subtype = 'search-form';
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
    $pane->uuid = 'b200fc05-2e44-40a0-a5a1-5f59cf864f2d';
    $display->content['new-b200fc05-2e44-40a0-a5a1-5f59cf864f2d'] = $pane;
    $display->panels['header'][0] = 'new-b200fc05-2e44-40a0-a5a1-5f59cf864f2d';
    $pane = new stdClass();
    $pane->pid = 'new-42da6d6c-e8e4-49b8-89d6-35c1f48aa665';
    $pane->panel = 'header';
    $pane->type = 'menu_tree';
    $pane->subtype = 'main-menu';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'parent' => 'main-menu:0',
      'title_link' => 0,
      'admin_title' => NULL,
      'level' => '2',
      'follow' => 0,
      'depth' => '0',
      'depth_relative' => NULL,
      'expanded' => 1,
      'sort' => 0,
      'menu_name' => 'main-menu',
      'parent_mlid' => '0',
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
    $pane->uuid = '42da6d6c-e8e4-49b8-89d6-35c1f48aa665';
    $display->content['new-42da6d6c-e8e4-49b8-89d6-35c1f48aa665'] = $pane;
    $display->panels['header'][1] = 'new-42da6d6c-e8e4-49b8-89d6-35c1f48aa665';
    $pane = new stdClass();
    $pane->pid = 'new-407ab43a-dfc4-49ea-a537-292b9d04c95c';
    $pane->panel = 'header';
    $pane->type = 'block';
    $pane->subtype = 'user-login';
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
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'main-login-form',
    );
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '407ab43a-dfc4-49ea-a537-292b9d04c95c';
    $display->content['new-407ab43a-dfc4-49ea-a537-292b9d04c95c'] = $pane;
    $display->panels['header'][2] = 'new-407ab43a-dfc4-49ea-a537-292b9d04c95c';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['site_template_panel_context_2'] = $handler;

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'site_template_panel_context_3';
  $handler->task = 'site_template';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = -30;
  $handler->conf = array(
    'title' => 'eReolen app mode',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'app_mode',
          'settings' => NULL,
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
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
  $display->uuid = 'bb5be69d-d59b-4c9a-8295-9046957d9713';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-0615016f-6be0-4782-a45e-6e3d23fcd679';
    $pane->panel = 'middle';
    $pane->type = 'pane_messages';
    $pane->subtype = 'pane_messages';
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
    $pane->uuid = '0615016f-6be0-4782-a45e-6e3d23fcd679';
    $display->content['new-0615016f-6be0-4782-a45e-6e3d23fcd679'] = $pane;
    $display->panels['middle'][0] = 'new-0615016f-6be0-4782-a45e-6e3d23fcd679';
    $pane = new stdClass();
    $pane->pid = 'new-3e342f33-a104-4f07-a39e-5430fa6252b3';
    $pane->panel = 'middle';
    $pane->type = 'page_content';
    $pane->subtype = 'page_content';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => 'argument_page_content_1',
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
    $pane->uuid = '3e342f33-a104-4f07-a39e-5430fa6252b3';
    $display->content['new-3e342f33-a104-4f07-a39e-5430fa6252b3'] = $pane;
    $display->panels['middle'][1] = 'new-3e342f33-a104-4f07-a39e-5430fa6252b3';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-3e342f33-a104-4f07-a39e-5430fa6252b3';
  $handler->conf['display'] = $display;
  $export['site_template_panel_context_3'] = $handler;

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'ting_collection__ereolen-ting-collection';
  $handler->task = 'ting_collection';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = -100;
  $handler->conf = array(
    'title' => 'eReolen ting collection',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'metatag_panels' => array(
      'enabled' => 1,
      'metatags' => array(
        'title' => array(
          'value' => 'Ting collection | %ting_collection:title_full | [current-page:pager][site:name]',
        ),
      ),
    ),
    'name' => 'ereolen-ting-collection',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
  );
  $display = new panels_display();
  $display->layout = 'onecol';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'left' => NULL,
      'middle' => NULL,
      'right' => NULL,
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
  $display->uuid = 'accd93cd-f443-4d6e-9be8-d91300f9b07a';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-55cc4d0d-d8cd-46ae-96f7-18bb4fc809c8';
    $pane->panel = 'middle';
    $pane->type = 'ting_collection';
    $pane->subtype = 'ting_collection';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => 'argument_ting_collection_id_17',
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = '';
    $pane->uuid = '55cc4d0d-d8cd-46ae-96f7-18bb4fc809c8';
    $display->content['new-55cc4d0d-d8cd-46ae-96f7-18bb4fc809c8'] = $pane;
    $display->panels['middle'][0] = 'new-55cc4d0d-d8cd-46ae-96f7-18bb4fc809c8';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['ting_collection__ereolen-ting-collection'] = $handler;

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'ting_object__ereolen-ting-object';
  $handler->task = 'ting_object';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = -100;
  $handler->conf = array(
    'title' => 'eReolen ting object',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'metatag_panels' => array(
      'enabled' => 1,
      'metatags' => array(
        'title' => array(
          'value' => 'Ting object | %ting_object:title_full | [current-page:pager][site:name]',
        ),
      ),
    ),
    'name' => 'ereolen-ting-object',
  );
  $display = new panels_display();
  $display->layout = 'onecol';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'left' => NULL,
      'middle' => NULL,
      'right' => NULL,
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
  $display->uuid = '7da7c33f-8425-44e8-a02d-0f497e4945e0';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-eda37090-d344-4baa-8c21-78573268da3d';
    $pane->panel = 'middle';
    $pane->type = 'ting_object';
    $pane->subtype = 'ting_object';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => 'argument_ting_object_id_17',
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = '';
    $pane->uuid = 'eda37090-d344-4baa-8c21-78573268da3d';
    $display->content['new-eda37090-d344-4baa-8c21-78573268da3d'] = $pane;
    $display->panels['middle'][0] = 'new-eda37090-d344-4baa-8c21-78573268da3d';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['ting_object__ereolen-ting-object'] = $handler;

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'user_edit_panel_context_3';
  $handler->task = 'user_edit';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = -100;
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
      'override_title' => 1,
      'override_title_text' => '',
      'path' => '',
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
  $handler->weight = -100;
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
      'form_build_id' => 'form-HqKDYeifXl62yzInE4LkOmWdpJG26hwOx5nzcDMntxY',
      'form_token' => 'LhXHXSx98EKVaWoeFWTVKu1q_fiBdnvk7uDz77Td4Zg',
      'form_id' => 'ding_reservation_reservations_content_type_edit_form',
      'override_title' => 0,
      'override_title_text' => 'Redeemable reservations',
      'reservation_empty_text' => 'There are no reservations ready.',
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
