<?php

class TingClientException extends Exception {
  public $user_message = NULL;
  private $errors = array(
    'Unsupported index',
    'Unsupported boolean modifier',
    'Invalid or unsupported use',
    'Internal problem',
  );

  public function __construct($message, $code = 0, Exception $previous = null) {
    foreach($this->errors as $val){
      if(strpos($message, $val) !== FALSE){
        $this->user_message = $val;
      }
    }
    parent::__construct($message, $code, $previous);
  }
}
