<?php

class TingClientRequestAdapter {
  /**
   * @var TingClientLogger
   */
  protected $logger;

  /**
   * Default constructor for the class.
   *
   * @todo: Why is the options parameter here?
   *
   * @param array $options
   *   Array of options that is not used.
   */
  public function __construct($options = array()) {
    $this->logger = new TingClientVoidLogger();
  }

  /**
   * Set the type of logger to used.
   *
   * If this method is not called the object defaults to void logger.
   *
   * @param TingClientLogger $logger
   *   A logger to set for this object.
   */
  public function setLogger(TingClientLogger $logger) {
    $this->logger = $logger;
  }

  /**
   * Execute request against the data well.
   *
   * @param TingClientRequest $request
   *
   * @return mixed|string
   * @throws Exception
   * @throws TingClientException
   */
  public function execute(TingClientRequest $request) {
    //Prepare the parameters for the SOAP request
    $soapParameters = $request->getParameters();

    // Separate the action from other parameters
    $soapAction = $soapParameters['action'];
    unset($soapParameters['action']);

    // We use JSON as the default outputType.
    if (!isset($soapParameters['outputType'])) {
      $soapParameters['outputType'] = 'json';
    }

    try {
      try {
        $startTime = explode(' ', microtime());

        // Add option to send CURL parameters with the request. This can be used
        // to send requests through a SOCKS5 ssh proxy.
        $curl_options = array();
        if (function_exists('variable_get')) {
          $curl_options = variable_get('curl_options');
        }

        $client = new NanoSOAPClient($request->getWsdlUrl(), array('curl' => $curl_options));
        $response = $client->call($soapAction, $soapParameters);

        $stopTime = explode(' ', microtime());
        $time = floatval(($stopTime[1]+$stopTime[0]) - ($startTime[1]+$startTime[0]));

        $this->logger->log('Completed SOAP request ' . $soapAction . ' ' . $request->getWsdlUrl() . ' (' . round($time, 3) . 's). Request body: ' . $client->requestBodyString . ' Response: ' . $response);

        // If using JSON and DKABM, we help parse it.
        if ($soapParameters['outputType'] == 'json') {
          return json_decode($response);
        }
        else {
          return $response;
        }
      } catch (NanoSOAPcURLException $e) {
        //Convert NanoSOAP exceptions to TingClientExceptions as callers
        //should not deal with protocol details
        throw new TingClientException($e->getMessage(), $e->getCode());
      }
    } catch (TingClientException $e) {
      $this->logger->log('Error handling SOAP request ' . $soapAction . ' ' . $request->getWsdlUrl() .': '. $e->getMessage());
      throw $e;
    }
  }
}
