<?php

/**
 * @file
 * Implementation of communicating with the Publizon API for reservations.
 */

class PublizonReservationClient extends PublizonClient {

  /**
   * Create a reservation.
   *
   * Create a new reservation at Publizon. It throws an exception if the
   * reservation is not successfull, otherwise TRUE is returned.
   *
   * @param string $retailer_id
   *   The id of the retailer to reserve for.
   * @param string $card_number
   *   The users card number/CPR also known as login id.
   * @param ?string $pincode
   *   The users login pin code.
   * @param string $isbn
   *   ISBN on the product.
   * @param string $email
   *   Optional email to send notification to when title is available.
   * @param string $phone
   *   Optional phone number to send notification to when title is available.
   * @param array $institution_tags
   *   Tags from login
   *
   * @return bool
   *   TRUE on success.
   *
   * @throws \PublizonConnectionException
   * @throws \PublizonException
   */
  public function createReservation(string $retailer_id, string $card_number, ?string $pincode, string $isbn, string $email = '', string $phone = '', array $institution_tags = array()): bool {
    // Call the webservice, throwing exception on failure.
    $response = $this->call('reservation', 'Create', $retailer_id, array(
      'pub:ebookid' => $isbn,
      'pub:cardnumber' => $card_number,
      'pub:pincode' => $pincode,
      'pub:email' => $email,
      'pub:phonenumber' => $phone,
      'pub:institutionTags' => array(
        'pub:string' => $institution_tags
      ),
    ), array('pub' => 'http://pubhub.dk/'));

    // Parse returned data.
    $data = $response->xpath('//data');
    if (isset($data[0]) && $data[0][0] == $card_number) {
      return TRUE;
    }

    // Data was malformed.
    $this->logger->log('Create reservation request returned no/invalid data (' . $isbn . ').', 'ERROR');
    throw new PublizonException('Create reservation request returned no/invalid data (' . $isbn . ').');
  }

  /**
   * Get the reservations of a user.
   *
   * @param string $retailer_id
   *   The id of the retailer.
   * @param string $card_number
   *   The card number to get list for.
   *
   * @return array
   *   Array of PublizonReservation objects.
   *
   * @throws \PublizonConnectionException
   * @throws \PublizonException
   */
  public function listReservations(string $retailer_id, string $card_number): array {
    // Call the webservice, throwing exception on failure.
    $response = $this->call('reservation', 'List', $retailer_id, array(
      'pub:cardnumber' => $card_number,
    ), array('pub' => 'http://pubhub.dk/'));

    // Parse returned data.
    $data = $response->xpath('//data/reservation');
    $reservations = array();
    if (isset($data[0])) {
      foreach ($data as $reservation) {
        $reservations[] = new PublizonReservation($reservation);
      }
    }

    return $reservations;
  }

  /**
   * Delete a reservation.
   *
   * Delete a reservation for a title at Publizon. It throws an exception on
   * any error, or returns TRUE.
   *
   * @param string $retailer_id
   *   The id of the retailer to delete for.
   * @param string $card_number
   *   The users card number/CPR also known as login id.
   * @param string $isbn
   *   ISBN on the product.
   *
   * @return bool
   *   TRUE on success.
   *
   * @throws \PublizonConnectionException
   * @throws \PublizonException
   */
  public function deleteReservation(string $retailer_id, string $card_number, string $isbn): bool {
    // Call the webservice, throwing exception on failure.
    $response = $this->call('reservation', 'Delete', $retailer_id, array(
      'pub:cardnumber' => $card_number,
      'pub:ebookid' => $isbn,
    ), array('pub' => 'http://pubhub.dk/'));

    // Parse returned data.
    $data = $response->xpath('//data');
    if (isset($data[0]) && $data[0][0] == $card_number) {
      return TRUE;
    }

    // Data was malformed.
    $this->logger->log('Create reservation request returned no/invalid data (' . $isbn . ').', 'ERROR');
    throw new PublizonException('Create reservation request returned no/invalid data (' . $isbn . ').');
  }

}
