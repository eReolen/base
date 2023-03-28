<?php

/**
 * @file
 * Implementation of communicating with the Publizon API for libraries.
 */

/**
 * TODO doc comment is empty.
 */
class PublizonLibraryClient extends PublizonClient {

  /**
   * Get basic information about a given library as registered at Publizon.
   *
   * @param string|null $retailer_id
   *   The library's ID at Publizon.
   *
   * @return PublizonLibrary|bool
   *   Library information object.
   *
   * @throws \PublizonConnectionException
   * @throws \PublizonException
   */
  public function getLibraryProfile(string $retailer_id = NULL, array $institution_tags = array()) {
    // Make the web-service call.
    $response = $this->call('library_profile', 'GetLibraryProfile', $retailer_id, array(
      'pub:institutionTags' => array(
        'pub:string' => $institution_tags
      ),
    ), array('pub' => 'http://pubhub.dk/'));

    // Check if any data was returned.
    $data = $response->xpath('//data');
    if (isset($data[0])) {
      return new PublizonLibrary($data[0]);
    }

    $this->logger->log('The library profile with id (' . $retailer_id . ') did not return any data', 'WARNING');
    return FALSE;
  }

}
