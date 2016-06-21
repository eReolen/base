<?php

/**
 * @file
 * Base class for classes communicating with the Unilogin services.
 */

class ServiceBase {
  protected $client;

  public function __construct() {
    $this->client = new SoapClient($this::WSDLURL, array('trace' => TRUE));
  }

  function call($method, $parameters = array()) {
    try {
      return $this->client->{$method}($parameters);
    }
    catch (Exception $e) {
      print "Error: \n";
      print "Request: \n";
      print $this->client->__getLastRequest();
      print "Response: \n";
      print $this->client->__getLastResponse();
    }
  }
}
