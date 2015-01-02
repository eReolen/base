<?php
/**
 * @file
 * CTools Content Type for showing latest from data well.
 */

$plugin = array(
  'title' => t('Show latest titles.'),
  'description' => t('Show a list of the latest titles from the data well.'),
  'category' => 'ereolen.dk',
  'single' => TRUE,
  'content type' => 'latest',
  'render callback' => 'latest_content_type_render',
  'hook theme' => 'latest_content_type_theme',
  'edit form' => 'latest_content_type_edit_form',
  'all contexts' => TRUE,
);

/**
 * Render the content type.
 */
function latest_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();
  $type = FALSE;
  if (isset($conf['type'])) {
    $type = ctools_context_keyword_substitute($conf['type'], array(), $context);
  }

  // There might be no latest.
  if ($ting_entities = reol_latest_get_latest_count($conf['count'] ? $conf['count'] : 5, !empty($type) ? $type : FALSE)) {
    $ting_rendered = array();
    foreach ($ting_entities as $ting_entity) {
      $ting_rendered[] = array(
        'link' => 'ting/object/' . $ting_entity->id,
        'view' => ting_object_view($ting_entity, 'latest'),
      );
    }

    $block->content = theme('latest', array(
      'ting_objects' => $ting_rendered,
    ));
    $types = reol_base_get_type();
    $type = $types[$type];
    $block->title = t('Latest @type_plural', array('@type_plural' => $type['title_plural']));
  }

  return $block;
}

/**
 * Admin settings form.
 */
function latest_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];

  $form['count'] = array(
    '#type' => 'textfield',
    '#title' => t('Count'),
    '#description' => t('Number of items to show.'),
    '#default_value' => isset($conf['count']) ? $conf['count'] : '5',
  );

  $form['type'] = array(
    '#type' => 'textfield',
    '#title' => t('Type'),
    '#description' => t('Select which type to show latest for.'),
    '#default_value' => isset($conf['type']) ? $conf['type'] : '',
  );

  return $form;
}

/**
 * Submit handler for content type settings form.
 */
function latest_content_type_edit_form_submit($form, &$form_state) {
  $form_state['conf']['type'] = $form_state['values']['type'];
  $form_state['conf']['count'] = $form_state['values']['count'];
}

/**
 * Ctools block theme function.
 */
function latest_content_type_theme(&$theme, $plugin) {
  $theme['latest'] = array(
    'variables' => array('vars' => NULL),
    'path' => $plugin['path'],
    'template' => 'latest',
  );
}
