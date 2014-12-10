<?php
/**
 * @file
 * Implementation of communicating with the Publizon API for loans.
 */

class PublizonLoanClient extends PublizonClient {
  /**
   * Create a loan.
   *
   * Create a new loan at Publizon. It throws an exception if the loan is not
   * successfull, otherwise the retailer orderno and internal orderno is
   * returned.
   *
   * @param string $retailer_id
   *   The id of the retailer to loan for.
   * @param string $card_number
   *   The users card number/CPR also known as login id.
   * @param string $pincode
   *   The users login pin code.
   * @param string $isbn
   *   ISBN number on the product.
   *
   * @return array
   *   Array containing the retailer and internal order numbers.
   *
   * @throws PublizonException
   */
  public function createLoan($retailer_id, $card_number, $pincode, $isbn) {
    // Call the webservice, throwing exception on failure.
    $response = $this->call('loan', 'CreateLoan', $retailer_id, array(
      'pub:ebookid' => $isbn,
      'pub:cardnumber' => $card_number,
      'pub:pincode' => $pincode,
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
   * @param string $card_number
   *   User card_number/CPR also known as login id.
   *
   * @return bool
   *   Returns an array of PublizonLoan objects.
   *
   * @throws PublizonException
   */
  public function getLibraryUserOrderList($retailer_id, $card_number) {
    // Make request to the web-service for the loans.
    $response = $this->call('library_user_order_list', 'GetLibraryUserOrderList', $retailer_id, array(
      'pub:cardnumber' => $card_number,
    ), array('pub' => 'http://pubhub.dk/'));

    // Check if any data was returned.
    $data = $response->xpath('//data/orderitem');
    $loans = array();
    if (isset($data[0])) {
      while (list(, $loan) = each($data)) {
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
   *   ISBN number on the product.
   *
   * @return PublizonLoan
   *   Returns the loan, or FALSE if no loan exists.
   *
   * @throws PublizonException
   */
  public function getLibraryUserOrder($retailer_id, $card_number, $isbn) {
    // Make request to the web-service for the loans.
    $response = $this->call('library_user_order_list', 'GetLibraryUserOrder', $retailer_id, array(
      'pub:cardnumber' => $card_number,
      'pub:ebookid' => $isbn,
    ), array('pub' => 'http://pubhub.dk/'));

    // Check if any data was returned.
    $data = $response->xpath('//data/orderitem');
    if (isset($data[0])) {
      while (list(, $loan) = each($data)) {
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
   * @param string $card_number
   *   The users card number/CPR also known as login id.
   * @param array $isbns
   *   ISBN numbers on the products.
   *
   * @return array
   *   Array of PublizonLoanStatus objects.
   *
   * @throws PublizonException
   */
  public function getProductLoanStatusList($retailer_id, $card_number, $isbns) {
    // Make request to the web-service for the status.
    $response = $this->call('loan_status', 'GetProductLoanStatusList', $retailer_id, array(
      'pub:cardnumber' => $card_number,
      'pub:ebookids' => array(
        'pub:ebookid' => $isbns,
      ),
    ), array('pub' => 'http://pubhub.dk/'));

    // Check if any data was returned.
    $data = $response->xpath('//data/productloanstatus');
    $status = array();
    if (isset($data[0])) {
      while (list(, $stat) = each($data)) {
        $status[] = new PublizonLoanStatus($stat);
      }
    }
    return $status;
  }
}
