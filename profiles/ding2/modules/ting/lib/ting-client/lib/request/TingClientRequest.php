<?php

abstract class TingClientRequest {
  private $wsdlUrl;
  private $parameters = array();

  abstract public function processResponse(stdClass $response);

  abstract protected function getRequest();

  public function __construct($wsdlUrl) {
    $this->wsdlUrl = $wsdlUrl;
  }


  public function setwsdlUrl($wsdlUrl) {
    $this->wsdlUrl = $wsdlUrl;
  }

  public function setParameter($name, $value) {
    $this->parameters[$name] = $value;
  }

  public function getParameter($name) {
    return isset($this->parameters[$name]) ? $this->parameters[$name] : NULL;
  }

  // pjo removed parameter $name
  // public function setParameters($name, $array) {
  public function setParameters($array) {
    $this->parameters = array_merge($this->parameters, $array);
  }

  public function getNumResults() {
    return $this->numResults;
  }

  public function setNumResults($numResults) {
    $this->numResults = $numResults;
  }

  public function getWsdlUrl() {
    return $this->wsdlUrl;
  }

  public function getParameters() {
    return $this->parameters;
  }

  public function execute(TingClientRequestAdapter $adapter) {
    return $adapter->execute($this->getRequest());
  }

  public function parseResponse($response) {
    if ($this->getRequest() instanceof TingFulltextRequest) {
      // Objectify response since processResponse() awaiting stdClass.
      return $this->processResponse((object) $response);
    }

    if (!$response) {
      throw new TingClientException('Unable to decode response as JSON: ' . print_r($response, TRUE));
    }

    if (!is_object($response)) {
      throw new TingClientException('Unexpected JSON response: ' . var_export($response, TRUE));
    }

    // Find error messages in the response - data well v3. The data well return
    // objects with only title elements that contains an error message (not the
    // title), but the hit count is zero on these error objects. I may have
    // been fixed on later version of the data well (3.0+), but it have to be
    // tested.
    if (!empty($response->searchResponse->result->hitCount)) {
      if (!empty($response->searchResponse->result->searchResult)) {
        $search_result = $response->searchResponse->result->searchResult;
        foreach ($search_result as $result) {
          foreach ($result->collection->object as $object) {
            if (isset($object->error)) {
              throw new TingClientException('Unexpected error message in response: ' . var_export($response, TRUE));
            }
          }
        }
      }
    }

    return $this->processResponse($response);
  }

  protected static function getValue($object) {
    if (is_array($object)) {
      return array_map(array('RestJsonTingClientRequest', 'getValue'), $object);
    }
    else {
      return self::getBadgerFishValue($object, '$');
    }
  }

  protected static function getAttributeValue($object, $attributeName) {
    $attribute = self::getAttribute($object, $attributeName);
    if (is_array($attribute)) {
      return array_map(array('RestJsonTingClientRequest', 'getValue'), $attribute);
    }
    else {
      return self::getValue($attribute);
    }
  }

  protected static function getAttribute($object, $attributeName) {
    //ensure that attribute names are prefixed with @
    $attributeName = ($attributeName[0] != '@') ? '@'.$attributeName : $attributeName;
    return self::getBadgerFishValue($object, $attributeName);
  }

  protected static function getNamespace($object) {
    return self::getBadgerFishValue($object, '@');
  }

  /**
   * Helper to reach JSON BadgerFish values with tricky attribute names.
   */
  protected static function getBadgerFishValue($badgerFishObject, $valueName) {
    $properties = get_object_vars($badgerFishObject);
    if (isset($properties[$valueName])) {
      $value = $properties[$valueName];
      if (is_string($value)) {
        //some values contain html entities - decode these
        $value = html_entity_decode($value, ENT_COMPAT, 'UTF-8');
      }

      return $value;
    }
    else {
      return NULL;
    }
  }

}

