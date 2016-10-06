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

/**
 * Represents a library.
 *
 * Not called PublizonLibrary as that's already taken by the client.
 */
class PublizonConfiguredLibrary {
  /*
   * Should be static, but arrays is only allowed for statics in PHP 5.6+.
   */
  protected $properties = array(
    'library_name',
    'retailer_id',
    'unilogin_id',
    'retailer_key_code',
    'subscribed_users',
  );

  /**
   * Constructor.
   */
  public function __construct() {
    foreach ($this->properties as $prop) {
      if (!isset($this->{$prop})) {
        $this->{$prop} = '';
      }
    }
  }

  /**
   * Create from array.
   */
  public static function fromArray($array) {
    $lib = new self();
    foreach ($lib->properties as $prop) {
      if (isset($array[$prop])) {
        $lib->{$prop} = $array[$prop];
      }
    }
    return $lib;
  }

  /**
   * Get field list.
   */
  public static function fields() {
    // A bit odd, but as we can't use an array as a static variable.
    $lib = new self();
    return $lib->properties;
  }

  /**
   * Convert to array.
   */
  public function toArray() {
    $array = array();
    foreach ($this->properties as $prop) {
      $array[$prop] = $this->{$prop};
    }

    return $array;
  }

}
