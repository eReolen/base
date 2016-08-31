<?php

/**
 * @file
 * Preprocess and Process Functions.
 */

/**
 * Implements hook_form_alter().
 */
function brin_form_alter(&$form, &$form_state, $form_id) {
  switch ($form_id) {
    case 'search_block_form':
      // Undo the un-hiding ddbasic does.
      $form['search_block_form']['#title_display'] = 'invisible';

      // Remove the standard search icon.
      unset($form['search_block_form']['#field_prefix']);
      break;
  }
}

/**
 * Implements hook_css_alter().
 */
function brin_css_alter(&$css) {
  // Fix tipsy to use the same media for its CSS as all the rest, so advagg will
  // be able to aggregate it all together.
  $tipsy = drupal_get_path('module', 'tipsy') . '/stylesheets/tipsy.css';
  if (isset($css[$tipsy])) {
    $css[$tipsy]['media'] = 'all';
  }
}

/**
 * Implements hook_js_alter().
 */
function brin_js_alter(&$javascript) {
  // Remove minified version of scripts we have overridden.
  $ddbasic = drupal_get_path('theme', 'ddbasic');
  unset($javascript[$ddbasic . '/scripts/ddbasic.topbar.menu.min.js']);
  unset($javascript[$ddbasic . '/scripts/ddbasic.search.min.js']);
}

/**
 * Implements hook_preprocess_node().
 */
function brin_preprocess_node(&$variables, $hook) {
  // Add tpl suggestions for node view modes on node type.
  if (isset($variables['view_mode'])) {
    $variables['theme_hook_suggestions'][] = 'node__' . $variables['node']->type . '__view_mode__' . $variables['view_mode'];
  }

  $node = $variables['node'];
  if (($node->type == 'article' || $node->type == 'author_portrait' || $node->type == 'video') && ($variables['view_mode'] == 'teaser' || $variables['view_mode'] == 'search_result')) {
    // Add type icon.
    $node_wrapper = entity_metadata_wrapper('node', $node);
    $type = $node_wrapper->field_reol_entity_type->value();
    if ($type) {
      // We default to quota icons when we really can't tell.
      $variables['classes_array'] = array_merge($variables['classes_array'],
                                    _brin_type_icon_classes($type, TRUE));
    }
  }
}

/**
 * Implements hook_ting_view_alter().
 *
 * Fix all fieldgroups to be open.
 */
function brin_ting_view_alter(&$build) {
  foreach ($build['#groups'] as $group) {
    if ($group->format_settings['formatter'] == 'collapsed') {
      $group->format_settings['formatter'] = 'open';
    }
  }
}

/**
 * Implements hook_preprocess_ting_object().
 */
function brin_process_ting_object(&$variables) {
  // Remove the type prefix from the title of the first material of
  // the collection.
  if (!empty($variables['content']['ting_primary_object'][0]['ting_title'][0]['title']['#prefix'])) {
    unset($variables['content']['ting_primary_object'][0]['ting_title'][0]['title']['#prefix']);
  }

  if ($variables['object'] instanceof TingCollection) {
    // Move the availability field into the primary ting object
    // render array to allow it to be printed as part of the object
    // template. It's further processed in the else statement.
    if (isset($variables['content']['ting_collection_types'])) {
      $variables['content']['ting_primary_object'][0]['ting_collection_types'] = $variables['content']['ting_collection_types'];
      unset($variables['content']['ting_collection_types']);
    }
  }
  else {
    // Move the availability field from above into the fieldgroup
    // wrapper, now that fieldgroup has processed it.
    if (isset($variables['content']['ting_collection_types']) && isset($variables['content']['group_ting_right_col_search'])) {

      $variables['content']['group_ting_right_col_search']['ting_collection_types'] = $variables['content']['ting_collection_types'];
      $variables['content']['group_ting_right_col_search']['ting_collection_types']['#weight'] = 100;
      unset($variables['content']['ting_collection_types']);
    }
  }
}

/**
 * Implements theme_menu_tree().
 */
function brin_menu_tree__menu_block__main_menu($vars) {
  return '<ul class="main-menu">' . $vars['tree'] . '</ul>';
}

/**
 * Implements theme_faq_page().
 */
function brin_faq_page($variables) {
  $content = $variables['content'];
  $answers = $variables['answers'];
  $description = $variables['description'];
  $output = '<div class="faq-content"><div class="faq">';
  if (!empty($description)) {
    $output .= '<div class="faq-description">' . $description . "</div>\n";
  }
  if (variable_get('faq_show_expand_all', FALSE)) {
    $output .= '<div id="faq-expand-all">';
    $output .= '<a class="faq-expand-all-link" href="#faq-expand-all-link">[' . t('expand all') . ']</a>';
    $output .= '<a class="faq-collapse-all-link" href="#faq-collapse-all-link">[' . t('collapse all') . ']</a>';
    $output .= "</div>\n";
  }

  $output .= '<div class="faq-questions">' . $content . '</div>';
  $output .= '<div class="faq-answers">' . $answers . "</div></div></div>\n";
  return $output;
}

/**
 * Returns HTML for a textfield form element.
 *
 * Basically theme_textfield with the size attribute removed.
 */
function brin_textfield($variables) {
  $element = $variables['element'];
  $element['#attributes']['type'] = 'text';
  element_set_attributes($element, array('id', 'name', 'value', 'maxlength'));
  _form_set_class($element, array('form-text'));

  $extra = '';
  if ($element['#autocomplete_path'] && drupal_valid_path($element['#autocomplete_path'])) {
    drupal_add_library('system', 'drupal.autocomplete');
    $element['#attributes']['class'][] = 'form-autocomplete';

    $attributes = array();
    $attributes['type'] = 'hidden';
    $attributes['id'] = $element['#attributes']['id'] . '-autocomplete';
    $attributes['value'] = url($element['#autocomplete_path'], array('absolute' => TRUE));
    $attributes['disabled'] = 'disabled';
    $attributes['class'][] = 'autocomplete';
    $extra = '<input' . drupal_attributes($attributes) . ' />';
  }

  $output = '<input' . drupal_attributes($element['#attributes']) . ' />';

  return $output . $extra;
}

/**
 * Theme function to render an webform email component.
 *
 * Basically theme_webform_email with the size attribute removed.
 */
function brin_webform_email($variables) {
  $element = $variables['element'];

  // This IF statement is mostly in place to allow our tests to set type="text"
  // because SimpleTest does not support type="email".
  if (!isset($element['#attributes']['type'])) {
    $element['#attributes']['type'] = 'email';
  }

  // Convert properties to attributes on the element if set.
  foreach (array('id', 'name', 'value') as $property) {
    if (isset($element['#' . $property]) && $element['#' . $property] !== '') {
      $element['#attributes'][$property] = $element['#' . $property];
    }
  }
  _form_set_class($element, array('form-text', 'form-email'));

  return '<input' . drupal_attributes($element['#attributes']) . ' />';
}

/**
 * Theme menu links.
 *
 * Add use ajax to login links.
 */
function brin_menu_link($vars) {
  $element = $vars['element'];

  // Render any sub-links/menus.
  $sub_menu = '';
  if ($element['#below']) {
    $sub_menu = drupal_render($element['#below']);
  }

  if (!is_array($element['#localized_options']['attributes']['class'])) {
    $element['#localized_options']['attributes']['class'] = array();
  }
  // Add default class to a tag.
  $element['#localized_options']['attributes']['class'][] = 'menu-item';

  if (isset($element['#original_link'])) {
    // If this element uses ajax, add class and load ajax.
    if (isset($element['#original_link']['delivery_callback']) && $element['#original_link']['delivery_callback'] == "ajax_deliver") {
      drupal_add_library('system', 'drupal.ajax');
      $element['#localized_options']['attributes']['class'][] = 'use-ajax';
    }
  }

  // Filter classes.
  $element['#attributes']['class'] = ddbasic_remove_default_link_classes($element['#attributes']['class']);

  // Make sure text string is treated as html by l function.
  $element['#localized_options']['html'] = TRUE;

  $link = l('<span>' . $element['#title'] . '</span>', $element['#href'], $element['#localized_options']);

  return '<li' . drupal_attributes($element['#attributes']) . '>' . $link . $sub_menu . "</li>\n";
}

/**
 * Preprocess HTML.
 *
 * Add ajax for all pages. Add icons and meta tags.
 */
function brin_preprocess_html(&$variables) {
  drupal_add_library('system', 'drupal.ajax');

  $tags = array(
    // Add tags for mobile devices.
    'viewport' => array(
      'type' => 'meta',
      'attributes' => array(
        'name' => 'viewport',
        'content' => 'width=device-width,initial-scale=1.0,maximum-scale=1.0',
      ),
    ),

    // iOS.
    'webapp' => array(
      'type' => 'meta',
      'attributes' => array(
        'name' => 'apple-mobile-web-app-capable',
        'content' => 'yes',
      ),
    ),

    // Microsoft.
    'ms_name' => array(
      'type' => 'meta',
      'attributes' => array(
        'name' => 'application-name',
        'content' => variable_get('site_name', ''),
      ),
    ),
    'ms_tile_color' => array(
      'type' => 'meta',
      'attributes' => array(
        'name' => 'msapplication-TileColor',
        'content' => '#FFFFFF',
      ),
    ),
    'ms_tile_image' => array(
      'type' => 'meta',
      'attributes' => array(
        'name' => 'msapplication-TileImage',
        'content' => '/' . path_to_theme() . '/images/favicon/mstile-square144x144.png',
      ),
    ),
  );

  // Apple iTunes app id.
  if ($app_id = variable_get('reol_base_itunes_app_id', FALSE)) {
    $tags['apple-itunes-app'] = array(
      'type' => 'meta',
      'attributes' => array(
        'name' => 'apple-itunes-app',
        'content' => 'app-id=' . $app_id,
      ),
    );
  }

  // Apple icons.
  $apple_icons = array(
    '57x57',
    '114x114',
    '72x72',
    '144x144',
    '60x60',
    '120x120',
    '76x76',
    '152x152',
  );
  foreach ($apple_icons as $size) {
    $tags['apple_icon_' . $size] = array(
      'type' => 'link',
      'attributes' => array(
        'rel' => 'apple-touch-icon-precomposed',
        'href' => '/' . path_to_theme() . '/images/favicon/apple-touch-icon-' . $size . '.png',
        'sizes' => $size,
      ),
    );
  }

  // Favicon.
  $favicons = array(
    '196x196',
    '96x96',
    '32x32',
    '16x16',
    '128x128',
  );
  foreach ($favicons as $size) {
    $tags['favicon_' . $size] = array(
      'type' => 'link',
      'attributes' => array(
        'rel' => 'icon',
        'href' => '/' . path_to_theme() . '/images/favicon/favicon-' . $size . '.png',
        'sizes' => $size,
      ),

    );
  }

  // Microsoft icons.
  $favicons = array(
    'square70x70',
    'square150x150',
    'wide310x150',
    'square310x310',
  );
  foreach ($favicons as $size) {
    $tags['msfavicon_' . $size] = array(
      'type' => 'meta',
      'attributes' => array(
        'name' => 'msapplication-' . $size . 'logo',
        'content' => '/' . path_to_theme() . '/images/favicon/mstile-' . $size . '.png',
      ),
    );
  }

  foreach ($tags as $name => $tag) {
    $html_tag = array(
      '#type' => 'html_tag',
      '#tag' => $tag['type'],
      '#attributes' => $tag['attributes'],
    );
    drupal_add_html_head($html_tag, $name);
  }
}

/**
 * Preprocess single_review.
 *
 * Adds type icon.
 */
function brin_preprocess_single_review(&$variables) {
  $ting_entity = $variables['#object'];
  if ($ting_entity && $ting_entity->reply) {
    $classes = _brin_type_icon_classes(reol_base_get_type_name($ting_entity->type), $ting_entity->reply->on_quota);
    $variables['classes_array'] = array_merge($variables['classes_array'], $classes);
  }
}

/**
 * Implements hook_ting_collection_view_alter().
 *
 * Suppress the type icon on the material in the ting_primary_object when the
 * collection contains more than one material. This removes the type-icon in
 * search results where the cover represents more than one material (likely of
 * different types).
 */
function brin_ting_collection_view_alter(&$build) {
  if (isset($build['ting_primary_object'])) {
    foreach (element_children($build['ting_primary_object']) as $key) {
      $collection = $build['ting_primary_object']['#object'];
      if (count($collection->entities) > 1) {
        if (isset($build['ting_primary_object'][$key]['ting_cover'])) {
          $build['ting_primary_object'][$key]['ting_cover'][0]['#suppress_type_icon'] = TRUE;
        }
      }
    }
  }
}

/**
 * Implements hook_preprocess_preprocess_material_item().
 *
 * @todo check if this is still valid, or whether
 *   brin_ting_collection_view_alter() ensures there's a type icon.
 */
function brin_preprocess_material_item(&$variables) {
  $element = $variables['element'];
  // TODO Can we rely on this?
  $ding_entity_id = $element['#cover']['#object']->ding_entity_id;
  $ting_entity = ding_entity_load($ding_entity_id);

  $add_classes = _brin_type_icon_classes(reol_base_get_type_name($ting_entity->type), $ting_entity->reply->on_quota);
  $variables['classes_array'] = array_merge($variables['classes_array'], $add_classes);
}

/**
 * Implements hook_preprocess_ting_object_cover().
 *
 * Adds type icon to ting object covers.
 */
function brin_preprocess_ting_object_cover(&$variables) {
  if (!isset($variables['elements']['#suppress_type_icon']) ||
    !$variables['elements']['#suppress_type_icon']) {
    $ting_entity = $variables['object'];
    if ($ting_entity && $ting_entity->reply) {
      $add_classes = _brin_type_icon_classes(reol_base_get_type_name($ting_entity->type), $ting_entity->reply->on_quota);
      $variables['classes'] = array_merge($variables['classes'], $add_classes);
    }
  }
}

/**
 * Return classes for type icon.
 *
 * @return array
 *   Classes as array.
 */
function _brin_type_icon_classes($type, $quota = NULL) {
  $classes = array(
    'type-icon',
    'type-icon-' . $type,
  );
  if (is_bool($quota)) {
    $classes[] = 'type-icon-' . ($quota ? 'quota' : 'noquota');
  }
  return $classes;
}
