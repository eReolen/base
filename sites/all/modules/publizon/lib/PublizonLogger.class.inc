<?php

/**
 * @file
 * Logger classes used to log information from the Publizon client.
 */

/**
 * Logger class that is used to send logged messages to the system for later
 * usage in debugging problems.
 */
abstract class PublizonLogger {

  const EMERGENCY = 'EMERGENCY';
  const ALERT = 'ALERT';
  const CRITICAL = 'CRITICAL';
  const ERROR = 'ERROR';
  const WARNING = 'WARNING';
  const NOTICE = 'NOTICE';
  const INFO = 'INFO';
  const DEBUG = 'DEBUG';

  /**
   * Defines the different levels that a error message can have.
   */
  static public $levels = array(
    self::EMERGENCY,
    self::ALERT,
    self::CRITICAL,
    self::ERROR,
    self::WARNING,
    self::NOTICE,
    self::INFO,
    self::DEBUG,
  );

  /**
   * Log a message.
   *
   * @param string $message
   *   The message to log.
   * @param string $severity
   *   The severity of the message.
   *
   * @throws Exception
   */
  public function log($message, $severity = self::INFO) {
    if (!in_array($severity, self::$levels)) {
      throw new Exception('Unsupported severity: ' . $severity);
    }
    $this->doLog($message, $severity);
  }

  /**
   * Method that must be overridden by child classes.
   */
  abstract protected function dolog($message, $severity);

}

/**
 * Watch dog logger that ensure that the log message is sent to Drupal's
 * logger.
 */
class PublizonWatchDogLogger extends PublizonLogger {

  /**
   * Actually log, and to watchdog.
   */
  public function doLog($message, $severity) {
    watchdog('publizon client', htmlspecialchars($message, ENT_QUOTES, 'UTF-8', FALSE), array(),
      constant('WATCHDOG_' . $severity),
      'http://' . $_SERVER["HTTP_HOST"] . request_uri());
  }

}

/**
 * Void logger class that sends the log message into the big void.
 */
class PublizonVoidLogger extends PublizonLogger {

  /**
   * Log nothing.
   */
  public function doLog($message, $severity) {}

}
