<?php

/**
 * @file
 * CTools Content Type for showing the library info.
 */

$plugin = array(
  'title' => t('Show library info.'),
  'description' => t('Show the info for the library of the user.'),
  'category' => 'ereolen.dk',
  'single' => TRUE,
  'content type' => 'library_info',
  'render callback' => 'library_info_content_type_render',
  'hook theme' => 'library_info_content_type_theme',
  'edit form' => 'library_info_content_type_edit_form',
  'required context' => array(
    new ctools_context_required(t('User'), 'user'),
  ),
);

/**
 * Render the content type.
 */
function library_info_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();

  // Load library.
  $user = $context[0]->data;
  $library_id = publizon_get_retailer_id($user);
  $library = publizon_client_library_load($library_id);

  $query = array(
    'facets' => array(
      'facet.extraTitles:ekstra titler',
    ),
  );
  $extra_link = url('search/ting/*', array('query' => $query));

  // Build information on current number of loans by material type.
  global $user;
  require_once drupal_get_path('module', 'publizon') . '/includes/publizon.loan.inc';
  $loans = publizon_loan_list($user);

  // Group quota loans by type.
  $loans_by_type = [];
  foreach ($loans as $loan) {
    if ($loan->publizon_on_quota ?? FALSE) {
      $loans_by_type[$loan->publizon_type] = ($loans_by_type[$loan->publizon_type] ?? 0) + 1;
    }
  }

  $variables = array(
    'ebook_loans' => $loans_by_type['ebog'] ?? 0,
    'audiobook_loans' => $loans_by_type['lydbog (net)'] ?? 0,
    // Quotas.
    'max_ebook_loans' => $library->maxEbookLoans,
    'max_audiobook_loans' => $library->maxAudiobookLoans,
    'max_ebook_reservations' => $library->maxEbookReservations,
    'max_audiobook_reservations' => $library->maxAudiobookReservations,
    'extra_link' => $extra_link,
    // Legacy texts.
    'max_ebook_loans_text' => t('You have loaned @number_of_loans out of @max_number_of_loans e-books.', array(
      '@number_of_loans' => $loans_by_type['ebog'] ?? 0,
      '@max_number_of_loans' => $library->maxEbookLoans,
    )),
    'max_audiobook_loans_text' => t('You have loaned @number_of_loans out of @max_number_of_loans audiobooks.', array(
      '@number_of_loans' => $loans_by_type['lydbog (net)'] ?? 0,
      '@max_number_of_loans' => $library->maxAudiobookLoans,
    )),
    'max_reservations_text' => t('You are allowed to reserve @reservations titles simultaneously.', array('@reservations' => $library->maxEbookReservations)),
    'extra_info_text' => t('<a href="@url">Titles exempt from quotas.</a>', array('@url' => $extra_link)),
  );

  $block->title = t('Restrictions');
  $block->content = theme('library_info', $variables);

  return $block;
}

/**
 * Admin settings form.
 */
function library_info_content_type_edit_form($form, &$form_state) {
  return $form;
}

/**
 * Ctools block theme function.
 */
function library_info_content_type_theme(&$theme, $plugin) {
  $theme['library_info'] = array(
    'variables' => array('vars' => NULL),
    'path' => $plugin['path'],
    'template' => 'library_info',
  );
}
