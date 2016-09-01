<?php
/**
 * @file
 * breol_search_frontend.panels_default.inc
 */

/**
 * Implements hook_default_panels_mini().
 */
function breol_search_frontend_default_panels_mini() {
  $export = array();

  $mini = new stdClass();
  $mini->disabled = FALSE; /* Edit this to true to make a default mini disabled initially */
  $mini->api_version = 1;
  $mini->name = 'search';
  $mini->category = '';
  $mini->admin_title = 'Search';
  $mini->admin_description = '';
  $mini->requiredcontexts = array(
    0 => array(
      'identifier' => 'Søgestreng',
      'keyword' => 'string',
      'name' => 'string',
      'optional' => 0,
      'id' => 1,
    ),
  );
  $mini->contexts = array();
  $mini->relationships = array();
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
  $display->title = 'Søgeresultater';
  $display->uuid = 'cbc1e091-c100-4f06-95df-18b7a5f23f4a';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-0bc392da-f395-4f44-9a99-308c43e9e7eb';
    $pane->panel = 'before_content';
    $pane->type = 'search_result_count';
    $pane->subtype = 'search_result_count';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => 'requiredcontext_string_1',
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
    $pane->uuid = '0bc392da-f395-4f44-9a99-308c43e9e7eb';
    $display->content['new-0bc392da-f395-4f44-9a99-308c43e9e7eb'] = $pane;
    $display->panels['before_content'][0] = 'new-0bc392da-f395-4f44-9a99-308c43e9e7eb';
    $pane = new stdClass();
    $pane->pid = 'new-cb9a255f-6f14-4ec8-bdd5-1647e70e5263';
    $pane->panel = 'before_content';
    $pane->type = 'search_result_count';
    $pane->subtype = 'search_result_count';
    $pane->shown = FALSE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => 'requiredcontext_string_1',
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
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = 'cb9a255f-6f14-4ec8-bdd5-1647e70e5263';
    $display->content['new-cb9a255f-6f14-4ec8-bdd5-1647e70e5263'] = $pane;
    $display->panels['before_content'][1] = 'new-cb9a255f-6f14-4ec8-bdd5-1647e70e5263';
    $pane = new stdClass();
    $pane->pid = 'new-6adb6cbf-1c54-4f35-a9a9-af44f36d742a';
    $pane->panel = 'before_content';
    $pane->type = 'search_per_page';
    $pane->subtype = 'search_per_page';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'select_type' => 'dropdown',
      'context' => 'requiredcontext_string_1',
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
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '6adb6cbf-1c54-4f35-a9a9-af44f36d742a';
    $display->content['new-6adb6cbf-1c54-4f35-a9a9-af44f36d742a'] = $pane;
    $display->panels['before_content'][2] = 'new-6adb6cbf-1c54-4f35-a9a9-af44f36d742a';
    $pane = new stdClass();
    $pane->pid = 'new-0d47494b-9958-4453-b84a-5f453644e712';
    $pane->panel = 'before_content';
    $pane->type = 'block';
    $pane->subtype = 'ting_search-sort_form';
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
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = '0d47494b-9958-4453-b84a-5f453644e712';
    $display->content['new-0d47494b-9958-4453-b84a-5f453644e712'] = $pane;
    $display->panels['before_content'][3] = 'new-0d47494b-9958-4453-b84a-5f453644e712';
    $pane = new stdClass();
    $pane->pid = 'new-d58f1165-b167-422c-90e4-ccb6aab4d858';
    $pane->panel = 'header';
    $pane->type = 'breol_facetbrowser';
    $pane->subtype = 'breol_facetbrowser';
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
    $pane->uuid = 'd58f1165-b167-422c-90e4-ccb6aab4d858';
    $display->content['new-d58f1165-b167-422c-90e4-ccb6aab4d858'] = $pane;
    $display->panels['header'][0] = 'new-d58f1165-b167-422c-90e4-ccb6aab4d858';
    $pane = new stdClass();
    $pane->pid = 'new-3dea43f8-9d6d-4606-ad4b-625063eef6af';
    $pane->panel = 'main_content';
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
      'context' => 'requiredcontext_string_1',
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
    $pane->uuid = '3dea43f8-9d6d-4606-ad4b-625063eef6af';
    $display->content['new-3dea43f8-9d6d-4606-ad4b-625063eef6af'] = $pane;
    $display->panels['main_content'][0] = 'new-3dea43f8-9d6d-4606-ad4b-625063eef6af';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-6adb6cbf-1c54-4f35-a9a9-af44f36d742a';
  $mini->display = $display;
  $export['search'] = $mini;

  return $export;
}
