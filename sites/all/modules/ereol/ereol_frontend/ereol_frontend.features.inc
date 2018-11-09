<?php
/**
 * @file
 * ereol_frontend.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ereol_frontend_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function ereol_frontend_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function ereol_frontend_image_default_styles() {
  $styles = array();

  // Exported image style: ereol_cover_base.
  $styles['ereol_cover_base'] = array(
    'label' => 'eReol cover base',
    'effects' => array(
      1 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 260,
          'height' => 375,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_default_search_api_index().
 */
function ereol_frontend_default_search_api_index() {
  $items = array();
  $items['ereol_index'] = entity_import('search_api_index', '{
    "name" : "eReol index",
    "machine_name" : "ereol_index",
    "description" : null,
    "server" : "localhost_db",
    "item_type" : "node",
    "options" : {
      "datasource" : { "bundles" : [ "article" ] },
      "index_directly" : 0,
      "cron_limit" : "50",
      "fields" : {
        "body:value" : { "type" : "text" },
        "nid" : { "type" : "integer" },
        "search_api_language" : { "type" : "string" },
        "title" : { "type" : "text", "boost" : "2.0" },
        "type" : { "type" : "string" }
      },
      "data_alter_callbacks" : {
        "ding_frontend_published_filter" : { "status" : 0, "weight" : "-10", "settings" : [] },
        "search_api_alter_bundle_filter" : {
          "status" : 0,
          "weight" : "-10",
          "settings" : { "default" : "1", "bundles" : [] }
        },
        "ding_frontend_bundle_filter" : {
          "status" : 0,
          "weight" : "-10",
          "settings" : { "default" : "1", "bundles" : [] }
        },
        "ding_frontend_role_filter" : {
          "status" : 0,
          "weight" : "-10",
          "settings" : { "default" : "1", "match_type" : "partial", "roles" : [] }
        },
        "search_api_alter_node_access" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_language_control" : {
          "status" : 0,
          "weight" : "0",
          "settings" : { "lang_field" : "", "languages" : [] }
        },
        "search_api_alter_node_status" : { "status" : 1, "weight" : "0", "settings" : [] },
        "search_api_alter_add_hierarchy" : { "status" : 0, "weight" : "0", "settings" : { "fields" : [] } },
        "search_api_alter_add_url" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_metatag_alter_callback" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_add_aggregation" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_add_viewed_entity" : { "status" : 0, "weight" : "0", "settings" : { "mode" : "full" } }
      },
      "processors" : {
        "search_api_case_ignore" : {
          "status" : 0,
          "weight" : "0",
          "settings" : { "fields" : { "title" : true, "body:value" : true } }
        },
        "search_api_html_filter" : {
          "status" : 0,
          "weight" : "10",
          "settings" : {
            "fields" : { "title" : true, "body:value" : true },
            "title" : 0,
            "alt" : 1,
            "tags" : "h1 = 5\\r\\nh2 = 3\\r\\nh3 = 2\\r\\nstrong = 2\\r\\nb = 2\\r\\nem = 1.5\\r\\nu = 1.5"
          }
        },
        "search_api_transliteration" : {
          "status" : 0,
          "weight" : "15",
          "settings" : { "fields" : { "title" : true, "body:value" : true } }
        },
        "search_api_tokenizer" : {
          "status" : 0,
          "weight" : "20",
          "settings" : {
            "fields" : { "title" : true, "body:value" : true },
            "spaces" : "[^[:alnum:]]",
            "ignorable" : "[\\u0027]"
          }
        },
        "search_api_stopwords" : {
          "status" : 0,
          "weight" : "30",
          "settings" : {
            "fields" : { "title" : true, "body:value" : true },
            "file" : "",
            "stopwords" : "but\\r\\ndid\\r\\nthe this that those\\r\\netc"
          }
        },
        "search_api_highlighting" : {
          "status" : 0,
          "weight" : "35",
          "settings" : {
            "prefix" : "\\u003Cstrong\\u003E",
            "suffix" : "\\u003C\\/strong\\u003E",
            "excerpt" : 1,
            "excerpt_length" : "256",
            "exclude_fields" : [],
            "highlight" : "always"
          }
        }
      }
    },
    "enabled" : "1",
    "read_only" : "0"
  }');
  return $items;
}

/**
 * Implements hook_default_search_api_server().
 */
function ereol_frontend_default_search_api_server() {
  $items = array();
  $items['localhost_db'] = entity_import('search_api_server', '{
    "name" : "Localhost DB",
    "machine_name" : "localhost_db",
    "description" : "",
    "class" : "search_api_db_service",
    "options" : {
      "database" : "default:default",
      "min_chars" : "1",
      "partial_matches" : 1,
      "indexes" : {
        "ereol_index" : {
          "nid" : {
            "table" : "search_api_db_ereol_index",
            "column" : "nid",
            "type" : "integer",
            "boost" : "1.0"
          },
          "type" : {
            "table" : "search_api_db_ereol_index",
            "column" : "type",
            "type" : "string",
            "boost" : "1.0"
          },
          "title" : {
            "table" : "search_api_db_ereol_index_text",
            "type" : "text",
            "boost" : "2.0"
          },
          "search_api_language" : {
            "table" : "search_api_db_ereol_index",
            "column" : "search_api_language",
            "type" : "string",
            "boost" : "1.0"
          },
          "body:value" : {
            "table" : "search_api_db_ereol_index_text",
            "type" : "text",
            "boost" : "1.0"
          }
        },
        "default_multiple_index" : {
          "item_id" : {
            "table" : "search_api_db_default_multiple_index",
            "column" : "item_id_1",
            "type" : "string",
            "boost" : "1.0"
          },
          "item_type" : {
            "table" : "search_api_db_default_multiple_index",
            "column" : "item_type",
            "type" : "string",
            "boost" : "1.0"
          },
          "item_bundle" : {
            "table" : "search_api_db_default_multiple_index",
            "column" : "item_bundle",
            "type" : "string",
            "boost" : "1.0"
          },
          "node" : {
            "table" : "search_api_db_default_multiple_index",
            "column" : "node",
            "type" : "integer",
            "boost" : "1.0"
          },
          "user" : {
            "table" : "search_api_db_default_multiple_index",
            "column" : "user",
            "type" : "integer",
            "boost" : "1.0"
          },
          "search_api_language" : {
            "table" : "search_api_db_default_multiple_index",
            "column" : "search_api_language",
            "type" : "string",
            "boost" : "1.0"
          },
          "node:nid" : {
            "table" : "search_api_db_default_multiple_index",
            "column" : "node_nid",
            "type" : "integer",
            "boost" : "1.0"
          },
          "node:title" : {
            "table" : "search_api_db_default_multiple_index_text",
            "type" : "text",
            "boost" : "2.0"
          },
          "node:created" : {
            "table" : "search_api_db_default_multiple_index",
            "column" : "node_created",
            "type" : "date",
            "boost" : "1.0"
          },
          "node:changed" : {
            "table" : "search_api_db_default_multiple_index",
            "column" : "node_changed",
            "type" : "date",
            "boost" : "1.0"
          },
          "node:author" : {
            "table" : "search_api_db_default_multiple_index",
            "column" : "node_author",
            "type" : "integer",
            "boost" : "1.0"
          },
          "node:field_ding_news_category" : {
            "table" : "search_api_db_default_multiple_index",
            "column" : "node_field_ding_news_category",
            "type" : "integer",
            "boost" : "1.0"
          },
          "node:field_ding_news_lead" : {
            "table" : "search_api_db_default_multiple_index_text",
            "type" : "text",
            "boost" : "1.0"
          },
          "node:field_ding_news_tags" : {
            "table" : "search_api_db_default_multiple_index_node_field_ding_news_tags",
            "column" : "value",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "node:field_ding_page_lead" : {
            "table" : "search_api_db_default_multiple_index_text",
            "type" : "text",
            "boost" : "1.0"
          },
          "node:field_ding_page_tags" : {
            "table" : "search_api_db_default_multiple_index_node_field_ding_page_tags",
            "column" : "value",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "node:field_ding_event_category" : {
            "table" : "search_api_db_default_multiple_index",
            "column" : "node_field_ding_event_category",
            "type" : "integer",
            "boost" : "1.0"
          },
          "node:field_ding_event_lead" : {
            "table" : "search_api_db_default_multiple_index_text",
            "type" : "text",
            "boost" : "1.0"
          },
          "node:field_ding_event_tags" : {
            "table" : "search_api_db_default_multiple_index_node_field_ding_event_tag",
            "column" : "value",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "node:field_ding_event_target" : {
            "table" : "search_api_db_default_multiple_index",
            "column" : "node_field_ding_event_target",
            "type" : "integer",
            "boost" : "1.0"
          },
          "node:field_ding_library_fax_number" : {
            "table" : "search_api_db_default_multiple_index_text",
            "type" : "text",
            "boost" : "1.0"
          },
          "node:field_ding_library_lead" : {
            "table" : "search_api_db_default_multiple_index_text",
            "type" : "text",
            "boost" : "1.0"
          },
          "node:field_ding_library_mail" : {
            "table" : "search_api_db_default_multiple_index_text",
            "type" : "text",
            "boost" : "1.0"
          },
          "node:field_ding_library_phone_number" : {
            "table" : "search_api_db_default_multiple_index_text",
            "type" : "text",
            "boost" : "1.0"
          },
          "node:field_ding_group_lead" : {
            "table" : "search_api_db_default_multiple_index_text",
            "type" : "text",
            "boost" : "1.0"
          },
          "user:uid" : {
            "table" : "search_api_db_default_multiple_index",
            "column" : "user_uid",
            "type" : "integer",
            "boost" : "1.0"
          },
          "user:roles" : {
            "table" : "search_api_db_default_multiple_index_user_roles",
            "column" : "value",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "user:status" : {
            "table" : "search_api_db_default_multiple_index",
            "column" : "user_status",
            "type" : "integer",
            "boost" : "1.0"
          },
          "user:profile_ding_staff_profile" : {
            "table" : "search_api_db_default_multiple_index",
            "column" : "user_profile_ding_staff_profile",
            "type" : "integer",
            "boost" : "1.0"
          },
          "user:relation_ting_reference_ting_object" : {
            "table" : "search_api_db_default_multiple_index_user_relation_ting_refere",
            "column" : "value",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "node:type" : {
            "table" : "search_api_db_default_multiple_index",
            "column" : "node_type",
            "type" : "string",
            "boost" : "1.0"
          },
          "node:url" : {
            "table" : "search_api_db_default_multiple_index",
            "column" : "node_url",
            "type" : "uri",
            "boost" : "1.0"
          },
          "user:profile_ding_staff_profile:field_ding_staff_department" : {
            "table" : "search_api_db_default_multiple_index_user_profile_ding_staff_p",
            "column" : "value",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "user:profile_ding_staff_profile:field_ding_staff_email" : {
            "table" : "search_api_db_default_multiple_index_text",
            "type" : "text",
            "boost" : "1.0"
          },
          "user:profile_ding_staff_profile:field_ding_staff_forename" : {
            "table" : "search_api_db_default_multiple_index_text",
            "type" : "text",
            "boost" : "2.0"
          },
          "user:profile_ding_staff_profile:field_ding_staff_phone" : {
            "table" : "search_api_db_default_multiple_index_text",
            "type" : "text",
            "boost" : "1.0"
          },
          "user:profile_ding_staff_profile:field_ding_staff_position" : {
            "table" : "search_api_db_default_multiple_index_text",
            "type" : "text",
            "boost" : "1.0"
          },
          "user:profile_ding_staff_profile:field_ding_staff_surname" : {
            "table" : "search_api_db_default_multiple_index_text",
            "type" : "text",
            "boost" : "2.0"
          },
          "user:profile_ding_staff_profile:field_ding_staff_work_areas" : {
            "table" : "search_api_db_default_multiple_index_text",
            "type" : "text",
            "boost" : "1.0"
          }
        }
      }
    },
    "enabled" : "1"
  }');
  return $items;
}
