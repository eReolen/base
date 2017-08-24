<?php

/**
 * @file
 * Notifications icon.
 */

$plugin = array(
  'title' => t('eReolen notifications'),
  'description' => t('Link to login/profile, with JS behaviur.'),
  'category' => 'ereolen.dk',
  'single' => TRUE,
  'content type' => 'reol_profile_link',
  'render callback' => 'reol_frontend_reol_notifications_content_type_render',
  'edit form' => 'reol_frontend_reol_notifications_content_type_edit_form',
);

/**
 * Render this content type.
 */
function reol_frontend_reol_notifications_content_type_render($subtype, $conf, $panel_args, $context) {
  global $user;
  $block = new stdClass();

  $block->content = ' ';
  if (ding_user_is_provider_user($user)) {
    $parameters = array(
      'uri' => url('user'),
      'messages' => 0,
    );

    if (module_exists('ding_message')) {
      $parameters['messages'] = ding_message_get_message_count();
    }
    $parameters['reservations'] = count(ding_provider_invoke('reservation', 'list', $user, DING_RESERVATION_READY));
    $parameters['debts'] = count(ding_provider_invoke('debt', 'list', $user));
    $parameters['total'] = $parameters['messages'] + $parameters['reservations'] + $parameters['debts'];

    $block->content .= theme('reol_frontend_reol_notifications', $parameters);
  }

  return $block;
}

/**
 * Content type settings form.
 */
function reol_frontend_reol_notifications_content_type_edit_form($form, &$form_state) {
  return $form;
}
