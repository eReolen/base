<?php

/**
 * @file
 * ISBN statistics.
 */

/**
 * School statistics implementation.
 */
class ReolStatisticsISBN implements ReolStatisticsInterface, ReolStatisticsMunicipalityInterface {

  /**
   * {@inheritdoc}
   */
  public function schema() {
    $schema = array(
      'reol_statistics_isbn' => array(
        'description' => 'Daily loans of ISBN per school statistics',
        'fields' => array(
          'day' => array(
            'description' => 'Day, stored as YYYYMMDD',
            'type' => 'int',
            'not null' => TRUE,
            'default' => 0,
          ),
          'class' => array(
            'description' => 'Class of user.',
            'type' => 'varchar',
            'length' => 255,
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
          'isbn' => array(
            'description' => 'ISBN of material.',
            'type' => 'varchar',
            'length' => 255,
            'not null' => TRUE,
            'default' => '',
          ),
          'loans' => array(
            'description' => 'Total loans of material.',
            'type' => 'int',
            'not null' => TRUE,
            'default' => 0,
          ),
          'period_total' => array(
            'description' => 'Total loans in period.',
            'type' => 'int',
            'not null' => TRUE,
            'default' => 0,
          ),
        ),
        'indexes' => array(
          'municipality_school_day' => array(
            'municipality_id',
            'school_id',
            'day',
          ),
          'municipality_school_isbn_day' => array(
            'municipality_id',
            'school_id',
            'isbn',
            'day',
          ),
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
      'loans' => 0,
    );
    // Collect loans.
    $query = db_select('reol_statistics_loans', 'l');
    $query->join('reol_statistics_unilogin', 'u', 'l.sid = u.sid');
    $query->fields('l', array(
      'timestamp',
      'isbn',
    ))
      ->fields('u', array(
        'municipality_id',
        'school_id',
        'school',
        'class',
      ));
    $query->condition('l.timestamp', array($month->getStartTimestamp(), $month->getEndTimestamp()), 'BETWEEN');
    $query->orderBy('timestamp');

    // Count up the totals.
    foreach ($query->execute() as $row) {
      $day = date('Ymd', $row->timestamp);
      $index = $row->municipality_id . ':' . $row->school_id . ':' .
             $row->class . ":" . $row->isbn . ':' . $day;
      if (!isset($data[$index])) {
        $data[$index] = $empty + array(
          'class' => $row->class,
          'municipality_id' => $row->municipality_id,
          'school_id' => $row->school_id,
          'isbn' => $row->isbn,
        );
      }
      $data[$index]['day'] = $day;
      $data[$index]['school'] = $row->school;
      $data[$index]['loans'] += 1;
    }

    if ($data) {
      $period = new DateInterval('P' . variable_get('reol_statistics_isbn_period', 14) . 'D');
      foreach ($data as $row) {

        $query = db_merge('reol_statistics_isbn')
               ->key(
                 array(
                   'day' => $row['day'],
                   'class' => $row['class'],
                   'municipality_id' => $row['municipality_id'],
                   'school_id' => $row['school_id'],
                   'isbn' => $row['isbn'],
                 )
               )
               ->fields(
                 array(
                   'loans' => $row['loans'],
                   'period_total' => 0,
                   'school' => $row['school'],
                 )
               );
        $query->execute();

        // Update the row with the total of the period.
        // Start day of period where current is end day.
        $start_time = (new DateTime($row['day']))->sub($period)->format('Ymd');
        $total = db_select('reol_statistics_isbn')
               ->condition('class', $row['class'])
               ->condition('municipality_id', $row['municipality_id'])
               ->condition('school_id', $row['school_id'])
               ->condition('isbn', $row['isbn'])
               ->condition('day', array($start_time, $row['day']), 'BETWEEN');

        $total->addExpression('SUM(loans)', 'total');
        $total = $total->execute()->fetchField();

        $query = db_update('reol_statistics_isbn')
               ->condition('class', $row['class'])
               ->condition('municipality_id', $row['municipality_id'])
               ->condition('school_id', $row['school_id'])
               ->condition('isbn', $row['isbn'])
               ->condition('day', $row['day'])
               ->fields(
                 array(
                   'period_total' => $total,
                 )
               );
        $query->execute();
      }
    }
  }

  /**
   * {@inheritdoc}
   */
  public function buildMunicipality(array $library, ReolStatisticsMonth $from, ReolStatisticsMonth $to) {
    if (!isset($library['unilogin_id'])) {
      return '';
    }

    $max_count = variable_get('reol_statistics_isbn_count', 10);
    $period_days = variable_get('reol_statistics_isbn_period', 14);

    $header = array(t('Period'), t('School'), t('ISBN Number'), 'Loans');
    $isbn_rows = array();

    $start = $from->getStartDatetime()->format('Ymd');
    $end = $to->getEndDateTime()->format('Ymd');

    $query = db_select('reol_statistics_isbn', 'i')
           ->fields('i', array('day', 'isbn', 'school', 'period_total'))
           ->condition('day', array($start, $end), 'BETWEEN')
           ->condition('municipality_id', $library['unilogin_id'])
           ->condition('i.period_total', $max_count, '>');

    $isbns = array();
    foreach ($query->execute() as $row) {
      $index = $row->school . ':' . $row->isbn;
      $isbns[$index][] = $row;
    }

    // Consolidate concurrent periods so we wont repeat.
    $interval = new DateInterval('P' . $period_days . 'D');
    foreach ($isbns as $periods) {
      while ($periods) {
        $period = array_shift($periods);
        // Let anything that goes within the interval of this period belong to
        // it.
        $following = new DateTime($period->day);
        $following->add($interval);
        while ($periods && $following->format('Ymd') >= $periods[0]->day) {
          // Record the maximum total in the aggregated period.
          $period->period_total = max($period->period_total, $periods[0]->period_total);
          // Note the end of this period.
          $period->end_day = $periods[0]->day;
          // Extend the period to include the added one.
          $following = new DateTime($period->end_day);
          $following->add($interval);
          array_shift($periods);
        }

        // Periods actually goes backwards (you can't sum the future), so
        // adjust it for display.
        $start = new DateTime($period->day);
        $start->sub($interval);
        $isbn_rows[] = array(
          $start->format('j/n') . '-' .
          (new DateTime($period->end_day))->format('j/n'),
          $period->school,
          $period->isbn,
          $period->period_total,
        );
      }
    }

    if (!$isbn_rows) {
      return '';
    }

    $table = array(
      'attributes' => array(
        'class' => array('statistics-isbn'),
      ),
      'caption' => t("3. List of ISBN numbers that's been loaned more than @times times per @period days", array(
        '@times' => $max_count,
        '@period' => $period_days,
      )),
      'header' => $header,
      'rows' => $isbn_rows,
    );

    return theme('table', $table);
  }

}
