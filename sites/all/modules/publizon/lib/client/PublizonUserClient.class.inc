<?php

/**
 * @file
 * Implementation of communicating with the Publizon API for users.
 */

/**
 * User client class.
 */
class PublizonUserClient extends PublizonClient {

  /**
   * Get support ID for the user.
   *
   * @param $card_number
   *   The users card number/GUID/cpr.
   * @param $retailer_id
   *   The retailer id that belongs to the user.
   *
   * @return bool|string
   *   FALSE if not found else the support id.
   *
   * @throws \Exception
   */
  public function getSupportId($card_number, $retailer_id) {
    $arguments = array(
      'pub:cardnumber' => $card_number,
    );

    $support_id = NULL;
    // Call the webservice, throwing exception on failure.
    try {
      $response = $this->call('get_friendly_cardnumber', 'GetFriendlyCardnumber', $retailer_id, $arguments, array('pub' => 'http://pubhub.dk/'));

      // Extract friendly card number.
      $friendly_elements = $response->xpath('//data/FriendlyCardNumber');
      if (isset($friendly_elements[0])) {
        $support_id = (string) $friendly_elements[0];
      }
    }
      // On exception, we are not logged in.
    catch (PublizonException $e) {
      $this->logger->log($e->getMessage(), 'ERROR');
      return FALSE;
    }

    // If we end up here, we are logged in. Return support_id if it's not
    // empty.
    return empty($support_id) ? TRUE : $support_id;
  }

  /**
   * Validate a library user.
   *
   * Validates that a given user is allowed to login to the publizon web-service.
   *
   * @param string $card_number
   *   User card_number/CPR/UNI•Login id also known as login id.
   * @param string $pincode
   *   The users pin code. Null for UNI•Login users.
   * @param string $retailer_id
   *   The retailer's id.
   *
   * @return bool|string|null
   *   FALSE if the user is invalid, TRUE or their friendly card number
   *   otherwise.
   *
   * @throws \Exception
   *
   * @deprecated removed in publizon API version 2.6.
   */
  public function validateLibraryUser($card_number, $pincode, $retailer_id) {
    $arguments = array(
      'pub:cardnumber' => $card_number,
    );

    if (!is_null($pincode)) {
      $arguments['pub:pincode'] = $pincode;
    }

    $support_id = NULL;
    // Call the webservice, throwing exception on failure.
    try {
      $response = $this->call('user', 'ValidateLibraryUser', $retailer_id, $arguments, array('pub' => 'http://pubhub.dk/'));

      // Extract friendly card number.
      $friendly_elements = $response->xpath('//data/friendlycardnumber');
      if (isset($friendly_elements[0])) {
        $support_id = (string) $friendly_elements[0];
      }
    }
    // On exception, we are not logged in.
    catch (PublizonException $e) {
      $this->logger->log($e->getMessage(), 'ERROR');
      return FALSE;
    }

    // If we end up here, we are logged in. Return support_id if it's not
    // empty.
    return empty($support_id) ? TRUE : $support_id;
  }

}
