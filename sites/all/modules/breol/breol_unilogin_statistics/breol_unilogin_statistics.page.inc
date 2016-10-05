<?php

/**
 * @file
 * Page and forms for statistics.
 */

/**
 * Statistics dump form.
 */
function breol_unilogin_statistics_form($form, &$form_state) {
  $form['from'] = array(
    '#type' => 'date_select',
    '#title' => t('From'),
    '#default_value' => date('Y-m-01'),
    '#date_format' => 'd-m-Y',
  );

  $form['to'] = array(
    '#type' => 'date_select',
    '#title' => t('To'),
    '#default_value' => date('Y-m-d'),
    '#date_format' => 'd-m-Y',
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#default_value' => t('Submit'),
  );

  return $form;
}

/**
 * Statistics dump form.
 */
function breol_unilogin_statistics_other_form($form, &$form_state) {
  $form = breol_unilogin_statistics_form($form, $form_state);
  $form['#validate'][] = 'breol_unilogin_statistics_form_validate';

  return $form;
}

/**
 * Validate handler for statisticts dump form.
 */
function breol_unilogin_statistics_form_validate($form, &$form_state) {
  // This converts the (timezone-less) string time to a DateTime in the site
  // timezone (DateObject defaults to time timezone), which we then can
  // convert to a Unix timestamp (which sorta have a fixed timezone).
  $form_state['from'] = new DateObject($form_state['values']['from']);
  $form_state['to'] = new DateObject($form_state['values']['to']);
  if ($form_state['from'] >= $form_state['to']) {
    form_error($form['from'], t('To date must be greater than from date.'));
  }

  if ($form_state['to'] > new DateObject()) {
    form_error($form['to'], t('Dates must be in the past.'));
  }
}


/**
 * Submit handler for statisticts dump form.
 */
function breol_unilogin_statistics_form_submit($form, &$form_state) {
  // Include the to date.
  $form_state['to']->setTime(23, 59, 59);

  $form_state['redirect'] = 'admin/reports/breol_unilogin_statistics/' .
                          $form_state['from']->format('U') . '/' .
                          $form_state['to']->format('U');
}

/**
 * Submit handler for statisticts dump form.
 */
function breol_unilogin_statistics_other_form_submit($form, &$form_state) {
  // Include the to date.
  $form_state['to']->setTime(23, 59, 59);

  $form_state['redirect'] = 'admin/reports/breol_statistics/' .
                          $form_state['from']->format('U') . '/' .
                          $form_state['to']->format('U');
}

/**
 * Page callback for outputting CSV data.
 */
function breol_unilogin_statistics_data($from, $to) {
  $fields = array(
    'timestamp',
    'retailer_id',
    'class',
    'school_id',
    'school',
    'municipality_id',
    'municipality',
    'isbn',
  );

  header('Content-Type: text/csv; charset=utf-8');
  header('Content-Disposition: attachment; filename=data.csv');

  print implode(';', $fields) . "\n";

  $res = db_select('breol_unilogin_statistics', 'b')
       ->fields('b', $fields)
       ->condition('timestamp', array($from, $to), 'BETWEEN')
       ->orderBy('timestamp')
       ->execute();

  while ($row = $res->fetchAssoc()) {
    $time = new DateTime('@' . $row['timestamp']);
    $row['timestamp'] = $time->format(DateTime::ATOM);
    print implode(';', $row) . "\n";
  }

  drupal_exit();
}

/**
 * Page callback for outputting CSV data.
 */
function breol_unilogin_statistics_data_other($from, $to) {
  $libraries = publizon_get_libraries();
  $fields = array(
    'timestamp',
    'retailer_id',
    'isbn',
  );

  header('Content-Type: text/csv; charset=utf-8');
  header('Content-Disposition: attachment; filename=data.csv');

  print "timestamp;retailer_id;library;isbn\n";
  $query = db_select('reol_statistics_loans', 'b')
         ->fields('b', $fields);
  $query->leftJoin('reol_statistics_unilogin', 'u', 'b.sid = u.sid');
  $query->isNull('u.sid')
    ->condition('timestamp', array($from, $to), 'BETWEEN')
    ->orderBy('timestamp');
  $res = $query->execute();

  while ($row = $res->fetchAssoc()) {
    $time = new DateTime('@' . $row['timestamp']);
    $data = array(
      $time->format(DateTime::ATOM),
      $row['retailer_id'],
      (isset($libraries[$row['retailer_id']]) ?
        $libraries[$row['retailer_id']]->library_name : '?'),
      $row['isbn'],
    );
    print implode(';', $data) . "\n";
  }

  drupal_exit();
}
