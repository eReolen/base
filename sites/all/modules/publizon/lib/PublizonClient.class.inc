<?php

/**
 * @file
 * The main communication object with the Publizon web-service.
 */

/**
 * TODO doc comment is empty.
 */
abstract class PublizonClient {
  /**
   * TODO missing member variable doc comment.
   *
   * @var logger
   */
  protected $logger;

  /**
   * TODO missing member variable doc comment.
   *
   * @var string
   */
  protected $baseUrl = '';

  /**
   * TODO missing member variable doc comment.
   *
   * @var array
   */
  protected $endpoints = array(
    'product' => 'getproduct.asmx',
    'product_list' => 'getproductlist.asmx',
    'loan' => 'createloan.asmx',
    'reservation' => 'reservations.asmx',
    'user' => 'validatelibraryuser.asmx',
    'libraray_list' => 'getlibrarylist.asmx',
    'library_user_order_list' => 'getlibraryuserorderlist.asmx',
    'removed_product_list' => 'getremovedproductlist.asmx',
    'loan_status' => 'getproductloanstatus.asmx',
    'checklist' => 'Checklists.asmx',
    'library_profile' => 'getlibraryinfo.asmx',
  );

  /**
   * Holds the object instance (part of the singleton pattern).
   *
   * @var array
   */
  private static $instances = array();

  /**
   * Get the singleton client.
   */
  public static function getClient() {
    $class = get_called_class();
    if (!isset(self::$instances[$class])) {
      self::$instances[$class] = new $class();
    }
    return self::$instances[$class];
  }

  /**
   * Constructor.
   *
   * Class constructor that prepares an connection to publizon and wrappers all
   * calls into this object. This is a private constructor as the object is
   * implemented as a singleton pattern, use PublizonClient::getClient() to get
   * an instance.
   */
  protected function __construct() {
    // Get publizon url.
    $publizon_url = variable_get('publizon_base_url', FALSE);
    if (!$publizon_url) {
      throw new PublizonException('Publizon client could not load publizon base url (publizon_base_url)');
    }

    // Set base URL.
    $this->baseUrl = $publizon_url;

    // Set logger.
    $this->logger = new PublizonVoidLogger();
    if (variable_get('publizon_logging', FALSE)) {
      $this->logger = new PublizonWatchDogLogger();
    }
  }

  /**
   * Call method on endpoint.
   *
   * Wrapper function for preforming of call to Publizon's web-service via the
   * NanoSOAP module.
   *
   * @param string $endpoint
   *   Index into the end-points array (defined in the top of the object).
   * @param string $action
   *   SOAP action to request.
   * @param string $retailer_id
   *   Retailer id.
   * @param array $parameters
   *   The parameters to call the actions with. Also known as the content of the
   *   message. Remember to prefix them with the namespace they should use.
   * @param array $namespace
   *   The namespaces that is used inside the SOAP message.
   *
   * @return bool|\SimpleXMLElement|string
   *   The response from the web-service.
   *
   * @throws PublizonConnectionException
   *   If the connection fails.
   * @throws PublizonException
   *   If the response dose not have a 101 status.
   */
  protected function call($endpoint, $action, $retailer_id, array $parameters, array $namespace) {
    // Get retailer information.
    $retailer = publizon_get_library($retailer_id);

    // Log request.
    $this->logger->log('Call to "' . $this->endpoints[$endpoint] . '" for "' . $action . '"');

    // Get namespace key.
    $ns = array_keys($namespace);

    // Create a new soap client for the request and set default parameters.
    $client = new PublizonNanoSOAPClient($this->baseUrl . $this->endpoints[$endpoint], array('namespaces' => $namespace));
    $parameters += array(
      $ns[0] . ':languagecode' => '',
      $ns[0] . ':clientid' => publizon_get_client_id(),
      $ns[0] . ':retailerid' => $retailer->retailer_id,
      $ns[0] . ':retailerkeycode' => md5($retailer->retailer_key_code),
    );

    // Make the request.
    try {
      $response = $client->call($ns[0] . ':' . $action, $parameters, in_array($endpoint, $this->getSoap11Endpoints()));
      // SimpleXML warns that xmlns is relative url, which it is not,
      // and SOAP 1.1 will not work with absolute. Disable the warnings.
      libxml_use_internal_errors(TRUE);
      $response = simplexml_load_string($response);
    }
    catch (Exception $e) {
      // Connection error.
      $this->logger->log('Connection with the Publizon web-service failed.');
      throw new PublizonConnectionException('Connection with the Publizon web-service failed.');
    }

    // Check for SOAP faults.
    $fault = $response->xpath('//soap:Fault');
    if (isset($fault[0])) {
      $message = $fault[0]->faultstring ?? 'Fault from Publizon web-service.';
      $this->logger->log($message);

      // Throw exception, it's translated in the exception.
      throw new PublizonException($message);
    }

    // Check the response error codes.
    $status = $response->xpath('//status');
    if (isset($status[0])) {
      if ($status[0]->code == 101) {
        return $response;
      }
      else {
        $message = $status[0]->message ?? 'Connection with the Publizon web-service failed.';
        $this->logger->log(check_plain($message));

        // Throw exception, it's translated in the exception.
        throw new PublizonException($message, intval($status[0]->code));
      }
    }
    else {
      $message = 'No status code from Publizon web-service.';
      $this->logger->log($message);

      throw new PublizonException($message);
    }

    return FALSE;
  }

  /**
   * Return array of SOAP 1.1 endpoints.
   *
   * @return array
   *   Array of names of the SOAP 1.1 endpoints.
   */
  private function getSoap11Endpoints() {
    return array(
      'reservation',
      'loan_status',
    );
  }

}

/**
 * Custom exception so the frontend receives a checked and translatable string.
 *
 * All other Exception class should use this as their base class.
 *
 * TODO Find a better solution than passing message through t function.
 */
class PublizonException extends Exception {

  /**
   * Create new constructor that ensure message is translated.
   */
  public function __construct($message, $code = 0, Exception $previous = NULL) {
    // Make sure everything is assigned properly.
    parent::__construct($message, $code, $previous);
  }

}

/**
 * Connection Exception that is used when the communication with Publizon fails.
 *
 * Mostly in the case where they are not online.
 */
class PublizonConnectionException extends PublizonException {}
