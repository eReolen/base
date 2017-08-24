<?php

/**
 * @file
 * Login/profile link.
 */

$plugin = array(
  'title' => t('eReolen profile link'),
  'description' => t('Link to login/profile, with JS behaviur.'),
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

  $block->content = '';
  if (!user_is_logged_in()) {
    $block->content .= l(t('Login'), 'login/nojs', array('attributes' => array('class' => array('js-login-link'))));
  }
  elseif (ding_user_is_provider_user($user)) {
    $block->content .= l(t('My page'), 'user');
  }

  return $block;
}

/**
 * Content type settings form.
 */
function reol_frontend_reol_profile_link_content_type_edit_form($form, &$form_state) {
  return $form;
}
