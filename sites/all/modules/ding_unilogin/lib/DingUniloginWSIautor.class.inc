<?php

/**
 * @file
 * Class for communicating with the WS05 service at Unilogin.
 */

/**
 * Class for the authorization service.
 */
class DingUniloginWSIautor extends DingUniloginServiceBase {
  const WSDLURL = 'https://wsiautor.uni-login.dk/wsiautor-v3/ws?WSDL';

  /**
   * Soap version to use.
   *
   * This service is Soap 1.2. We get an "Unsupported Media Type" if using 1.1.
   */
  protected $soapVersion = SOAP_1_2;

  /**
   * Get all licenses for a user.
   */
  public function getLicenses($id) {
    return $this->callWithAuth('hentBrugerLicenser', array(
      'brugerid' => $id,
    ));
  }

  /**
   * Check if user has a license for a project.
   */
  public function hasLicense($id, $context, $project) {
    $parameters = array(
      'brugerid' => $id,
      'udbydernr' => $context,
      'tjenestekode' => $project,
    );
    $res = $this->callWithAuth('harBrugerLicens', $parameters, 'harLicens');
    return (bool) $res;
  }

}
