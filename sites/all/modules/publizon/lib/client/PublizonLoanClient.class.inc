<?php

/**
 * @file
 * Implementation of communicating with the Publizon API for loans.
 */

/**
 * TODO doc comment is empty.
 */
class PublizonLoanClient extends PublizonClient {

  /**
   * Create a loan.
   *
   * Create a new loan at Publizon. It throws an exception if the loan is not
   * successful, otherwise the retailer order no and internal order no is
   * returned.
   *
   * @param string $retailer_id
   *   The id of the retailer to loan for.
   * @param string $card_number
   *   The users card number/CPR also known as login id.
   * @param ?string $pincode
   *   The users login pin code.
   * @param string $isbn
   *   ISBN on the product.
   * @param string|null $institution_id
   *   The user's institution id.
   *
   * @return array
   *   Array containing the retailer and internal order numbers.
   *
   * @throws \PublizonConnectionException
   * @throws \PublizonException
   */
  public function createLoan(string $retailer_id, string $card_number, ?string $pincode, string $isbn, string $institution_id = NULL): array {
    // Call the webservice, throwing exception on failure.
    $response = $this->call('loan', 'CreateLoan', $retailer_id, array(
      'pub:ebookid' => $isbn,
      'pub:cardnumber' => $card_number,
      'pub:pincode' => $pincode,
      'pub:institutionid' => $institution_id,
      'pub:format' => '',
      'pub:mobipocketid' => '',
    ), array('pub' => 'pubhub.dk'));

    // Parse returned data.
    $data = $response->xpath('//data');
    if (isset($data[0])) {
      $data = $data[0];
      return array(
        'retailer' => (string) $data->retailerordernumber,
        'internal' => (string) $data->internalordernumber,
      );
    }

    // Data was malformed.
    $this->logger->log('Create loan request returned no data (' . $isbn . ').', 'ERROR');
    throw new PublizonException('Create loan request returned no data (' . $isbn . ').');
  }

  /**
   * Retrieves information about the user loans stored at Publizon.
   *
   * @param string $retailer_id
   *   Retailer id.
   * @param string $card_number
   *   User card_number/CPR also known as login id.
   *
   * @return array
   *   Returns an array of PublizonLoan objects.
   *
   * @throws \PublizonConnectionException
   * @throws \PublizonException
   */
  public function getLibraryUserOrderList(string $retailer_id, string $card_number): array {
    // Make request to the web-service for the loans.
    $response = $this->call('library_user_order_list', 'GetLibraryUserOrderList', $retailer_id, array(
      'pub:cardnumber' => $card_number,
    ), array('pub' => 'http://pubhub.dk/'));

    // Check if any data was returned.
    $data = $response->xpath('//data/orderitem');
    $loans = array();
    if (isset($data[0])) {
      foreach ($data as $loan) {
        $loans[] = new PublizonLoan($loan);
      }
    }

    return $loans;
  }

  /**
   * Get a users loan for an isbn.
   *
   * @param string $retailer_id
   *   The id of the retailer to get loan for.
   * @param string $card_number
   *   The users card number/CPR also known as login id.
   * @param string $isbn
   *   ISBN on the product.
   *
   * @return PublizonLoan|bool
   *   Returns the loan, or FALSE if no loan exists.
   *
   * @throws PublizonException
   */
  public function getLibraryUserOrder(string $retailer_id, string $card_number, string $isbn) {
    // Make request to the web-service for the loans.
    $response = $this->call('library_user_order_list', 'GetLibraryUserOrder', $retailer_id, array(
      'pub:cardnumber' => $card_number,
      'pub:ebookid' => $isbn,
    ), array('pub' => 'http://pubhub.dk/'));

    // Check if any data was returned.
    $data = $response->xpath('//data/orderitem');
    if (isset($data[0])) {
      foreach ($data as $loan) {
        return new PublizonLoan($loan);
      }
    }

    return FALSE;
  }

  /**
   * Get the status of a loan for a number of products.
   *
   * @param string $retailer_id
   *   The id of the retailer to get status for.
   * @param array $isbns
   *   ISBNs on the products.
   * @param string|null $card_number
   *   The users card number/CPR also known as login id.
   *
   * @return array
   *   Array of PublizonLoanStatus objects.
   *
   * @throws PublizonException
   */
  public function getProductLoanStatusList(string $retailer_id, array $isbns, string $card_number = NULL): array {
    // Make request to the web-service for the status.
    $request = array(
      'pub:ebookids' => array(
        'pub:ebookid' => $isbns,
      ),
    );
    if ($card_number) {
      $request['pub:cardnumber'] = $card_number;
    }

    $response = $this->call('loan_status', 'GetProductLoanStatusList', $retailer_id, $request, array('pub' => 'http://pubhub.dk/'));

    // Check if any data was returned.
    $data = $response->xpath('//data/productloanstatus');
    $status = array();
    if (isset($data[0])) {
      foreach ($data as $stat) {
        $status[] = new PublizonLoanStatus($stat);
      }
    }
    return $status;
  }

}
