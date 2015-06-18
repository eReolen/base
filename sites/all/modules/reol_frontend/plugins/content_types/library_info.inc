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
  $library = publizon_library_load($library_id);

  $block->content = theme('library_info', array(
    'max_ebook_loans' => t('You are allowed to loan @loans e-books simultaneously.', array('@loans' => $library->maxEbookLoans)),
    'max_audiobook_loans' => t('You are allowed to loan @loans audiobooks simultaneously.', array('@loans' => $library->maxAudiobookLoans)),
    'max_reservations' => t('You are allowed to reserve @reservations titles simultaneously.', array('@reservations' => $library->maxReservations)),
    'extra_info' => t('<a href="@url">Titles exempt from quotas.</a>', array(
      '@url' => url('search/ting/*', array(
        'query' => array(
          'facets' => array(
            'facet.extraTitles:ekstra titler',
          ),
        ),
      )),
    )),
  ));

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
