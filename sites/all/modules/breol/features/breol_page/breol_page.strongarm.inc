<?php
/**
 * @file
 * breol_page.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function breol_page_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_breol_page';
  $strongarm->value = 0;
  $export['comment_anonymous_breol_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_breol_page';
  $strongarm->value = '0';
  $export['comment_breol_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_breol_page';
  $strongarm->value = 1;
  $export['comment_default_mode_breol_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_breol_page';
  $strongarm->value = '50';
  $export['comment_default_per_page_breol_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_breol_page';
  $strongarm->value = 1;
  $export['comment_form_location_breol_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_breol_page';
  $strongarm->value = '1';
  $export['comment_preview_breol_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_breol_page';
  $strongarm->value = 1;
  $export['comment_subject_field_breol_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__breol_page';
  $strongarm->value = array(
    'view_modes' => array(
      'teaser' => array(
        'custom_settings' => TRUE,
      ),
      'teaser_small' => array(
        'custom_settings' => TRUE,
      ),
      'teaser_medium' => array(
        'custom_settings' => TRUE,
      ),
      'full' => array(
        'custom_settings' => FALSE,
      ),
      'rss' => array(
        'custom_settings' => FALSE,
      ),
      'search_index' => array(
        'custom_settings' => FALSE,
      ),
      'search_result' => array(
        'custom_settings' => FALSE,
      ),
      'token' => array(
        'custom_settings' => FALSE,
      ),
      'workflow_tab' => array(
        'custom_settings' => FALSE,
      ),
    ),
    'extra_fields' => array(
      'form' => array(
        'title' => array(
          'weight' => '0',
        ),
        'path' => array(
          'weight' => '3',
        ),
        'redirect' => array(
          'weight' => '2',
        ),
      ),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_node__breol_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_breol_page';
  $strongarm->value = '0';
  $export['language_content_type_breol_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_breol_page';
  $strongarm->value = array(
    0 => 'main-menu',
    1 => 'menu-footer-menu-1',
    2 => 'menu-footer-menu-2',
    3 => 'menu-footer-menu-3',
    4 => 'menu-footer-menu-4',
  );
  $export['menu_options_breol_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_breol_page';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_breol_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_breol_page';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_breol_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_breol_page';
  $strongarm->value = '1';
  $export['node_preview_breol_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_breol_page';
  $strongarm->value = 0;
  $export['node_submitted_breol_page'] = $strongarm;

  return $export;
}
