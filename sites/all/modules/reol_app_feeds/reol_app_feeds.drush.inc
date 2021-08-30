<?php

/**
 * @file
 * Drush commands for the reol_app_feeds module.
 */

use Drupal\reol_app_feeds\Helper\FeedHelper;

/**
 * Implements hook_drush_command().
 */
function reol_app_feeds_drush_command() {
  $commands['reol-app-feeds-generate'] = array(
    'description' => 'Generate app feeds.',
    'arguments' => [
      'names' => 'One or more feed names (space-separated). Use --list to list all feed names.',
    ],
    'options' => [
      'all' => [
        'description' => 'Generate all feeds.',
      ],
      'list' => [
        'description' => 'List all feed names.',
      ],
    ],
    'examples' => array(
      'drush reol-app-feeds-generate --list' => 'List all feed names.',
      'drush reol-app-feeds-generate categories' => 'Generate categories feed.',
      'drush reol-app-feeds-generate categories frontpage' => 'Generate categories and frontpage feeds.',
      'drush reol-app-feeds-generate --all' => 'Generate all feeds.',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_DATABASE,
  );

  return $commands;
}

/**
 * Callback function for reol-app-feeds-generate command.
 */
function drush_reol_app_feeds_generate() {
  if (drush_get_option('list', FALSE)) {
    foreach (FeedHelper::$feedNames as $name) {
      drush_print($name);
    }
    return;
  }

  $all = drush_get_option('all', FALSE);
  $verbose = drush_get_option('verbose', FALSE);
  $feeds = $all ? FeedHelper::$feedNames : func_get_args();

  $feedHelper = new FeedHelper();
  foreach ($feeds as $feed) {
    $starttime = microtime(TRUE);
    $result = $feedHelper->generate($feed);
    $endtime = microtime(TRUE);
    if ($verbose) {
      drush_print(sprintf(
        '%-24s %s (%s)',
        $feed,
        FALSE === $result ? '–' : sprintf('%12d bytes', $result),
        sprintf('%.3f s', $endtime - $starttime)
      ));
    }
  }
}
