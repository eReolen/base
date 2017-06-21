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
    $options = array(
      // Set trace so we can pull out request/response in case of error.
      'trace' => TRUE,
      // We get an "Unsupported Media Type" on the new WSIautor service if using
      // 1.1.
      'soap_version' => SOAP_1_2,
    );
    $this->client = new SoapClient($this::WSDLURL, $options);
    $this->user = $user;
    $this->pass = $pass;
  }

  /**
   * Call service method.
   */
  protected function call($method, $parameters = array(), $returnProperty = 'return') {
    try {
      $res = $this->client->{$method}($parameters);
      return isset($res->{$returnProperty}) ? $res->{$returnProperty} : NULL;
    }
    catch (Exception $e) {
      // Catch error and throw a new one which includes request and response.
      $message = "Error: " . $e->getMessage() .
               "\nRequest: \n" . $this->client->__getLastRequest() .
               "\nResponse: \n" . $this->client->__getLastResponse();

      throw new RuntimeException($message, $e->getCode(), $e);
    }
  }

  /**
   * Call service method with authentication.
   */
  protected function callWithAuth($method, $parameters = array(), $returnProperty = 'return') {
    return $this->call($method, array(
      'wsBrugerid' => $this->user,
      'wsPassword' => $this->pass,
    ) + $parameters, $returnProperty);
  }

}
