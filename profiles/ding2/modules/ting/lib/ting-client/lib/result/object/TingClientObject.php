<?php

class TingClientObject {
  public $id;
  public $data;

  /**
   * Return object type.
   **/
  public function getType() {
    return (string) $this->record['dc:type']['dkdcplus:BibDK-Type'][0];
  }
}
