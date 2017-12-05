<?php

/**
 * @file
 * Login/profile link.
 */

$plugin = array(
  'title' => t('eReolen profile link'),
  'description' => t('Link to login/profile, with JS behavior and notification count.'),
  'category' => 'ereolen.dk',
  'single' => TRUE,
  'content type' => 'reol_profile_link',
  'render callback' => 'reol_frontend_reol_profile_link_content_type_render',
  'edit form' => 'reol_frontend_reol_profile_link_content_type_edit_form',
);

/**
 * Render this content type.
 */
function reol_frontend_reol_profile_link_content_type_render($subtype, $conf, $panel_args, $context) {
  global $user;
  $block = new stdClass();

  $variables = array(
    'content' => '',
    'count' => NULL,
  );

  $block->content = '';
  if (!user_is_logged_in()) {
    $options = array(
      'attributes' => array(
        'class' => array(
          'js-login-link',
          'user-login__link',
        ),
      ),
    );
    $variables['content'] = l(t('Login'), 'login/nojs', $options);
  }
  else {
    $options = array(
      'attributes' => array(
        'class' => array(
          'user-login__profile-link',
        ),
      ),
    );
    $variables['content'] = l(t('My page'), 'user', $options);
    if (ding_user_is_provider_user($user)) {
      $count = 0;
      if (module_exists('ding_message')) {
        $count = ding_message_get_message_count();
      }
      $count += count(ding_provider_invoke('reservation', 'list', $user, DING_RESERVATION_READY));
      $count += count(ding_provider_invoke('debt', 'list', $user));
      $variables['count'] = $count;
    }
  }

  $block->content = theme('reol_frontend_reol_login', $variables);

  return $block;
}

/**
 * Content type settings form.
 */
function reol_frontend_reol_profile_link_content_type_edit_form($form, &$form_state) {
  return $form;
}
