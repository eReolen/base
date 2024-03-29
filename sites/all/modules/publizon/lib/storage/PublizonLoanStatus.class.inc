<?php

/**
 * @file
 * Contains the loan status storage class.
 */

/**
 * TODO doc comment is empty.
 */
class PublizonLoanStatus extends Publizon {
  /**
   * TODO missing member variable doc comment.
   *
   * @var array
   */
  protected array $properties = array(
    'loanStatus' => NULL,
    'onChecklist' => NULL,
    'isbn' => NULL,
  );

  /**
   * Constructor.
   *
   * @param SimpleXMLElement $loan_status
   *   The XML-loan status.
   */
  public function __construct(SimpleXMLElement $loan_status) {
    $this->parse($loan_status);
  }

  /**
   * Parse a XML loan status from publizon into the object.
   *
   * @param SimpleXMLElement $item
   *   Publizon XML representation of a loan status.
   */
  private function parse(SimpleXMLElement $item) {
    $this->loanStatus = (int) $item->loanstatus;
    $this->onChecklist = ((string) $item->onchecklist) === 'true' ? TRUE : FALSE;
    $this->isbn = (string) $item->ebookid;
  }

}
