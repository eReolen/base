<?php

/**
 * @file
 * Class representing a UNI•Login user.
 */

/**
 * Represents a UNI•Login user.
 */
class DingUniloginUser {
  protected $name;
  protected $authname;
  protected $infoService;
  protected $authService;
  protected $profileData = array();
  protected $wsuser;
  protected $wspass;

  /**
   * Constructor.
   *
   * @param string $username
   *   The username of the user. Also default authname.
   * @param string $wsuser
   *   Username for the UNI•Login webservices.
   * @param string $wspass
   *   Password for the UNI•Login webservices.
   */
  public function __construct($username, $wsuser, $wspass) {
    $this->name = $username;
    // Authname defaults to same as username.
    $this->authname = $username;
    $this->wsuser = $wsuser;
    $this->wspass = $wspass;
  }

  /**
   * Get information service.
   *
   * @return DingUniloginWS02
   *   The information service.
   */
  protected function getInfoService() {
    if (!$this->infoService) {
      $this->infoService = new DingUniloginWS02($this->wsuser, $this->wspass);
    }

    return $this->infoService;
  }

  /**
   * Get authorization service.
   *
   * @return DingUniloginWS05
   *   The authorization service.
   */
  protected function getAuthService() {
    if (!$this->authService) {
      $this->authService = new DingUniloginWS05($this->wsuser, $this->wspass);
    }

    return $this->authService;
  }

  /**
   * Get user name.
   */
  public function getName() {
    return $this->name;
  }

  /**
   * Get authname.
   */
  public function getAuthName() {
    return $this->authname;
  }

  /**
   * Set authname.
   */
  public function setAuthName($name) {
    $this->authname = $name;
  }

  /**
   * Provide data for the users profile.
   *
   * @param string $field
   *   Name of the profile property.
   * @param mixed $value
   *   The value to set it to.
   */
  public function setProfileData($field, $value) {
    $this->profileData[$field] = $value;
  }

  /**
   * Get profile data.
   *
   * @return array
   *   Array of property => vaule pairs.
   */
  public function getProfileData() {
    return $this->profileData;
  }

  /**
   * Get the municipality of the users institution.
   */
  public function getInstitutionMunicipality() {
    $person = $this->getInfoService()->getPerson($this->name);
    if ($person) {
      $institution = $this->getInfoService()->getInstitution($person->Instnr);
      if ($institution) {
        return $institution->Kommunenr;
      }
    }

    return FALSE;
  }

  /**
   * Check if user has been given a particular license.
   *
   * @param string $context
   *   Context to check.
   * @param string $project
   *   Project to check.
   */
  public function hasLicense($context, $project) {
    return $this->getAuthService()
      ->hasLicense($this->name, $context, $project);
  }

}
