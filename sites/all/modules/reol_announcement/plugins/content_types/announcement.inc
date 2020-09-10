<?php

/**
 * @file
 * CTools Content Type for displaying announcements.
 */

$plugin = array(
  'title' => t('Display annoucement'),
  'description' => t('Display the site announcement.'),
  'category' => 'ereolen.dk',
  'single' => TRUE,
  'content type' => 'announcement',
  'render callback' => 'announcement_content_type_render',
  'hook theme' => 'announcement_content_type_theme',
  'edit form' => 'announcement_content_type_edit_form',
);

/**
 * Render the content type.
 */
function announcement_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();

  $state = variable_get('reol_announcement_state', REOL_ANNOUNCEMENT_DISABLED);

  switch ($state) {
    case REOL_ANNOUNCEMENT_DISABLED:
      return new StdClass();

    case REOL_ANNOUNCEMENT_ENABLED:
      $class = "info";
      break;

    case REOL_ANNOUNCEMENT_WARNING:
      $class = "warning";
      break;
  }

  $text = variable_get('reol_announcement_announcement', array('value' => ''));
  $vars = array(
    'class' => $class,
    'announcement' => $text['value'],
  );

  $block->content = theme('announcement', $vars);

  return $block;
}

/**
 * Admin settings form.
 */
function announcement_content_type_edit_form($form, &$form_state) {
  return $form;
}

/**
 * Ctools block theme function.
 */
function announcement_content_type_theme(&$theme, $plugin) {
  $theme['announcement'] = array(
    'variables' => array('vars' => NULL),
    'path' => $plugin['path'],
    'template' => 'announcement',
  );
}
