<?php

/**
 * @file
 * Classes used by publizon module.
 */

/**
 * Publizon provider exception.
 */
class PublizonDingProviderException extends DingProviderEnduserException {
  /**
   * TODO missing member variable doc comment.
   *
   * @var bool
   */
  private $showBookmark;
  /**
   * TODO missing member variable doc comment.
   *
   * @var bool
   */
  private $showReserve;
  /**
   * TODO missing member variable doc comment.
   *
   * @var exception
   */
  private $exception;

  /**
   * Convert a PublizonException to a PublizonDingProviderException.
   *
   * Rethrows the new exception.
   *
   * @throws PublizonDingProviderException
   *   The new exception.
   */
  public static function convert(PublizonException $publizon_exception) {
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
// phpcs:disable
/**
 * Represents a library.
 *
 * Not called PublizonLibrary as that's already taken by the client.
 */
class PublizonConfiguredLibrary {
  /**
   * TODO missing member variable doc comment.
   *
   * @var string
   */
  public $retailer_id = '';
  /**
   * TODO missing member variable doc comment.
   *
   * @var string
   */
  public $library_name = '';
  /**
   * TODO missing member variable doc comment.
   *
   * @var string
   */
  public $unilogin_id = '';
  /**
   * TODO missing member variable doc comment.
   *
   * @var string
   */
  public $retailer_key_code = '';
  /**
   * TODO missing member variable doc comment.
   *
   * @var string
   */
  public $subscribed_users = '';
// phpcs:enable

  /**
   * Create from array.
   */
  public static function fromArray($array) {
    $lib = new self();
    foreach ($array as $key => $val) {
      if (property_exists($lib, $key)) {
        $lib->{$key} = $val;
      }
    }

    return $lib;
  }

  /**
   * Convert to array.
   */
  public function toArray() {
    return get_object_vars($this);
  }

}
