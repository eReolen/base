<?php
/**
 * @file
 * reol_help.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function reol_help_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'faq_answer_category_name';
  $strongarm->value = 0;
  $export['faq_answer_category_name'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'faq_answer_label';
  $strongarm->value = 'A:';
  $export['faq_answer_label'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'faq_back_to_top';
  $strongarm->value = '';
  $export['faq_back_to_top'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'faq_category_display';
  $strongarm->value = 'categories_inline';
  $export['faq_category_display'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'faq_category_hide_qa_accordion';
  $strongarm->value = 1;
  $export['faq_category_hide_qa_accordion'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'faq_category_listing';
  $strongarm->value = 'ul';
  $export['faq_category_listing'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'faq_count';
  $strongarm->value = 1;
  $export['faq_count'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'faq_default_sorting';
  $strongarm->value = 'DESC';
  $export['faq_default_sorting'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'faq_disable_node_links';
  $strongarm->value = 1;
  $export['faq_disable_node_links'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'faq_display';
  $strongarm->value = 'questions_top';
  $export['faq_display'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'faq_group_questions_top';
  $strongarm->value = 0;
  $export['faq_group_questions_top'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'faq_hide_child_terms';
  $strongarm->value = 1;
  $export['faq_hide_child_terms'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'faq_hide_qa_accordion';
  $strongarm->value = 0;
  $export['faq_hide_qa_accordion'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'faq_omit_vocabulary';
  $strongarm->value = array(
    1 => 0,
    7 => 0,
    3 => 0,
    4 => 0,
    8 => 0,
    5 => 0,
    6 => 0,
    2 => 0,
  );
  $export['faq_omit_vocabulary'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'faq_qa_mark';
  $strongarm->value = 0;
  $export['faq_qa_mark'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'faq_question_label';
  $strongarm->value = 'Q:';
  $export['faq_question_label'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'faq_question_length';
  $strongarm->value = 'short';
  $export['faq_question_length'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'faq_question_listing';
  $strongarm->value = 'ul';
  $export['faq_question_listing'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'faq_question_long_form';
  $strongarm->value = 0;
  $export['faq_question_long_form'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'faq_show_expand_all';
  $strongarm->value = 0;
  $export['faq_show_expand_all'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'faq_show_node_links';
  $strongarm->value = 0;
  $export['faq_show_node_links'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'faq_show_term_page_children';
  $strongarm->value = 0;
  $export['faq_show_term_page_children'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'faq_use_categories';
  $strongarm->value = 1;
  $export['faq_use_categories'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'faq_use_teaser';
  $strongarm->value = 0;
  $export['faq_use_teaser'] = $strongarm;

  return $export;
}
