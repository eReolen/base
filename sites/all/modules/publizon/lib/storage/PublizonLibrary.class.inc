<?php

/**
 * @file
 * Contains the library storage class.
 */

/**
 *
 */
class PublizonLibrary extends Publizon {
  protected $properties = array(
    'maxEbookLoans' => NULL,
    'maxAudiobookLoans' => NULL,
    'maxEbookReservations' => NULL,
    'maxAudiobookReservations' => NULL,
  );

  /**
   * Constructor.
   *
   * @param SimpleXMLElement $library
   *   The XML-library.
   */
  public function __construct(SimpleXMLElement $library) {
    $this->parse($library);
  }

  /**
   * Parse a XML library from publizon into the object.
   *
   * @param SimpleXMLElement $item
   *   Publizon XML representation of a library.
   */
  private function parse(SimpleXMLElement $item) {
    $this->maxEbookLoans = (int) $item->MaxConcurrentLoansPerBorrower;
    $this->maxAudiobookLoans = (int) $item->MaxConcurrentAudioLoansPerBorrower;
    $this->maxEbookReservations = (int) $item->MaxConcurrentReservationsPerBorrower;
    $this->maxAudiobookReservations = (int) $item->MaxConcurrentAudioReservationsPerBorrower;
  }

}
