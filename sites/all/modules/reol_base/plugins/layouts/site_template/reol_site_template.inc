<?php

/**
 * @file
 * This file defines the site template layout for eReolen.
 */

$plugin = array(
  'title'     => t('eReolen Site template'),
  'theme'     => 'reol_site_template',
  'icon'      => 'reol_site_template.png',
  'category'  => 'eReolen, theme',
  'regions' => array(
    'top'        => t('Top'),
    'branding'   => t('Branding'),
    'header'     => t('Header'),
    'navigation' => t('Navigation'),
    'content'    => t('Main content'),
    'footer'     => t('Footer'),
    'bottom'     => t('Bottom'),
  ),
);
