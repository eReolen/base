<?php

/**
 * @file
 * Implementation of communicating with the Publizon API for products.
 */

/**
 * TODO doc comment is empty.
 */
class PublizonProductClient extends PublizonClient {

  /**
   * Fetch XML representation for a product at publizon.
   *
   * @param string $isbn
   *   Product id also known as ISBN.
   * @param bool $retailer_id
   *   Product id also known as ISBN.
   *
   * @return false|\PublizonProduct
   *   The publizon product.
   *
   * @throws \PublizonConnectionException
   * @throws \PublizonException
   */
  public function getProduct(string $isbn, bool $retailer_id = FALSE) {
    // Get default retailer id if none specified.
    $retailer_id = $retailer_id ? $retailer_id : variable_get('publizon_default_retailer', '');

    // Get product form the web-service.
    $response = $this->call('product', 'GetProduct', $retailer_id, array(
      'pub:ebookid' => $isbn,
    ), array('pub' => 'http://pubhub.dk/'));

    // Check if any data was returned.
    $data = $response->xpath('//data');
    if (isset($data[0])) {
      return new PublizonProduct($data[0]);
    }

    $this->logger->log('The product with isbn (' . $isbn . ') did not return any data', 'WARNING');

    return FALSE;
  }

  /**
   * Get the cover URI for an ISBN.
   *
   * @param string $isbn
   *   The ISBN to get cover for.
   *
   * @return string
   *   URI of the cover image, or false if no image found.
   */
  public function getCoverUri(string $isbn) {
    try {
      $product = $this->getProduct($isbn);

      return !empty($product->coverImage)
        ? url($product->coverImage, [
          'query' => array_filter([
            // Request cover image no higher than the defined ting cover max
            // size (defined in ting_covers.module).
            // The cover images will be scaled to fit inside a square box with
            // height (and width) TING_COVERS_MAX_SIZE pixels, and since most
            // book covers are higher than they are wide we limit the height for
            // best performance.
            'height' => defined('TING_COVERS_MAX_SIZE') ? TING_COVERS_MAX_SIZE : NULL
          ]),
        ])
        : FALSE;
    }
    catch (Exception $e) {
      return FALSE;
    }
  }

}
