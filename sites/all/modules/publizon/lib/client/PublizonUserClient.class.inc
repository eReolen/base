<?php
/**
 * @file
 * Implementation of communicating with the Publizon API for users.
 */

class PublizonUserClient extends PublizonClient {
  /**
   * Validata a library user.
   *
   * Validates that a given user is allowed to login to the publizon
   * web-service.
   *
   * @param string $card_number
   *   User card_number/CPR/UNI•Login id also known as login id.
   * @param string $pincode
   *   The users pin code. Null for UNI•Login users.
   *
   * @return bool
   *   If the user is valid TRUE is return else FALSE.
   */
  public function validateLibraryUser($card_number, $pincode, $retailer_id) {
    $arguments = array(
      'pub:cardnumber' => $card_number,
    );

    if (!is_null($pincode)) {
      $arguments['pub:pincode'] = $pincode;
    }
    // Call the webservice, throwing exception on failure.
    try {
      $response = $this->call('user', 'ValidateLibraryUser', $retailer_id, $arguments, array('pub' => 'http://pubhub.dk/'));
    }
    // On exception we are not logged in.
    catch (PublizonException $e) {
      $this->logger->log($e->getMessage(), 'ERROR');
      return FALSE;
    }

    // If we end up here, we are logged in.
    return TRUE;
  }
}
