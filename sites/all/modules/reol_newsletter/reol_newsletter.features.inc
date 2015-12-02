<?php
/**
 * @file
 * reol_newsletter.features.inc
 */

/**
 * Implements hook_default_mailchimp_signup().
 */
function reol_newsletter_default_mailchimp_signup() {
  $items = array();
  $items['newsletter_signup'] = entity_import('mailchimp_signup', '{
    "name" : "newsletter_signup",
    "mc_lists" : { "4bc9190fe1" : "4bc9190fe1" },
    "mode" : "1",
    "title" : "Tilmeld dig eReolens nyhedsbrev",
    "settings" : {
      "path" : "",
      "submit_button" : "Tilmeld",
      "confirmation_message" : "Du er nu tilmeldt eReolens nyhedsbrev",
      "destination" : "",
      "mergefields" : {
        "EMAIL" : {
          "name" : "Email Address",
          "req" : true,
          "field_type" : "email",
          "public" : true,
          "show" : true,
          "order" : "1",
          "default" : "",
          "helptext" : "",
          "size" : "25",
          "tag" : "EMAIL",
          "id" : 0
        },
        "SIGNUP" : {
          "name" : "SIGNUP",
          "req" : false,
          "field_type" : "text",
          "public" : true,
          "show" : true,
          "order" : "4",
          "default" : "",
          "helptext" : "",
          "size" : "25",
          "tag" : "SIGNUP",
          "id" : 3
        }
      },
      "description" : "",
      "doublein" : 1,
      "send_welcome" : 0,
      "include_interest_groups" : 0
    }
  }');
  return $items;
}
