<?php

/**
 * @file
 * Municipality rank statistics.
 */

/**
 * Municipality rankstatistics implementation.
 */
class ReolStatisticsMunicipalityRank implements ReolStatisticsInterface, ReolStatisticsGeneralInterface {

  /**
   * {@inheritdoc}
   */
  public function schema() {
    $schema = array();

    return $schema;
  }

  /**
   * {@inheritdoc}
   */
  public function collect(ReolStatisticsMonth $month) {
    // Nothing to be done, we leech of ReolStatisticsMunicipality's data.
  }

  /**
   * {@inheritdoc}
   */
  public function buildGeneral(ReolStatisticsMonth $from, ReolStatisticsMonth $to) {
    // This table is an aberration, it's not for the given library, but
    // globally, and not for the given period, but always the last month(s),
    // but they insisted.
    $libraries = array();
    foreach (publizon_get_libraries() as $def) {
      // We're only listing libraries that's configured for unilogin.
      if (!empty($def->unilogin_id)) {
        $libraries[$def->retailer_id] = array(
          'subscribed_users' => $def->subscribed_users,
          'name' => $def->library_name,
        );
      }
    }

    // Avoid excessive casting.
    $month_str = (string) $from;

    $prev_month = $from->prev();

    $header = array(
      t('Position'),
      t('Municipality'),
      t('Loans per student'),
      t('Position (last month)'),
      array('data' => t('Subscribed students'), 'field' => 'subscribed_users'),
      t('Unique users (% of subscribed)'),
      array('data' => t('Loans'), 'field' => 'loans'),
    );

    $rows = array();

    $query = db_select('reol_statistics_municipality', 'm')
      ->fields('m', array('month', 'retailer_id', 'loans', 'users'))
      ->condition('m.month', array($month_str, (string) $prev_month), 'IN');

    // Sort municipalities in order of most loans per subscribed users for
    // both current and previous month.
    $munis = array();
    $prev_munis = array();
    foreach ($query->execute() as $row) {
      if (isset($libraries[$row->retailer_id])) {
        $ratio = $libraries[$row->retailer_id]['subscribed_users'] > 0 ?
          $row->loans / $libraries[$row->retailer_id]['subscribed_users'] :
          0;
        $row->ratio = $ratio;
        if ($row->month == $month_str) {
          $munis[(string) $ratio][] = $row;
        }
        else {
          $prev_munis[(string) $ratio][] = $row;
        }
      }
    }

    // Sort on placement.
    krsort($munis);
    krsort($prev_munis);

    // Add placement to each row.
    $placement = 1;
    foreach ($munis as $muni) {
      foreach ($muni as $row) {
        $muni[0]->placement = $placement;
      }
      $placement++;
    }

    // Determine placement of last month, and convert to lookup table.
    $placement = 1;
    $prev_munis_lookup = array();
    foreach ($prev_munis as $items) {
      foreach ($items as $row) {
        $row->placement = $placement;
        $prev_munis_lookup[$row->retailer_id] = $row;
      }
      $placement++;
    }

    // Sort by selected table headers.
    $ts = tablesort_init($header);
    $sorted_munis = array();
    foreach ($munis as $items) {
      foreach ($items as $row) {
        switch ($ts['sql']) {
          case 'loans':
            $sorted_munis[$row->loans] = $row;
            break;

          case 'subscribed_users':
            $subscribed_users = $libraries[$row->retailer_id]['subscribed_users'];
            $sorted_munis[$subscribed_users] = $row;
            break;

          default:
            // Just append. Array indexes will ensure they keep the ordering.
            $sorted_munis[] = $row;
        }
      }
    }
    $func = $ts['sort'] == 'asc' ? 'ksort' : 'krsort';
    $func($sorted_munis);

    // Create table.
    $totals = array(
      'subscribed_users' => 0,
      'loans' => 0,
    );

    foreach ($sorted_munis as $row) {
      $subscribed_users = $libraries[$row->retailer_id]['subscribed_users'];
      $prev_placement = '';
      if (isset($prev_munis_lookup[$row->retailer_id])) {
        $prev_placement = $prev_munis_lookup[$row->retailer_id]->placement;
      }
      if ($libraries[$row->retailer_id]['subscribed_users'] > 0) {
        $ratio = round($row->ratio, 3);
        $ratio = sprintf('%.3f', $row->ratio);
      }
      else {
        $ratio = '';
      }
      $rows[] = array(
        $row->placement,
        array(
          'data' => $libraries[$row->retailer_id]['name'],
          'class' => 'municipality-column',
        ),
        $ratio,
        $prev_placement,
        $libraries[$row->retailer_id]['subscribed_users'],
        $libraries[$row->retailer_id]['subscribed_users'] > 0 ? sprintf("%.0f%%", ($row->users / $subscribed_users) * 100) : '',
        $row->loans,
      );
      $totals['subscribed_users'] += $subscribed_users;
      $totals['loans'] += $row->loans;
    }

    $rows[] = array(
      array(
        'data' => t('Total'),
        'header' => TRUE,
      ),
      '',
      '',
      '',
      $totals['subscribed_users'],
      '',
      $totals['loans'],
    );

    $table = array(
      'attributes' => array(
        'class' => array('statistics-municipality-rank'),
      ),
      'caption' => t('Municipalities ranked by loans per subscribed students'),
      'header' => $header,
      'rows' => $rows,
    );

    return theme('table', $table);
  }

}
