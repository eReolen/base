<?php
/**
 * @file
 * CTools Content Type for showing user quota info info.
 *
 * @todo use shared user_quota_info instead.
 */

$plugin = array(
  'title' => t('Show quota info.'),
  'description' => t('Show quota info for the user.'),
  'category' => 'eReolen shared',
  'single' => TRUE,
  'content type' => 'user_quota_info',
  'hook theme' => 'reol_shared_frontend_user_quota_info_content_type_theme',
  'required context' => array(
    new ctools_context_required(t('User'), 'user'),
  ),
);

/**
 * Render the content type.
 */
function reol_shared_frontend_user_quota_info_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();

  // Load library.
  $user = $context[0]->data;
  $library_id = publizon_get_retailer_id($user);
  $library = publizon_client_library_load($library_id);

  $extra_link = url('search/ting/*', array(
    'query' => array(
      'facets' => array(
        'facet.extraTitles:ekstra titler',
      ),
    ),
  ));
  $variables = array(
    // Quotas.
    'max_ebook_loans' => $library->maxEbookLoans,
    'max_audiobook_loans' => $library->maxAudiobookLoans,
    'max_ebook_reservations' => $library->maxEbookReservations,
    'max_audiobook_reservations' => $library->maxAudiobookReservations,
    'extra_link' => $extra_link,
    // Legacy texts.
    'max_ebook_loans_text' => t('You are allowed to loan @loans e-books simultaneously.', array('@loans' => $library->maxEbookLoans)),
    'max_audiobook_loans_text' => t('You are allowed to loan @loans audiobooks simultaneously.', array('@loans' => $library->maxAudiobookLoans)),
    'max_reservations_text' => t('You are allowed to reserve @reservations titles simultaneously.', array('@reservations' => $library->maxEbookReservations)),
    'extra_info_text' => t('<a href="@url">Titles exempt from quotas.</a>', array(
      '@url' => $extra_link,
    )),
  );
  $block->content = theme('user_quota_info', $variables);

  return $block;
}

/**
 * Admin settings form.
 */
function reol_shared_frontend_user_quota_info_content_type_edit_form($form, &$form_state) {
  return $form;
}

/**
 * Ctools block theme function.
 */
function reol_shared_frontend_user_quota_info_content_type_theme(&$theme, $plugin) {
  $theme['user_quota_info'] = array(
    'variables' => array('vars' => NULL),
    'path' => $plugin['path'],
    'template' => 'user_quota_info',
  );
}
