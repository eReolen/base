<?php

/**
 * @file
 * Contains the loans storage classes uses by PublizonUserLoans.
 */

/**
 * Stores information about a given loan (storage class). This object should
 * only be create from inside PublizonUserLoans.
 *
 * The loan contains a PublizonProduct object with extened information about the
 * product if avaliable from Publizon. If not available its values will be empty
 * with the exception of the ISBN number.
 */
class PublizonReservation extends Publizon {
  protected $properties = array(
    'bookId' => NULL,
    'isbn' => NULL,
    'createdUtc' => NULL,
    'status' => NULL,
    'title' => NULL,
    'expireUtc' => NULL,
    'expectedRedeemDateUtc' => NULL,
  );

  /**
   * Constructor.
   *
   * Creates a new PublizonLoans object that stores basic information about the
   * users loans and also how many loans the user has. The object assumes that
   * the user is logged in and faling back to using the session values when
   * connecting to Publizon.
   *
   * @param SimpleXMLElement $book
   *   The XML-book to loan.
   *
   * @throws PublizonProductException
   */
  public function __construct(SimpleXMLElement $book) {
    $this->parse($book);
  }

  /**
   * Parse a XML loan from publizon into the object.
   *
   * @param SimpleXMLElement $item
   *   Publizon XML representation of a loan.
   */
  private function parse(SimpleXMLElement $item) {
    $this->bookId = (string) $item->bookId;
    $this->isbn = (string) $item->isbn;
    $this->createdUtc = strtotime((string) $item->createdutc);
    $this->status = (int) $item->status;
    $this->title = (string) $item->title;
    $this->expireUtc = strtotime((string) $item->expireutc);
    $this->expectedRedeemDateUtc = strtotime((string) $item->expectedredeemdateutc);
  }

}
