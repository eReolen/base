<?php
/**
 * @file
 * Contains the checklist item storage class.
 */

class PublizonChecklistItem extends Publizon {
  protected $properties = array(
    'creationDateUtc' => NULL,
    'title' => NULL,
    'isbn' => NULL,
  );

  /**
   * Constructor.
   *
   * @param SimpleXMLElement $checklist_item
   *   The XML-checklist item.
   */
  public function __construct(SimpleXMLElement $checklist_item) {
    $this->parse($checklist_item);
  }

  /**
   * Parse a XML checklist item from publizon into the object.
   *
   * @param SimpleXMLElement $item
   *   Publizon XML representation of a checklist item.
   */
  private function parse(SimpleXMLElement $item) {
    $this->creationDateUtc = strtotime((string) $item->creationdateutc);
    $this->title = (string) $item->title;
    $this->isbn = (string) $item->isbn;
  }
}
