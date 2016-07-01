<?php

/**
 * @file
 * Base class for classes communicating with the UNI•Login services.
 */

/**
 * Base class for UNI•Login services.
 */
abstract class DingUniloginServiceBase {
  protected $client;

  /**
   * Base constructor.
   */
  public function __construct($user, $pass) {
    $this->client = new SoapClient($this::WSDLURL, array('trace' => TRUE));
    $this->user = $user;
    $this->pass = $pass;
  }

  /**
   * Call service method.
   */
  protected function call($method, $parameters = array()) {
    try {
      $res = $this->client->{$method}($parameters);
      return isset($res->return) ? $res->return : NULL;
    }
    catch (Exception $e) {
      $message = "Error: " . $e->getMessage() .
               "\nRequest: \n" . $this->client->__getLastRequest() .
               "\nResponse: \n" . $this->client->__getLastResponse();

      throw new RuntimeException($message, $e->getCode(), $e);
    }
  }

  /**
   * Call service method with authentication.
   */
  protected function callWithAuth($method, $parameters = array()) {
    return $this->call($method, array(
      'wsBrugerid' => $this->user,
      'wsPassword' => $this->pass,
    ) + $parameters);
  }

}
