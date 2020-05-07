<?php

/**
 * Get a Ting object by ID.
 *
 * Objects requests are much like search request, so this is implemented
 * as a subclass, even though it is a different request type.
 */
class TingClientObjectRequest extends TingClientRequest {
  // The string prefix used on objects with error in Opensearch versions < 5.2.
  // See $this->processResponse().
  const MISSING_OBJECT_TITLE = 'Error: unknown/missing/inaccessible record:';

  protected $agency;
  protected $allRelations;
  protected $format;
  protected $id;
  protected $localIds;
  protected $relationData;
  protected $identifiers;
  protected $profile;
  protected $outputType;
  protected $objectFormat;
  protected $fausts;

  public function setObjectFormat($objectFormat) {
    $this->objectFormat = $objectFormat;
  }

  public function getObjectFormat() {
    return $this->objectFormat;
  }

  public function setOutputType($outputType) {
    $this->outputType = $outputType;
  }

  public function getOutputType() {
    return $this->outputType;
  }

  public function getProfile() {
    return $this->profile;
  }
  public function setProfile($profile) {
    $this->profile = $profile;
  }
  public function getAgency() {
    return $this->agency;
  }

  public function setAgency($agency) {
    $this->agency = $agency;
  }

  public function getAllRelations() {
    return $this->allRelations;
  }

  public function setAllRelations($allRelations) {
    $this->allRelations = $allRelations;
  }

  public function getFormat() {
    return $this->format;
  }

  public function setFormat($format) {
    $this->format = $format;
  }

  public function getLocalIds() {
    return $this->localIds;
  }

  public function setLocalId($localId) {
    $this->localIds = array($localId);
  }

  public function setLocalIds($localIds) {
    $this->localIds = $localIds;
  }

  public function getObjectIds() {
    return $this->identifiers;
  }

  public function setObjectId($id) {
    $this->identifiers = array($id);
  }

  public function setObjectIds(array $ids) {
    $this->identifiers = $ids;
  }

  public function getRelationData() {
    return $this->relationData;
  }

  public function setRelationData($relationData) {
    $this->relationData = $relationData;
  }

  public function getRequest() {
    $parameters = $this->getParameters();

    $this->useAuth();

    // These defaults are always needed.
    $this->setParameter('action', 'getObjectRequest');

    if (!isset($parameters['format']) || empty($parameters['format'])) {
      $this->setParameter('format', 'dkabm');
    }

    // Determine which id to use.
    if ($this->identifiers) {
      $this->setParameter('identifier', $this->identifiers);
    }
    elseif ($this->localIds) {
      $this->setParameter('localIdentifier', $this->localIds);
    }

    $methodParameterMap = array(
      'format' => 'format',
      'allRelations' => 'allRelations',
      'relationData' => 'relationData',
      'agency' => 'agency',
      'profile' => 'profile',
      'outputType' => 'outputType',
      'objectFormat' => 'objectFormat',
    );

    foreach ($methodParameterMap as $method => $parameter) {
      $getter = 'get' . ucfirst($method);
      if ($value = $this->$getter()) {
        $this->setParameter($parameter, $value);
      }
    }

    return $this;
  }

  public function processResponse(stdClass $response) {
    // If search result is empty there are no objects to process and return and
    // we can safely return en empty array early.
    if (empty($response->searchResponse->result->searchResult)) {
      return array();
    }

    $search_result = &$response->searchResponse->result->searchResult;

    // Look for errors on collection objects in the response. Since we can fetch
    // multiple objects at once the best course of action is to just discard the
    // error objects, log an expection and just not return anything for this ID.
    // Then we may return an empty array, but this is the standard behavior for
    // functions returning multiple objects/entities.
    // We handle this here in TingObjectRequest since these errors are specific
    // to getObject requests. Note that we do it before passing the response to
    // TingClientSearchRequest for further processing, so we get a chance to log
    // an error. Also, we can remove the error objects from search result, so
    // that TingClientSearchRequest doesn't waste time parsing error objects
    // that we don't need anyway.
    foreach ($search_result as $index => $result) {
      $object = $result->collection->object;

      // The error element added to objects in opensearch version 5.2+ is
      // changing the result of the XML parsing: for objects with an error
      // element the object will not be an array like with "normal" objects
      // without error element, but instead the object itself. In earlier
      // versions, where the error is returned as real objects, the object
      // is still an array. So to be able to handle errors in all versions,
      // we normalize it here. There seems to be no difference in the WSDL
      // and XSD, so the new of handling errors on objects in 5.2+ must be
      // the cause of this change in data structure.
      // See: https://platform.dandigbib.org/issues/4212
      $object = is_array($object) ? reset($object) : $object;

      // In Opensearch versions < 5.2 there is no error object, but instead
      // a real object with the error message as title is returned. To
      // maintain backwards compatability we construct the error object
      // ourself if we find such an object.
      $title = isset($object->record->title[0]->{'$'}) ? $object->record->title[0]->{'$'} : '';
      if (strpos($title, self::MISSING_OBJECT_TITLE) === 0) {
        $object->error = new stdClass();
        // The title is the error message.
        $object->error->{'$'} = $title;
      }

      // This object has an error. Remove it from search result and log it.
      if (isset($object->error)) {
        unset($search_result[$index]);
        watchdog_exception('opensearch', new TingClientException('Unexpected error on object in getObject response: ' . var_export($object, TRUE)));
      }
    }    

    // Use TingClientSearchRequest::processResponse for processing the
    // response from Ting.
    $searchRequest = new TingClientSearchRequest(NULL);
    $response = $searchRequest->processResponse($response);

    // As the get object request can return more than one object we need to
    // extract them.
    $objects = array();
    foreach ($response->collections as $collection) {
      foreach ($collection->objects as $object) {
        $objects[$object->id] = $object;
      }
    }

    return $objects;
  }
}
