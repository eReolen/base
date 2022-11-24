<?php

/**
 * @file
 * Implementation of communicating with the Publizon API for checklists.
 */

/**
 * TODO doc comment is empty.
 */
class PublizonChecklistClient extends PublizonClient {

  /**
   * Add a title to the user's checklist.
   *
   * @param string $retailer_id
   *   The id of the retailer to add to checklist for.
   * @param string $card_number
   *   The card number whose checklist to add to.
   * @param string $isbn
   *   The ISBN-number of the title.
   *
   * @throws PublizonException
   */
  public function addChecklistItem(string $retailer_id, string $card_number, string $isbn): bool {
    // Call the webservice, throwing exception on failure.
    $response = $this->call('checklist', 'AddCheckListItem', $retailer_id, array(
      'pub:cardnumber' => $card_number,
      'pub:ebookid' => $isbn,
    ), array('pub' => 'http://pubhub.dk/'));

    // Parse returned data.
    $data = $response->xpath('//data');
    if (isset($data[0]) && $data[0][0] == $card_number) {
      return TRUE;
    }

    // Data was malformed.
    $this->logger->log('Add checklist item request returned no/invalid data (' . $isbn . ').', 'ERROR');
    throw new PublizonException('Add checklist item request returned no/invalid data (' . $isbn . ').');
  }

  /**
   * Delete a title from the user's checklist.
   *
   * @param string $retailer_id
   *   The id of the retailer to delete from checklist for.
   * @param string $card_number
   *   The card number whose checklist to delete from.
   * @param string $isbn
   *   The ISBN-number of the title.
   *
   * @throws PublizonException
   */
  public function deleteChecklistItem(string $retailer_id, string $card_number, string $isbn): bool {
    // Call the webservice, throwing exception on failure.
    $response = $this->call('checklist', 'DeleteCheckListItem', $retailer_id, array(
      'pub:cardnumber' => $card_number,
      'pub:ebookid' => $isbn,
    ), array('pub' => 'http://pubhub.dk/'));

    // Parse returned data.
    $data = $response->xpath('//data');
    if (isset($data[0]) && $data[0][0] == $card_number) {
      return TRUE;
    }

    // Data was malformed.
    $this->logger->log('Delete checklist item request returned no/invalid data (' . $isbn . ').', 'ERROR');
    throw new PublizonException('Delete checklist item request returned no/invalid data (' . $isbn . ').');
  }

  /**
   * Get a user's checklist.
   *
   * @param string $retailer_id
   *   The id of the retailer to add to checklist for.
   * @param string $card_number
   *   The card number whose checklist to add to.
   *
   * @return array
   *   Array of PublizonChecklistItem objects.
   *
   * @throws PublizonException
   */
  public function getChecklist(string $retailer_id, string $card_number): array {
    // Call the webservice, throwing exception on failure.
    $response = $this->call('checklist', 'GetCheckList', $retailer_id, array(
      'pub:cardnumber' => $card_number,
    ), array('pub' => 'http://pubhub.dk/'));

    // Parse returned data.
    $data = $response->xpath('//data/checklist');
    $checklist = array();
    if (isset($data[0])) {
      foreach ($data as $chk) {
        $checklist[] = new PublizonChecklistItem($chk);
      }
    }
    return $checklist;
  }

}
