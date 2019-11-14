<?php

/**
 * @file
 * Municipality statistics.
 */

/**
 * Municipality statistics implementation.
 */
class ReolStatisticsMunicipality implements ReolStatisticsInterface, ReolStatisticsMunicipalityInterface {

  /**
   * {@inheritdoc}
   */
  public function schema() {
    $schema = array(
      'reol_statistics_municipality' => array(
        'description' => 'Monthly municipality statistics',
        'fields' => array(
          'month' => array(
            'description' => 'Month, stored as YYYYMM.',
            'type' => 'int',
            'not null' => TRUE,
            'default' => 0,
          ),
          'retailer_id' => array(
            'description' => 'Retailer id of library.',
            'type' => 'varchar',
            'length' => 255,
          ),
          'loans' => array(
            'description' => 'Total loans.',
            'type' => 'int',
            'not null' => TRUE,
            'default' => 0,
          ),
          'users' => array(
            'description' => 'Unique users.',
            'type' => 'int',
            'not null' => TRUE,
            'default' => 0,
          ),
        ),
        'indexes' => array(
          'month_retailer' => array('month', 'retailer_id'),
        ),
      ),
    );

    return $schema;
  }

  /**
   * {@inheritdoc}
   */
  public function collect(ReolStatisticsMonth $month) {
    $data = array();
    $empty = array(
      'month' => (string) $month,
      'loans' => 0,
      'users' => 0,
    );
    // Collect loans and unique users.
    $query = db_select('reol_statistics_loans', 'l');
    $query->join('reol_statistics_unilogin', 'u', 'l.sid = u.sid');
    $query->fields('l', array('retailer_id'));
    $query->addExpression('COUNT(l.sid)', 'loans');
    $query->addExpression('COUNT(DISTINCT l.user_hash)', 'users');
    $query->condition('l.timestamp', array($month->getStartTimestamp(), $month->getEndTimestamp()), 'BETWEEN');
    $query->groupBy('l.retailer_id');

    foreach ($query->execute() as $row) {
      if (!isset($data[$row->retailer_id])) {
        $data[$row->retailer_id] = $empty + array(
          'retailer_id' => $row->retailer_id,
        );
      }
      $data[$row->retailer_id]['loans'] = $row->loans;
      $data[$row->retailer_id]['users'] = $row->users;
    }

    if ($data) {
      foreach ($data as $row) {
        $query = db_merge('reol_statistics_municipality')
          ->key(
            array(
              'month' => $row['month'],
              'retailer_id' => $row['retailer_id'],
            )
          )
          ->fields(
            array(
              'loans' => $row['loans'],
              'users' => $row['users'],
            )
          );
        $query->execute();
      }
    }
  }

  /**
   * {@inheritdoc}
   */
  public function buildMunicipality(PublizonConfiguredLibrary $library, ReolStatisticsMonth $from, ReolStatisticsMonth $to) {
    if (!isset($library->unilogin_id)) {

      return '';
    }

    $header = array(array());
    $loan_row = array(
      array(
        'data' => t('Number of loans'),
        'header' => TRUE,
      ),
    );
    $user_row = array(
      array(
        'data' => t('Unique users (count)'),
        'header' => TRUE,
      ),
    );
    $percentage_row = array(
      array(
        'data' => t('Unique users (% of subscribed)'),
        'header' => TRUE,
      ),
    );

    // We create an array of columns that we can just iterate over.
    $cols = array();
    foreach ($from->rangeTo($to) as $month) {
      $cols[] = array(
        'label' => $month->getMonthName(),
        'from' => (string) $month,
        'to' => (string) $month,
        'total' => FALSE,
      );
    }
    $cols[] = array(
      'label' => t('Total'),
      'from' => (string) $from,
      'to' => (string) $to,
      'total' => TRUE,
    );

    foreach ($cols as $col) {
      $header[] = $col['label'];
      if ($col['total']) {
        // Total will have to be recalculated for unique users, as we can't
        // pre-calculate it for arbitrary ranges.
        $query = db_select('reol_statistics_loans', 'l');
        $query->join('reol_statistics_unilogin', 'u', 'l.sid = u.sid');
        $query->addExpression('COUNT(l.sid)', 'loans');
        $query->addExpression('COUNT(DISTINCT user_hash)', 'users');
        $query->condition('l.timestamp', array($from->getStartTimestamp(), $to->getEndTimestamp()), 'BETWEEN');
        $query->condition('l.retailer_id', $library->retailer_id);

      }
      else {
        $query = db_select('reol_statistics_municipality', 'm')
          ->condition('m.month', array($col['from'], $col['to']), 'BETWEEN')
          ->condition('m.retailer_id', $library->retailer_id);
        $query->addExpression('SUM(m.loans)', 'loans');
        $query->addExpression('SUM(m.users)', 'users');
      }

      if ($row = $query->execute()->fetchObject()) {
        if (!is_null($row->loans)) {
          $loan_row[] = $row->loans;
          $user_row[] = $row->users;
          $percentage_row[] = sprintf('%.' . ($col['total'] ? 0 : 2) . 'f%%', ($row->users / $library->subscribed_users) * 100);
        }
        else {
          $loan_row[] = $user_row[] = $percentage_row[] = '';
        }
      }
    }

    $table = array(
      'attributes' => array(
        'class' => array('statistics-municipality'),
      ),
      'caption' => t('1. Loans in municipality, per month and total'),
      'header' => $header,
      'rows' => array(
        $loan_row,
        $user_row,
        $percentage_row,
      ),
    );

    return theme('table', $table);
  }

}
