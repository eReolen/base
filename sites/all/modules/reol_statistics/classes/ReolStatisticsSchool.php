<?php

/**
 * @file
 * School statistics.
 */

/**
 * School statistics implementation.
 */
class ReolStatisticsSchool implements ReolStatisticsInterface {

  /**
   * {@inheritdoc}
   */
  public function schema() {
    $schema = array(
      'reol_statistics_school' => array(
        'description' => 'Monthly school statistics',
        'fields' => array(
          'month' => array(
            'description' => 'Month, stored as YYYYMM.',
            'type' => 'int',
            'not null' => TRUE,
            'default' => 0,
          ),
          'school_id' => array(
            'description' => 'School id.',
            'type' => 'varchar',
            'length' => 255,
          ),
          'school' => array(
            'description' => 'School name.',
            'type' => 'varchar',
            'length' => 255,
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
        ),
        'indexes' => array(
          'month_school' => array('month', 'school_id'),
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
    );
    // Collect loans.
    $query = db_select('reol_statistics_loans', 'l');
    $query->join('reol_statistics_unilogin', 'u', 'l.sid = u.sid');
    $query->fields('u', array('municipality_id', 'school_id', 'school'));
    $query->addExpression('COUNT(l.sid)', 'loans');
    $query->condition('l.timestamp', array($month->getStartTimestamp(), $month->getEndTimestamp()), 'BETWEEN');
    $query->groupBy('municipality_id');
    $query->groupBy('school_id');

    foreach ($query->execute() as $row) {
      $index = $row->municipality_id . ':' . $row->school_id;
      if (!isset($data[$index])) {
        $data[$index] = $empty + array(
          'municipality_id' => $row->municipality_id,
          'school_id' => $row->school_id,
        );
      }
      $data[$index]['school'] = $row->school;
      $data[$index]['loans'] += $row->loans;
    }

    if ($data) {
      foreach ($data as $row) {
        $query = db_merge('reol_statistics_school')
               ->key(
                 array(
                   'month' => $row['month'],
                   'municipality_id' => $row['municipality_id'],
                   'school_id' => $row['school_id'],
                 )
               )
               ->fields(
                 array(
                   'loans' => $row['loans'],
                   'school' => $row['school'],
                 )
               );
        $query->execute();
      }
    }
  }

  /**
   * {@inheritdoc}
   */
  public function build(array $library, ReolStatisticsMonth $from, ReolStatisticsMonth $to) {
    if (!isset($library['unilogin_id'])) {
      return '';
    }

    $header = array(array());
    $sub_header = array('School');
    $school_rows = array();

    // We create an array of columns that we can just iterate over.
    $cols = array();
    foreach ($from->rangeTo($to) as $month) {
      $cols[] = array(
        'label' => $month->getMonthName(),
        'from' => (string) $month,
        'to' => (string) $month,
      );
    }
    $cols[] = array(
      'label' => t('Total'),
      'from' => (string) $from,
      'to' => (string) $to,
    );

    // School data. Indexed by school (the name, so we kan ksort it), the value
    // is an array of columns.
    $school_data = array();
    foreach ($cols as $index => $col) {
      $header[] = array(
        'data' => $col['label'],
        'colspan' => 2,
      );
      $sub_header[] = t('Number of loans');
      $sub_header[] = t('% of total');

      // Get the total count of loans across schools for this period. We need it
      // for the percentage calculation.
      $query = db_select('reol_statistics_school', 's')
             ->condition('s.month', array($col['from'], $col['to']), 'BETWEEN')
             ->condition('s.municipality_id', $library['unilogin_id']);
      $query->addExpression('SUM(s.loans)', 'loans');

      // This might return false if there's no loans in the period, but then
      // there's no schools either, so it wont be used.
      $total = $query->execute()->fetchField();

      $query = db_select('reol_statistics_school', 's')
             ->condition('s.month', array($col['from'], $col['to']), 'BETWEEN')
             ->condition('s.municipality_id', $library['unilogin_id'])
             ->fields('s', array('school'))
             ->groupBy('school_id');
      $query->addExpression('SUM(s.loans)', 'loans');

      foreach ($query->execute() as $row) {
        if (!isset($school_data[$row->school])) {
          $school_data[$row->school] = array();
        }

        $school_data[$row->school][$index] = array(
          'loans' => $row->loans,
          'percentage' => ($row->loans / $total) * 100,
        );
      }
    }

    ksort($school_data);
    $table = array(
      'caption' => t('2. Number of loans per school in municipality, per month'),
      'header' => $header,
      'rows' => array(
        $sub_header,
      ),
    );

    foreach ($school_data as $school => $columns) {
      $row = array($school);
      foreach (array_keys($cols) as $index) {
        if (isset($columns[$index])) {
          $row[] = $columns[$index]['loans'];
          $row[] = sprintf('%.2f %%', $columns[$index]['percentage']);
        }
        else {
          $row[] = $row[] = '';
        }
      }
      $table['rows'][] = $row;
    }

    return theme('table', $table);
  }

}
