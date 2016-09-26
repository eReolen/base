<?php

/**
 * Helper class for month handling.
 */
class ReolStatisticsMonth {
  private $month;
  private $year;

  /**
   * Create ReolStatisticsMonth from int in YYYYMM format.
   */
  static public function fromInt($int) {
    $year = substr((string) $int, 0, 4);
    $month = substr((string) $int, 4, 2);

    return new self($year, $month);
  }

  /**
   * Create ReolStatisticsMonth from year and month.
   */
  public function __construct($year, $month) {
    $this->year = $year;
    $this->month = $month;
  }

  /**
   * Return YYYYMM string representation.
   */
  public function __toString() {
    return sprintf('%04u%02u', $this->year, $this->month);
  }

  /**
   * Return YYYYMM int representation.
   */
  public function toInt() {
    return (int) ((string) $this);
  }

  /**
   * Get the following month.
   */
  public function next() {
    $year = $this->year;
    $month = $this->month;
    if ($month >= 12) {
      $year += 1;
      $month = 0;
    }

    return new self($year, $month + 1);
  }

  /**
   * Return the name of the month.
   */
  public function getMonthName() {
    return drupal_ucfirst(format_date($this->getStartTimestamp(), 'custom', 'F'));
  }

  /**
   * Whether this is the current month.
   */
  public function isCurrent() {
    if (date('Y') == $this->year && date('m') == $this->month) {
      return TRUE;
    }
    return FALSE;
  }

  /**
   * Get a DateTime representing the start of the month.
   */
  public function getStartDateTime() {
    return new DateTime($this->year . '-' . $this->month);
  }

  /**
   * Timestamp of the start of the month.
   */
  public function getStartTimestamp() {
    return $this->getStartDateTime()->getTimestamp();
  }

  /**
   * DateTime just off end of the month.
   */
  public function getEndDateTime() {
    return $this->getStartDateTime()->add(new DateInterval('P1M'));
  }

  /**
   * Timestamp just off end of the month.
   */
  public function getEndTimestamp() {
    return $this->getEndDateTime()->getTimestamp();
  }

  /**
   * Return an range of months from this to the given month.
   */
  public function rangeTo(ReolStatisticsMonth $other) {
    if ($this->toInt() > $other->toInt()) {
      throw new RuntimeException('Other ReolStatisticsMonth must be equal or later than this.');
    }

    $next = $this;
    $range = array($next);
    while ($next->toInt() != $other->toInt()) {
      $range[] = $next = $next->next();
    }

    return $range;
  }

}
