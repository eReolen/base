<?php

/**
 * @file
 * Class for communicating with the WS02 service at Unilogin.
 */

class UniloginWS02 extends ServiceBase {
  const WSDLURL = 'https://ws02.infotjeneste.uni-c.dk/infotjeneste-ws/ws?WSDL';


  function getPerson($id) {
    return $this->call('hentPerson', array(
      'wsBrugerid' => 'ereolen',
      'wsPassword' => 'mDsbp2ha8zv2',
      'brugerid' => $id,
    ));
  }
}
