<?php

/**
 * Panels layout for the front page.
 */

$plugin['reol_frontpage'] = array(
  'title' => t('Reol frontpage'),
  'icon' => 'reol_frontpage.png',
  'theme' => 'reol_frontpage',
  'category'  => 'eReolen',
  'regions' => array(
    'top' => t('Top'),
    'left' => t('Left'),
    'highlight' => t('Highlight'),
    'right' => t('Right'),
    'bottom' => t('Bottom'),
  ),
);
