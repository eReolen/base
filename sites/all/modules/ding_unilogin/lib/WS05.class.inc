<?php

/**
 * @file
 * Class for communicating with the WS05 service at Unilogin.
 */

class UniloginWS05 extends ServiceBase {
  const WSDLURL = 'https://ws05.infotjeneste.uni-c.dk/infotjenesteautorisation-ws/ws?WSDL';

  function getLicenses($id) {
    return $this->call('hentBrugerLicenser', array(
      'wsBrugerid' => 'ereolen',
      'wsPassword' => 'mDsbp2ha8zv2',
      'brugerid' => $id,
    ));
  }
}
