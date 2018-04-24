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
  protected $authService;
  protected $userService;
  protected $institutionService;
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
   * Get authorization service.
   *
   * @return DingUniloginWSIautor
   *   The authorization service.
   */
  protected function getAuthService() {
    if (!$this->authService) {
      $this->authService = new DingUniloginWSIautor($this->wsuser, $this->wspass);
    }

    return $this->authService;
  }

  /**
   * Get user service.
   *
   * @return DingUniloginWSIbruger
   *   The user service.
   */
  protected function getUserService() {
    if (!$this->userService) {
      $this->userService = new DingUniloginWSIbruger($this->wsuser, $this->wspass);
    }

    return $this->userService;
  }

  /**
   * Get instution service.
   *
   * @return DingUniloginWSIinst
   *   The instution service.
   */
  protected function getInstitutionService() {
    if (!$this->institutionService) {
      $this->institutionService = new DingUniloginWSIinst($this->wsuser, $this->wspass);
    }

    return $this->institutionService;
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
   * Get the municipality IDs of the users institutions.
   *
   * @return array
   *   Municipality ids.
   */
  public function getInstitutionMunicipalities() {
    $municipality_ids = array();

    $institutions = $this->getUserService()->getUserInstitutions($this->name);
    foreach ($institutions as $institution_id) {
      $institution = $this->getInstitutionService()->getInstitution($institution_id);
      if (isset($institution->kommunenr)) {
        $municipality_ids[] = $institution->kommunenr;
      }
    }

    return $municipality_ids;
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
