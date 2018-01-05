<?php

/**
 * @file
 * reol_newsletter_paragraph.features.inc
 */

/**
 * Implements hook_paragraphs_info().
 */
function reol_newsletter_paragraph_paragraphs_info() {
  $items = array(
    'newsletter_signup' => array(
      'name' => 'Nyhedsbrevstilmelding',
      'bundle' => 'newsletter_signup',
      'locked' => '1',
    ),
  );
  return $items;
}
