<?php

/**
 * @file
 * Classes used by publizon module.
 */

/**
 * Publizon provider exception.
 */
class PublizonDingProviderException extends DingProviderUserException {
  private $showBookmark;
  private $showReserve;
  private $exception;

  /**
   * Convert a PublizonException to a PublizonDingProviderException.
   *
   * Rethrows the new exception.
   *
   * @throws PublizonDingProviderException
   *   The new exception.
   */
  static public function convert(PublizonException $publizon_exception) {
    $code = $publizon_exception->getCode();
    $message = publizon_get_message($code);

    throw new self($message['error_text']['value'], $code, $message['show_bookmark'], $message['show_reserve'], $publizon_exception);
  }

  /**
   * Constructor.
   */
  public function __construct($message, $code, $show_bookmark, $show_reserve, $exception) {
    $this->message = $message;
    $this->code = $code;
    $this->showBookmark = $show_bookmark;
    $this->showReserve = $show_reserve;
    $this->exception = $exception;
  }

  /**
   * Return whether or not to show bookmark button.
   */
  public function showBookmark() {
    return (bool) $this->showBookmark;
  }

  /**
   * Return whether or not to show reserve button.
   */
  public function showReserve() {
    return (bool) $this->showReserve;
  }
}
