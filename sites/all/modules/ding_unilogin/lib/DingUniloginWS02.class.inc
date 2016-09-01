<?php

/**
 * @file
 * Class for communicating with the WS02 service at Unilogin.
 */

/**
 * Class for the information service.
 */
class DingUniloginWS02 extends DingUniloginServiceBase {
  const WSDLURL = 'https://ws02ovm.infotjeneste.uni-c.dk/infotjeneste-ws/ws?WSDL';

  /**
   * Lookup a person.
   */
  public function getPerson($person_id) {
    return $this->callWithAuth('hentPerson', array(
      'brugerid' => $person_id,
    ));
  }

  /**
   * Lookup a student.
   */
  public function getStudent($institution_id, $person_id) {
    return $this->callWithAuth('hentElev', array(
      'instnr' => $institution_id,
      'uid' => $person_id,
    ));
  }

  /**
   * Lookup institution.
   */
  public function getInstitution($institution_id) {
    return $this->callWithAuth('hentInstitution', array(
      'instid' => $institution_id,
    ));
  }

}
