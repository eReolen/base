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
          'municipality_id' => array(
            'description' => 'Municipality id of school.',
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
          'month_municipality' => array('month', 'municipality_id'),
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
    // Collect loans.
    $query = db_select('reol_statistics_loans', 'l');
    $query->join('reol_statistics_unilogin', 'u', 'l.sid = u.sid');
    $query->fields('u', array('municipality_id'));
    $query->addExpression('COUNT(l.sid)', 'loans');
    $query->condition('l.timestamp', array($month->getStartTimestamp(), $month->getEndTimestamp()), 'BETWEEN');
    $query->groupBy('municipality_id');

    foreach ($query->execute() as $row) {
      if (!isset($data[$row->municipality_id])) {
        $data[$row->municipality_id] = $empty + array(
          'municipality_id' => $row->municipality_id,
        );
      }
      $data[$row->municipality_id]['loans'] += $row->loans;
    }

    // Collect unique users.
    $query = db_select('reol_statistics_loans', 'l');
    $query->join('reol_statistics_unilogin', 'u', 'l.sid = u.sid');
    $query->fields('u', array('municipality_id'));
    $query->addExpression('COUNT(DISTINCT user_hash)', 'users');
    $query->condition('l.timestamp', array($month->getStartTimestamp(), $month->getEndTimestamp()), 'BETWEEN');
    $query->groupBy('municipality_id');

    foreach ($query->execute() as $row) {
      if (!isset($data[$row->municipality_id])) {
        $data[$row->municipality_id] = $empty + array(
          'municipality_id' => $row->municipality_id,
        );
      }
      $data[$row->municipality_id]['users'] = $row->users;
    }

    if ($data) {
      foreach ($data as $row) {
        $query = db_merge('reol_statistics_municipality')
               ->key(
                 array(
                   'month' => $row['month'],
                   'municipality_id' => $row['municipality_id'],
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
        'scale' => 2,
      );
    }
    $cols[] = array(
      'label' => t('Total'),
      'from' => (string) $from,
      'to' => (string) $to,
      'scale' => 0,
    );

    foreach ($cols as $col) {
      $header[] = $col['label'];
      $query = db_select('reol_statistics_municipality', 'm')
             ->condition('m.month', array($col['from'], $col['to']), 'BETWEEN')
             ->condition('m.municipality_id', $library->unilogin_id);
      $query->addExpression('SUM(m.loans)', 'loans');
      $query->addExpression('SUM(m.users)', 'users');

      if ($row = $query->execute()->fetchObject()) {
        if (!is_null($row->loans)) {
          $loan_row[] = $row->loans;
          $user_row[] = $row->users;
          $percentage_row[] = sprintf('%.' . $col['scale'] . 'f%%', ($row->users / $library->subscribed_users) * 100);
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
