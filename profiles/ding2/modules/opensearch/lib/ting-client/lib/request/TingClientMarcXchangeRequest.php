<?php
/**
 * @file
 * TingClientMarcXchnageRequest class.
 */

class TingClientMarcXchangeRequest extends TingClientRequest {
  protected $agency;
  protected $profile;
  protected $identifier;

  /**
   * Set agency.
   *
   * @param string $agency
   *   Well agency identifier.
   */
  public function setAgency($agency) {
    $this->agency = $agency;
  }

  /**
   * Set profile.
   *
   * @param string $profile
   *   Well profile name.
   */
  public function setProfile($profile) {
    $this->profile = $profile;
  }

  /**
   * Set Ting object ID.
   *
   * @param string $id
   *   Ting object ID.
   */
  public function setIdentifier($id) {
    $this->identifier = $id;
  }

  /**
   * {@inheritdoc}
   */
  public function getRequest() {
    $this->useAuth();

    // Hardcoded defaults.
    $this->setParameter('action', 'getObjectRequest');
    $this->setParameter('outputType', 'json');
    $this->setParameter('objectFormat', 'marcxchange');

    // Library settings.
    $this->setParameter('agency', $this->agency);
    $this->setParameter('profile', $this->profile);

    // Object ID (agency:faust).
    $this->setParameter('identifier', $this->identifier);

    return $this;
  }

  /**
   * {@inheritdoc}
   */
  public function processResponse(stdClass $response) {
    return new TingMarcResult($response);
  }

}
