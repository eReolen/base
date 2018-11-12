<?php

class TingFulltextRequest extends TingClientObjectRequest {
  public function processResponse(stdClass $response) {
    return $response;
  }
}
