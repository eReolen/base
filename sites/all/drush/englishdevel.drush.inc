<?php
/**
 * @file
 * Contains drush hack for keeping language english.
 */

/**
 * Hack to switch language to i18n source language or English in drush.
 */
function englishdevel_drush_init() {
  if (function_exists('language_list')) {
    global $language;
    $languages = language_list();
    $prefix = variable_get('i18n_string_source_language', 'en');
    $language = $languages[$prefix];
  }
}
