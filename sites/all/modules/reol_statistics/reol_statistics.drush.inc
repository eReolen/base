<?php

/**
 * @file
 */

/**
 * Implements hook_drush_command().
 */
function reol_statistics_drush_command() {
  $commands['reol-statistics-crunch-isbn'] = [
    'description' => 'Crunch data for ReolStatisticsISBN.',
    'arguments' => [
      'month' => 'Month to crunch (default: current month).',
    ],
    'examples' => [
      'drush reol-statistics-crunch-isbn' => 'Cruch data for current month.',
      'drush reol-statistics-crunch-isbn "previous month"' => 'Cruch data for previous month.',
      'drush reol-statistics-crunch-isbn 2019-01' => 'Cruch data for January 2019.',
    ],
  ];

  return $commands;
}

/**
 * Drush command logic.
 * drush_[COMMAND_NAME]().
 */
function drush_reol_statistics_crunch_isbn($month = NULL) {
  $month = new \DateTime(NULL === $month ? 'first day of this month' : $month);

  $statistic = new ReolStatisticsISBN();
  $statistic->collect(ReolStatisticsMonth::fromInt((int) $month->format('Ym')));
}
