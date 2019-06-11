<?php

/**
 * @file
 * Drush commands for the reol_review module.
 */

/**
 * Implements hook_drush_command().
 */
function reol_review_drush_command() {
  $commands['reol-review-check'] = array(
    'description' => 'Check availability of reviews from litteratursiden.dk.',
    'options' => array(
      'count' => array(
        'description' => 'Number of items to process (default: 100).',
        'value' => 'required',
      ),
      'updated-before' => array(
        'description' => 'Process items last updated before this time.',
        'value' => 'required',
      ),
    ),
    'examples' => array(
      'drush reol-review-check' => 'Process 100 items.',
      'drush reol-review-check --count=87' => 'Process 87 items.',
      'drush reol-review-check --updated-before="-1 month"' => 'Process items updated more than 1 month ago.',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_DATABASE,
  );

  return $commands;
}

/**
 * Check status of reviews.
 */
function drush_reol_review_check() {
  $count = drush_get_option('count', 100);
  $updated_before = drush_get_option('updated-before');

  $condition = db_or();
  $condition->isNull('http_code');
  if (NULL !== $updated_before) {
    $time = strtotime($updated_before);
    if (FALSE !== $time) {
      $condition->condition('http_code_updated', $time, '<');
    }
  }

  $query = db_select('reol_review_reviews', 'r')
    ->fields('r', array('rrid', 'link'))
    ->condition($condition)
    ->range(0, $count);
  $rows = $query->execute()->fetchAll();

  $count = 0;
  foreach ($rows as $row) {
    $count++;

    $url = $row->link;
    $result = drupal_http_request($url, ['method' => 'HEAD']);
    $code = $result->code;

    drush_log(sprintf('%04d/%04d % 8s %s %s', $count, count($rows), '#' . $row->rrid, $code, $url));

    db_update('reol_review_reviews')
      ->fields([
        'http_code' => $code,
        'http_code_updated' => REQUEST_TIME,
      ])
      ->condition('link', $row->link)
      ->execute();
  }
}
