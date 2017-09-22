<?php

/**
 * @file
 * Preprocess and Process Functions.
 */

/**
 * Implements THEME_panels_default_style_render_region().
 *
 * Remove panel seprator markup from panels.
 */
function orwell_panels_default_style_render_region($vars) {
  $output = '';
  $output .= implode('', $vars['panes']);
  return $output;
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function orwell_form_search_block_form_alter(&$form, &$form_state) {
  // HTML5 placeholder attribute.
  $form['search_block_form']['#attributes']['placeholder'] = t('Søg efter');
  $form['search_block_form']['#attributes']['class'][] = 'search-form__input--text';
  // Hide submit button.
  $form['actions']['#attributes']['class'][] = 'element-invisible';
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function orwell_form_user_login_block_alter(&$form, &$form_state) {
  // Hide links.
  $form['links']['#access'] = FALSE;
}

/**
 * Implements hook_preprocess_node().
 */
function orwell_preprocess_node(&$variables) {
  $node = $variables['node'];
  // Make author information available.
  $variables['author'] = user_load($node->uid);
  $variables['created_formatted'] = format_date($node->created, 'custom', 'd - m / y');

  if ($node->type === 'article' && ($variables['view_mode'] == 'teaser' || $variables['view_mode'] == 'search_result')) {
    $variables['covers'] = array();
    $entity_ids = array();
    // Sadly no entity_wrapper support in ting_reference, so we'll do it the
    // hard way.
    if (isset($node->field_ding_news_materials[LANGUAGE_NONE])) {
      foreach ($node->field_ding_news_materials[LANGUAGE_NONE] as $item) {
        if (isset($item['value']->endpoints[LANGUAGE_NONE][1])) {
          $entity_ids[] = $item['value']->endpoints[LANGUAGE_NONE][1]['entity_id'];
        }
      }
    }

    if ($entity_ids) {
      // Pick two randomly.
      shuffle($entity_ids);
      $entity_ids = array_slice($entity_ids, 0, 2);

      // Load the entities so we can get the well ID of them.
      $ding_entities = entity_load('ting_object', $entity_ids);
      $ids = array_map(function ($ding_entity) {
        return $ding_entity->getId();
      }, $ding_entities);

      $variables['covers'] = array_map(function ($file) {
        $variables = array(
          'style_name' => 'ereol_article_covers',
          'path' => $file,
        );
        return theme('image_style', $variables);
      }, ting_covers_get(array_values($ids)));
    }

    // Add template suggestion if teaser should use article_image
    // as background.
    if ($variables['is_image_teaser']) {
      $variables['theme_hook_suggestions'][] = 'node__article__view_mode__teaser__image';
    }
  }
}

/**
 * Implements hook_preprocess_panels_pane().
 */
function orwell_preprocess_panels_pane(&$variables) {
  if ($variables['pane']->type == 'node_content') {
    $variables['theme_hook_suggestions'][] = 'panels_pane__node_content__' . $variables['content']['#bundle'];
  }
}

/**
 * Template preprocessor for ting objects.
 */
function orwell_preprocess_ting_object(&$variables) {
  $variables['theme_hook_suggestions'][] = 'ting_object__' . $variables['elements']['#view_mode'];

  // Add font-awesome - used for ratings.
  $font_awesome = variable_get('ereol_font_awesome_path', '//netdna.bootstrapcdn.com/font-awesome/3.2.1/css/font-awesome.css');
  drupal_add_css($font_awesome, array('type' => 'external'));
}
