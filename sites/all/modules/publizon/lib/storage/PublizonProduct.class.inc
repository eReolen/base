<?php
/**
 * @file
 * Contains the product storage classes.
 */

class PublizonProduct extends Publizon {
  protected $properties = array(
    'coverImage' => NULL,
    'format' => NULL,
    'contributors' => NULL,
  );

  /**
   * Constructor.
   *
   * @param SimpleXMLElement $product
   *   The XML-product.
   *
   * @throws PublizonProductException
   */
  public function __construct(SimpleXMLElement $product) {
    $this->parse($product);
  }

  /**
   * Parse a XML loan from publizon into the object.
   *
   * @param SimpleXMLElement $item
   *   Publizon XML representation of a loan.
   */
  private function parse(SimpleXMLElement $item) {
    $this->coverImage = (string) $item->coverimage;
    $this->format = new StdClass();
    $this->format->id = (int) $item->formats->format_id;
    $this->format->name = (string) $item->formats->name;
    $this->format->size = (int) $item->formats->size_bytes;
    $this->contributors = new StdClass();
    foreach ($item->contributors as $contributor) {
      $key = $this->convertContributorType((string) $contributor->type);
      if (!$key) {
        continue;
      }

      $obj = $this->contributors->$key = new StdClass();
      $obj->firstName = (string) $contributor->first_name;
      $obj->lastName = (string) $contributor->last_name;
    }
  }

  /**
   * Convert a contributor type to internal representation.
   *
   * @param string $type
   *   The name of the type.
   *
   * @return string
   *   Internal representation of the type or FALSE if not found.
   */
  private function convertContributorType($type) {
    $map = array(
      'by (author)' => 'author',
      'read by' => 'reader',
    );

    return isset($map[strtolower($type)]) ? $map[strtolower($type)] : FALSE;
  }
}
