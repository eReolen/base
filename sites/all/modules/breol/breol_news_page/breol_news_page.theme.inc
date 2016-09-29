<?php

/**
 * @file
 * Theming functions.
 */

/**
 * Preprocess breol_news_page.
 */
function template_preprocess_breol_news_page(&$vars) {
  if ($vars['image_file']) {
    $vars['image'] = theme(
      'image',
      array('path' => $vars['image_file']->uri)
    );
  }
}
