<?php

/**
 * @file
 * Class for communicating with the ws71/wsiBRUGER service at Unilogin.
 */

/**
 * Class for the user information service.
 */
class DingUniloginWSIbruger extends DingUniloginServiceBase {
  const WSDLURL = 'https://wsibruger.uni-login.dk/wsibruger-v3/ws?WSDL';

  /**
   * Get user institutions.
   *
   * @return array
   *   Institution ids.
   */
  public function getUserInstitutions($id) {
    $parameters = array(
      'brugerid' => $id,
    );
    $res = $this->callWithAuth('hentBrugersInstitutionsTilknytninger', $parameters, 'institutionstilknytning');

    $institutions = array();
    foreach ($this->ensureArray($res) as $inst) {
      $institutions[] = $inst->instnr;
    }
    return $institutions;
  }

}
