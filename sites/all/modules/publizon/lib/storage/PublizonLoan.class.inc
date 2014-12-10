<?php
/**
 * @file
 * Contains the loans storage classes uses by PublizonUserLoans.
 */

/**
 * Stores information about a given loan (storage class). This object should
 * only be create from inside PublizonUserLoans
 *
 * The loan contains a PublizonProduct object with extened information about the
 * product if avaliable from Publizon. If not available its values will be empty
 * with the exception of the ISBN number.
 */
class PublizonLoan extends Publizon {
  protected $properties = array(
    'isbn' => NULL,
    'internal_order_number' => NULL,
    'retailer_order_number' => NULL,
    'status' => NULL,
    'order_date' => NULL,
    'expire_date' => NULL,
    'title' => NULL,
    'authors' => NULL,
    'publisher' => NULL,
    'format' => NULL,
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
   * Checks if a given loan is expired.
   *
   * @return bool
   *   Returns TRUE if the loan is expired else FALSE
   */
  public function isExpired() {
    if (($this->expire_date - time()) > 0) {
      return FALSE;
    }
    return TRUE;
  }

  /**
   * Get expiration of loan.
   *
   * Creates a user friendly expire string of a loans expire date in relation to
   * the current time.
   *
   * @return string
   *   Well formatter string of when the loan expires.
   */
  public function loanExpiresIn() {
    $str = t('The loan is expired.');
    if (!$this->isExpired()) {
      $hours = date_difference(time(), $this->expire_date, 'hours', DATE_UNIX);
      if ($hours <= 24) {
        $str = t('Loan expires in %hours', array(
          '%hours' => format_plural(ceil($hours), 'one hour.', '@count hours.'),
        ));
      }
      else {
        $days = date_difference(time(), $this->expire_date, 'days', DATE_UNIX);
        $str = t('Loan expires in %days', array(
          '%days' => format_plural($days, 'one day.', '@count days'),
        ));
      }
    }
    return $str;
  }

  /**
   * Parse a XML loan from publizon into the object.
   *
   * @param SimpleXMLElement $item
   *   Publizon XML representation of a loan.
   */
  private function parse(SimpleXMLElement $item) {
    // Get book authors.
    $authors = array();
    foreach ($item->book->authors->author as $author) {
      $authors[] = (string) $author->attributes()->name;
    }

    $this->isbn = (string) $item->book->attributes()->id;
    $this->retailer_order_number = (string) $item->retailerordernumber;
    $this->internal_order_number = (string) $item->internalordernumber;
    $this->status = (int) $item->orderstatus->attributes()->id;
    $this->order_date = strtotime((string) $item->orderdate);
    $this->expire_date = strtotime((string) $item->loanexpiredate);
    $this->title = (string) $item->book->title;
    $this->authors = $authors;
    $this->publisher = (string) $item->book->publisher;
    $this->format = (int) $item->format->attributes()->id;
  }
}
