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

  ksort($libraries);
  foreach ($libraries as $name => $id) {
    $output .= '<p>' . l($name, 'statistics/' . $id . '/201609/201612') . '</p>';
  }

  return $output;
}

/**
 * Page callback for statistics display.
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
    reol_statistics_ensure_schema($statistic);
    $output .= $statistic->build($library, $from, $to);
  }
  return $output;
}
