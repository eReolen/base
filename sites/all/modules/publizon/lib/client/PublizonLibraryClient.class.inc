<?php

/**
 * @file
 * Implementation of communicating with the Publizon API for libraries.
 */

/**
 *
 */
class PublizonLibraryClient extends PublizonClient {

  /**
   * Get basic information about a given library as registered at Publizon.
   *
   * @param string $retailer_id
   *   The library's ID at Publizon.
   *
   * @return PublizonLibrary|bool
   *   Library information object.
   *
   * @throws \PublizonConnectionException
   * @throws \PublizonException
   */
  public function getLibraryProfile($retailer_id = NULL) {
    // Make the web-service call.
    $response = $this->call('library_profile', 'GetLibraryProfile', $retailer_id, array(), array('pub' => 'http://pubhub.dk/'));

    // Check if any data was returned.
    $data = $response->xpath('//data');
    if (isset($data[0])) {
      return new PublizonLibrary($data[0]);
    }

    $this->logger->log('The library profile with id (' . $retailer_id . ') did not return any data', 'WARNING');
    return FALSE;
  }

}
