<?php

/**
 * @file
 * Pages for reol_statistics.
 */

/**
 * Page callback for the municipality select page.
 */
function reol_statistics_select_municipality_page() {
  $output = '';
  $publizon_libraries = publizon_get_libraries();

  $libraries = array();
  foreach ($publizon_libraries as $retailer_id => $def) {
    if (!empty($def['unilogin_id']) && !empty($def['subscribed_users'])) {
      $libraries[$def['library_name']] = $retailer_id;
    }
  }

  // Table of general statistics.
  $table = array(
    'caption' => t('Municipality ranking'),
    'rows' => array(),
  );

  $current_month = date('Ym');
  foreach (range(2016, date('Y')) as $year) {
    $table['rows'][] = array(
      array(
        'data' => $year,
        'header'  => TRUE,
        'colspan' => 12,
      ),
    );

    $row = array();
    foreach (range(1, 12) as $month_num) {
      $cell = '';
      $month = new ReolStatisticsMonth($year, $month_num);
      $month_string = (string) $month;
      $month_name = format_date($month->getStartTimestamp(), 'custom', 'M');
      if ($month_string > '201608' && $month_string <= $current_month) {
        $path = 'statistics/general/' . $month_string . '/' . $month_string;
        $cell = l($month_name, $path);
      }
      else {
        $cell = $month_name;
      }

      // We don't want cells for months before the start of the statistics.
      if ($month_string > '201608') {
        $row[] = $cell;
      }
    }
    $table['rows'][] = $row;
  }

  $output = theme('table', $table);

  // Library listing.
  ksort($libraries);
  $options = array(
    'attributes' => array(
      'class' => array(
        'btn-statistics',
      ),
    ),
  );

  $output .= '<h2 class="statistics-header">' . t('Select municipality to view the local stastistics') . '</h2>';
  foreach ($libraries as $name => $id) {
    $path = 'statistics/municipality/' . $id . '/201609/201612';
    $output .= l($name, $path, $options);
  }

  return $output;
}

/**
 * Page callback for general statistics display.
 */
function reol_statistics_general_page($from, $to) {
  $statistics = reol_statistics_get();

  $output = '';

  foreach ($statistics as $statistic) {
    if ($statistic instanceof ReolStatisticsGeneralInterface) {
      reol_statistics_ensure_schema($statistic);
      $output .= $statistic->buildGeneral($from, $to);
    }
  }
  return $output;
}

/**
 * Page callback for municipality statistics display.
 */
function reol_statistics_municipality_page($library, $from, $to) {
  $statistics = reol_statistics_get();

  $output = '';
  $header = variable_get('reol_statistics_header',
                                array(
                                  'value' => REOL_STATISTICS_DEFAULT_HEADER,
                                  'format' => 'plain_text',
                                ));

  $replacements = array(
    '@date' => date('Y-m-d'),
    '@municipality' => $library['library_name'],
    '@subscribed_users' => $library['subscribed_users'],
  );
  $output .= format_string(check_markup($header['value'], $header['format']), $replacements);

  foreach ($statistics as $statistic) {
    if ($statistic instanceof ReolStatisticsMunicipalityInterface) {
      reol_statistics_ensure_schema($statistic);
      $output .= $statistic->buildMunicipality($library, $from, $to);
    }
  }
  return $output;
}

/**
 * Page callback for publizon loan count.
 */
function reol_statistics_publizon_page($library, $month = NULL) {
  if ($month) {
    $month = reol_statistics_month_load($month);
  }

  if (!$month) {
    $month = reol_statistics_month_load(date('Ym'));
  }

  // Make sure the table exists.
  reol_statistics_ensure_schema(new ReolStatisticsMunicipality());

  $res = db_select('reol_statistics_municipality', 'm')
    ->fields('m', array('loans'))
    ->condition('m.municipality_id', $library['unilogin_id'])
    ->condition('m.month', (string) $month)
    ->execute();

  $count = $res->fetchField();
  if (!$count) {
    $count = 0;
  }

  echo (string) $count;
  drupal_exit();
}
