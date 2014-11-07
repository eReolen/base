<?php
/**
 * @file
 * Contains the information about the Object that stores information about a
 * given users status and loan at Publizon.
 */

/**
 * Stores information about a given users loans (storage class). So information
 * about max loans and remaining loans for the current user is stored here.
 *
 * The users loans are indexed by ISBN and can be fetched by
 * $user_loans->loans['isbn'] or simple $user_loans->loans. For more information
 * about a loan see the PublizonLoan class.
 */
class PublizonUserLoans extends Publizon {
  protected $properties = array(
    'max_loan_period' => NULL,
    'max_loan_per_time' => NULL,
    'max_loans_total' => NULL,

    // @todo: Ask Publizon what these are used for!
    'max_loan_pertime_sound' => NULL,
    'max_loans_total_sound' => NULL,

    // Loans in both netsound and e-book?
    'max_total_period' => NULL,
    'user_total_loans' => NULL,

    'usere_book_loans_remain' => NULL,
    'usere_book_loans_nexttime' => NULL,

    'user_sound_loans_nexttime' => NULL,

    'user_total_ebook_loans' => NULL,
    'user_total_sound_loans' => NULL,

    // Holds the objects loans.
    'loans' => NULL,
  );

  /**
   * Constructor.
   *
   * Creates a new PublizonLoans object that stores basic information about the
   * users loans and also how many loans the user has. The object assumes that
   * the user is logged in and falling back to using the session values when
   * connecting to Publizon.
   *
   * @param string $uid
   *   Drupal user ID
   * @param bool $fetch_ting_object
   *   Should the object fetch the ting objects for each loan
   * @param string $card_number
   *   The card number or CPR (login id) to get loans for (defaults to using the
   *   session).
   * @param bool $reset
   *   Should the cache be by passed.
   *
   * @throws PublizonProductException
   */
  public function __construct($uid = NULL, $fetch_ting_object = FALSE, $card_number = NULL, $reset = FALSE) {
    // Try to get current users uid.
    if (is_null($uid)) {
      global $user;
      $uid = $user->uid;
    }

    // Check cache for the properties values.
    if (!$reset && ($cache = cache_get($uid, 'cache_publizon_loans')) && $cache->expire > time()) {
      $this->properties = $cache->data;
    }
    else {
      // Get the users loans by building local cache.
      $this->refreshCache();
    }

    // This can not be done when parsing the loans, as this has to be outside
    // cache and fresh data always.
    if ($fetch_ting_object) {
      foreach ($this->loans as $loan) {
        $loan->product->getTingObject();
      }
    }
  }

  /**
   * Checks if a loan with the ISBN given is active for the user.
   *
   * @param string $isbn
   *   ISBN of the loan to check.
   * @param bool $expired
   *   If TRUE the loan must have not be expired to be a loan.
   *
   * @return bool
   *   TRUE if the user have the loan else FALSE.
   */
  public function isLoan($isbn, $expired = FALSE) {
    if (isset($this->loans[$isbn])) {
      if ($expired) {
        if ($this->loans[$isbn]->isExpired()) {
          return FALSE;
        }
      }
      return TRUE;
    }
    return FALSE;
  }

  /**
   * Create a new loan for the currently logged in user.
   *
   * If the loan is unsuccessful an Publizon exception will be thrown.
   *
   * @param string $isbn
   *   The products ISBN number for which the user is trying to loan.
   *
   * @return string
   *   The download link to the prodoct, if successfull.
   */
  public function createLoan($isbn) {
    // Check if this already is a loan and if so return that loan.
    if ($this->isLoan($isbn) && !$this->loans[$isbn]->isExpired()) {
      return $this->loans[$isbn];
    }

    // Try to create new loan.
    $client = PublizonClient::getClient();
    $download_url = $client->createLoan($this->getCardNumber(), $this->getPincode(), $isbn);

    // Refresh the local loans cache.
    $this->refreshCache();

    // Return the download url.
    return $download_url;
  }

  /**
   * Get the next loan period.
   *
   * Finds the number of hours or days until the current user can loan a book
   * again.
   *
   * @return string
   *   Formatted string with the next expire time.
   */
  public function nextLoanPeriode() {
    // Because of the loans cache we can not use the field available
    // from publizon.

    // Find the first loan to expire.
    $expire = 100000000000;
    foreach ($this->loans as $loan) {
      $expire = ($loan->expire_date > $expire) ? $expire : $loan->expire_date;
    }
    $hours = (date_difference(time(), $expire, 'hours', DATE_UNIX));
    if ($hours <= 24) {
      $str = t('You can loan a new product in %hours.', array(
        '%hours' => format_plural(ceil($hours), 'one hour', '@count hours'),
      ));
    }
    else {
      $days = date_difference(time(), $expire, 'days', DATE_UNIX);
      $str = t('You can loan a new product in %days.', array(
        '%days' => format_plural(ceil($days), 'one day', '@count days'),
      ));
    }

    return $str;
  }

  /**
   * Fetch all loans for the current user.
   *
   * @throws PublizonLoansException
   */
  private function fetchLoans() {
    $client = PublizonClient::getClient();
    $data = $client->getLibraryUserOrderList($this->getCardNumber());
    if ($data) {
      $this->parse($data);
    }

    // If the user dose not have any loans, no data element is returned from
    // publizon.
    return FALSE;
  }

  /**
   * Get card number.
   *
   * If the parameter given is not NULL and is numeric the card number is
   * returned. If not, the session is checked for a login ID, which is returned,
   * if found.
   *
   * @param string $card_number
   *   Login ID which most likely is a card number or CPR.
   *
   * @return string
   *   The card number.
   * @throws PublizonLoansException
   *   If the card number / login id is not found the exception is thrown.
   */
  private function getCardNumber($card_number = NULL) {
    if (isset($card_number) && is_numeric($card_number)) {
      return $card_number;
    }
    elseif (isset($_SESSION['login_id'])) {
      return $_SESSION['login_id'];
    }
    throw new PublizonLoansException('Can\'t get loans for the current user as login ID was not detected.');
  }

  /**
   * Get pincode.
   *
   * If the parameter given is not NULL and is numeric the pincode is returned.
   * If not, the session is checked for a pincode (pass), which is returned, if
   * found.
   *
   * @param string $pincode
   *   The current users pin code.
   *
   * @return string
   *   The current users pincode
   *
   * @throws PublizonLoansException
   *   If no pin code information is found and exception is thrown.
   */
  private function getPincode($pincode = NULL) {
    if (isset($pincode) && is_numeric($pincode)) {
      return $pincode;
    }
    elseif (isset($_SESSION['pass'])) {
      return $_SESSION['pass'];
    }
    throw new PublizonLoansException('Can\'t get loans for the current user as login ID was not detected.');
  }

  /**
   * Update the cache with the current loans.
   */
  private function refreshCache() {
    global $user;

    // Get the users loans.
    $this->fetchLoans();

    // We cache the result until the user makes changes to the loans or loan
    // expires.
    if (!$_SESSION['by_pass_cache']) {
      cache_set($user->uid, $this->properties, 'cache_publizon_loans', time() + 300);
    }

    // Loans have been refreshed, so the loan block cache needs to be updated.
    cache_clear_all('publizon_loan_block_' . $user->uid, 'cache_publizon_loans');
  }

  /**
   * Parse XML.
   *
   * Helper that is used during creation of this class and parses the XML
   * messages delivered from the web-service. It expects to review and array
   * with two elements (LibraryExtension and Loans) from the XML response.
   *
   * @param array $data
   *   Array with two elements (LibraryExtension and Loans) from the XML
   *   response as SimpleXmlElement objects.
   */
  private function parse($data) {
    // Set information about the users loans limit.
    $extension = $data[1];
    $this->max_loan_period = (int) $data[1]->maxloanperiod;
    $this->max_loan_per_time = (int) $data[1]->maxloanpertime;
    $this->max_loans_total = (int) $data[1]->maxloanstotal;
    $this->max_loan_pertime_sound = (int) $data[1]->maxloanpertimesound;
    $this->max_loans_total_sound = (int) $data[1]->maxloanstotalsound;
    $this->max_total_period = (int) $data[1]->maxtotalperiod;
    $this->user_total_loans = (int) $data[1]->usertotalloans;
    $this->usere_book_loans_remain = (int) $data[1]->userebookloansremain;
    $this->usere_book_loans_nexttime = strtotime((string) $data[1]->userebookloansnexttime);
    $this->user_sound_loans_nexttime = strtotime((string) $data[1]->usersoundloansNexttime);
    $this->user_total_ebook_loans = (int) $data[1]->usertotalebookloans;
    $this->user_total_sound_loans = (int) $data[1]->usertotalsoundloans;

    $loans = array();
    foreach ($data[0]->orderitem as $item) {
      // Load loans and check if the loan is expired, only storing no-expired
      // loans locally.
      $loan = new PublizonLoan($item);
      if (!$loan->isExpired()) {
        $loans[(string) $item->book->attributes()->id] = $loan;
      }
    }
    $this->loans = $loans;
  }
}

/**
 * Custom Exception class used to indicate that there was a problem with the
 * users loans.
 */
class PublizonLoansException extends PublizonException {}
