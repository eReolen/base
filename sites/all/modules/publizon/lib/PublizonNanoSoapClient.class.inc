<?php

/**
 * @file
 * The communication client to use with the Publizon client.
 */

/**
 * Implementation of the communication object based on NanoSOAPClient object.
 */
class PublizonNanoSOAPClient extends NanoSOAPClient {

  /**
   * Default constructor.
   */
  public function __construct($endpoint, $options = array()) {
    parent::__construct($endpoint, $options);
  }

  /**
   * Make a SOAP request.
   *
   * Modified this version to new set a SOAP action header as publizon's service
   * don't link that.
   *
   * @param string $action
   *   The method/action to be called.
   * @param array $parameters
   *   The parameters to send with the SOAP request.
   * @param bool $soap11
   *   Whether the endpoint is SOAP 1.1.
   *
   * @return string
   *   The SOAP response.
   */
  public function call($action, $parameters = array(), $soap11 = TRUE) {
    // Set content type and send the SOAP action as a header.
    $headers = array(
      'Content-Type: text/xml',
    );

    // For SOAP 1.1 we need to include SOAPAction header.
    if ($soap11) {
      list($action_ns, $action_txt) = explode(':', $action, 2);
      $headers[] = 'SOAPAction: ' . trim($this->namespaces[$action_ns], '/') . '/' . $action_txt;
    }

    // Make a DOM document from the envelope and get the Body tag so we
    // can add our request data to it.
    $this->doc = new DOMDocument();
    $this->doc->loadXML($this->generateSOAPenvelope());
    $body = $this->doc->getElementsByTagName('Body')->item(0);

    // Convert the parameters into XML elements and add them to the
    // body. The root element of this structure will be the action.
    $elem = $this->convertParameter($action, $parameters);
    $body->appendChild($elem);

    // Render and store the final request string.
    $this->requestBodyString = $this->doc->saveXML();

    // Send the SOAP request to the server via CURL.
    return $this->curlRequest($this->endpoint, 'POST', $this->requestBodyString, $headers);
  }

}
