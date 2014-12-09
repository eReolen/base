<?php
/**
 * @file
 * Implementation of communicating with the Publizon API for products.
 */

class PublizonProductClient extends PublizonClient {
  /**
   * Fetch XML representation for a product at publizon.
   *
   * @param string $isbn
   *   Product id also know as ISBN number.
   *
   * @return SimpleXmlElement
   *   Raw XML object containing the product.
   */
  private function getProduct($isbn, $retailer_id = FALSE) {
    // Get default retailer id if none specified.
    $retailer_id = $retailer_id ? $retailer_id : variable_get('publizon_default_retailer', '');

    // Get product form the web-serivce.
    $response = $this->call('product', 'GetProduct', $retailer_id, array(
      'pub:ebookid' => $isbn,
    ), array('pub' => 'http://pubhub.dk/'));

    // Check if any data was returned.
    $data = $response->xpath('//data');
    if (isset($data[0])) {
      return $data[0];
    }

    $this->logger->log('The product with isbn (' . $isbn . ') did not return any data', 'WARNING');
    return FALSE;
  }

  /**
   * Get the cover URI for an ISBN number.
   *
   * @param string $isbn
   *   The ISBN number to get cover for.
   *
   * @return string
   *   URI of the cover image, or false if no image found.
   */
  public function getCoverUri($isbn) {
    try {
      $product = $this->getProduct($isbn);

      return $product->coverimage ? $product->coverimage : FALSE;
    }
    catch (Exception $e) {
      return FALSE;
    }
  }
}
