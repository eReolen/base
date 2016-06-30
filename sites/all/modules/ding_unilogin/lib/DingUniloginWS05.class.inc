<?php

/**
 * @file
 * Class for communicating with the WS05 service at Unilogin.
 */

/**
 * Class for the authorization service.
 */
class DingUniloginWS05 extends DingUniloginServiceBase {
  const WSDLURL = 'https://ws05.infotjeneste.uni-c.dk/infotjenesteautorisation-ws/ws?WSDL';

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
    return (bool) $this->callWithAuth('harBrugerLicens', array(
      'kontekst' => $context,
      'projektid' => $project,
      'brugerid' => $id,
    ));
  }

}
