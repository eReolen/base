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

  $message = trim(variable_get('reol_statistics_message', ''));
  if (!empty($message)) {
    $output .= '<div class="statistics-message">' . $message . '</div>';
  }

  $publizon_libraries = publizon_get_libraries();

  $libraries = array();
  foreach ($publizon_libraries as $retailer_id => $def) {
    if (!empty($def->unilogin_id) && !empty($def->subscribed_users)) {
      $libraries[$def->library_name] = $retailer_id;
    }
  }

  // Table of general statistics.
  $table = array(
    'caption' => t('Municipality ranking'),
    'rows' => array(),
  );

  $current_month = date('Ym');
  foreach (range(2016, _reol_statistics_get_final_year()) as $year) {
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

  $output .= theme('table', $table);

  // Library listing.
  ksort($libraries);

  $quarter_spec = array(
    1 => array('01', '03'),
    2 => array('04', '06'),
    3 => array('07', '09'),
    4 => array('10', '12'),
  );

  $quarters = array(
    '2016-3' => '201607/201609',
    '2016-4' => '201610/201612',
  );

  $year = 2017;
  $current = date('Ym');
  while ($year <= _reol_statistics_get_final_year()) {
    foreach ($quarter_spec as $num => $def) {
      list($from, $to) = $def;
      $start = sprintf('%d%02d', $year, $from);
      if ($start <= $current) {
        $quarters[$year . '-' . $num] = $start . '/' . sprintf('%d%02d', $year, $to);
      }
    }
    $year++;
  }

  $output .= '<h2 class="statistics-header">' . t('Select municipality to view the local stastistics') . '</h2>';
  foreach ($libraries as $name => $id) {
    $output .= '<span class="btn-statistics">' . $name . '<br />';
    foreach ($quarters as $quarter_name => $path_fragment) {
      $path = 'statistics/municipality/' . $id . '/' . $path_fragment;
      $output .= l($quarter_name, $path) . '<br />';
    }
    $output .= '</span>';
  }

  return $output;
}

/**
 * Page callback for general statistics display.
 */
function reol_statistics_general_page($from, $to) {
  if (!_reol_statistics_are_valid_months([$from, $to])) {
    return drupal_goto('/statistics');
  }

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
  if (!_reol_statistics_are_valid_months([$from, $to])) {
    return drupal_goto('/statistics');
  }

  $statistics = reol_statistics_get();

  $output = '';
  $header = variable_get('reol_statistics_header',
                                array(
                                  'value' => REOL_STATISTICS_DEFAULT_HEADER,
                                  'format' => 'plain_text',
                                ));

  $replacements = array(
    '@date' => date('Y-m-d'),
    '@municipality' => $library->library_name,
    '@subscribed_users' => $library->subscribed_users,
  );
  $output .= format_string(check_markup($header['value'], $header['format']), $replacements);

  foreach ($statistics as $statistic) {
    if ($statistic instanceof ReolStatisticsMunicipalityInterface) {
      reol_statistics_ensure_schema($statistic);
      $output .= $statistic->buildMunicipality($library, $from, $to);
    }
  }

  $footer = variable_get('reol_statistics_footer',
                         array(
                           'value' => '',
                           'format' => 'plain_text',
                         ));
  $output .= check_markup($footer['value'], $footer['format']);
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
    ->condition('m.municipality_id', $library->unilogin_id)
    ->condition('m.month', (string) $month)
    ->execute();

  $count = $res->fetchField();
  if (!$count) {
    $count = 0;
  }

  echo (string) $count;
  drupal_exit();
}

/**
 * Get final year that we support showing statistics for.
 *
 * From 2020-01-01 all collection and display of statistics are handled by
 * Publizon.
 *
 * @return int
 *   The final year.
 */
function _reol_statistics_get_final_year() {
  return 2019;
}

/**
 * Check if a month is valid.
 *
 * A month is valid if and only if it ends before the first day we do not
 * support statistics for.
 *
 * @param ReolStatisticsMonth $month
 *   The month.
 *
 * @return bool
 *   True iff the month is valid.
 */
function _reol_statistics_is_valid_month(ReolStatisticsMonth $month) {
  $finalDate = new DateTime(sprintf('first day of January %d', _reol_statistics_get_final_year() + 1));

  return $month->getEndDateTime() < $finalDate;
}

/**
 * Check if a list of months are valid (cf. _reol_statistics_is_valid_month).
 *
 * @param ReolStatisticsMonth[] $months
 *   The months.
 *
 * @return bool
 *   True iff all months are valid.
 */
function _reol_statistics_are_valid_months(array $months) {
  foreach ($months as $month) {
    if (!_reol_statistics_is_valid_month($month)) {
      return FALSE;
    }
  }

  return TRUE;
}
