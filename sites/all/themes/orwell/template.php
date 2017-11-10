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
  $variables['bundle'] = $variables['elements']['#bundle'];

  $variables['theme_hook_suggestions'][] = 'ting_object__' . $variables['elements']['#view_mode'];

  // Add font-awesome - used for ratings.
  $font_awesome = variable_get('ereol_font_awesome_path', '//netdna.bootstrapcdn.com/font-awesome/3.2.1/css/font-awesome.css');
  drupal_add_css($font_awesome, array('type' => 'external'));

  // Add "also available" to material details.
  $variables['also_available'] = '';
  // Copied and adapted from ting_block_view().
  if ($variables['elements']['#view_mode'] == 'full') {
    if ($collection = ting_collection_load($variables['object']->id)) {
      $items = array();
      foreach ($collection->types as $k => $type) {
        if ($collection->types_count[$type] == 1) {
          $uri = entity_uri('ting_object', $collection);
          // Don't link to ourselves.
          if (isset($uri['options']['entity']->entities[$k]->ding_entity_id) &&
            $variables['object']->id == $uri['options']['entity']->entities[$k]->ding_entity_id) {
            continue;
          }
          $uri['path'] = urldecode(url('ting/object/' . $uri['options']['entity']->entities[$k]->ding_entity_id));
        }
        else {
          // This shouldn't happen on eReolen, but we're keeping this code
          // anyway.
          $uri = entity_uri('ting_collection', $collection);
          $uri['options']['fragment'] = $type;
          $uri['options']['attributes'] = array('class' => array('js-search-overlay'));
        }

        $items[] = l(ting_type_label($type), $uri['path'], $uri['options']);
      }

      // Only display if there are more than on item.
      if (count($items) > 1) {
        $variables['also_available'] = array(
          '#theme' => 'item_list',
          '#items' => $items,
        );

        // Add search overlay trigger.
        drupal_add_js(drupal_get_path('module', 'ting') . '/js/ting.js');
      }
    }
  }
}

/**
 * Preprocess ting_relations.
 */
function orwell_preprocess_ting_relation(&$vars) {
  if ($vars['relation']->getType() == 'dbcaddi:hasDescriptionFromPublisher') {
    // Replace abstract with full content of the relation.
    // I know, this is way too coupled, but it's what we have to work with.
    $path = drupal_get_path('module', 'ting_fulltext');
    include_once $path . '/includes/ting_fulltext.pages.inc';
    $fulltext = ting_fulltext_object_load($vars['relation']->object->getId());
    $build = array(
      'ting_fulltext' => array(
        '#theme' => 'ting_fulltext',
        '#fields' => ting_fulltext_parse($fulltext),
      ),
    );
    $vars['abstract'] = drupal_render($build);

    // Remove link to full text.
    unset($vars['fulltext_link']);

    // Title is ugly per default, fix it.
    $vars['title'] = t('Description from publisher');
  }
}

/**
 * Template preprocessor for entities.
 */
function orwell_preprocess_entity(&$variables) {
  if ($variables['entity_type'] == 'paragraphs_item') {
    if ($variables['paragraphs_item']->bundle() == 'linkbox') {
      $wrapper = $variables['paragraphs_item']->wrapper();
      $variables['classes_array'][] = 'linkbox';

      $color = $wrapper->field_link_color->value();
      if (isset($color['rgb'])) {
        $variables['attributes_array']['style'] = 'background-color: ' . $color['rgb'] . ';';
      }

      $variables['icons'] = '';
      $link = $wrapper->field_link->value();
      if (isset($link['url'])) {
        $variables['href'] = $link['url'];

        if (!preg_match('{^' . preg_quote($GLOBALS['base_url']) . '}', $link['url'])) {
          $variables['icons'] = theme('reol_overlay_icons', array('icons' => array('link')));
        }
      }
      if (isset($link['title'])) {
        $variables['title'] = check_plain($link['title']);
      }
    }
  }
}

/**
 * Process ding_carousel.
 */
function orwell_process_ding_carousel(&$variables) {
  // Add dots to carousels. We'll remove those we don't need in styling.
  $variables['slick_settings']['dots'] = TRUE;
}

/**
 * Theme menu links.
 *
 * We need a div around the submenu for theming purposes.
 */
function orwell_menu_link(array $variables) {
  $element = $variables['element'];
  $sub_menu = '';

  if ($element['#below']) {
    $sub_menu = '<div>' . drupal_render($element['#below']) . '</div>';
  }

  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}
