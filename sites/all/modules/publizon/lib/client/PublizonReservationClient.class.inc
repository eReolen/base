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
   * @param string $pincode
   *   The users login pin code.
   * @param string $isbn
   *   ISBN number on the product.
   * @param string $email
   *   Optional email to send notification to when title is available.
   * @param string $phone
   *   Optional phone number to send notification to when title is available.
   *
   * @return bool
   *   TRUE on success.
   *
   * @throws PublizonException
   */
  public function createReservation($retailer_id, $card_number, $pincode, $isbn, $email = '', $phone = '') {
    // Call the webservice, throwing exception on failure.
    $response = $this->call('reservation', 'Create', $retailer_id, array(
      'pub:ebookid' => $isbn,
      'pub:cardnumber' => $card_number,
      'pub:pincode' => $pincode,
      'pub:email' => $email,
      'pub:phonenumber' => $phone,
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
   */
  public function listReservations($retailer_id, $card_number) {
    // Call the webservice, throwing exception on failure.
    $response = $this->call('reservation', 'List', $retailer_id, array(
      'pub:cardnumber' => $card_number,
    ), array('pub' => 'http://pubhub.dk/'));

    // Parse returned data.
    $data = $response->xpath('//data/reservation');
    $reservations = array();
    if (isset($data[0])) {
      while (list(, $reservation) = each($data)) {
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
   *   ISBN number on the product.
   *
   * @return bool
   *   TRUE on success.
   *
   * @throws PublizonException
   */
  public function deleteReservation($retailer_id, $card_number, $isbn) {
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
