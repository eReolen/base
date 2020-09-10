<?php

/**
 * @file
 * Contains the product storage classes.
 */

/**
 * TODO doc comment is empty.
 */
class PublizonProduct extends Publizon {
  /**
   * TODO missing member variable doc comment.
   *
   * @var array
   */
  protected $properties = array(
    'coverImage' => NULL,
    'format' => NULL,
    'category' => NULL,
    'title' => NULL,
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
    $this->title = (string) $item->title;
    $this->coverImage = (string) $item->coverimage;
    $this->format = new StdClass();
    $this->format->id = (int) $item->formats->format_id;
    $this->format->name = (string) $item->formats->name;
    $this->format->size = (int) $item->formats->size_bytes;
    if (isset($item->categories)) {
      $this->category = (string) $item->categories->attributes()->desc;
    }
  }

}
