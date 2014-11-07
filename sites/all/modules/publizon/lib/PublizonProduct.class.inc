<?php
/**
 * @file
 * Defines class to hold a Publizon product. If the class is parsed an ISBN
 * number under construction it will automatically download the information form
 * the web-service. If the product have been cached, the cached version will be
 * used.
 *
 * Eg. $product = new PublizonProduct('9788770703147');
 */

/**
 * Publizon Product class that can hold a Publizon Product (ebook or netsound).
 */
class PublizonProduct extends Publizon {
  protected $properties = array(
    'created' => NULL,
    'modified' => NULL,
    'published' => NULL,
    'title' => NULL,
    'status' => NULL,
    'language' => NULL,
    'cover' => NULL,
    'cover_download_url' => NULL,
    'teaser_link' => NULL,
    'isbn' => NULL,
    'author' => NULL,
    'format_id' => NULL,
    'format' => NULL,
    'bytes' => NULL,
    'duration' => NULL,
    'price' => NULL,
    'publiser' => NULL,
    'description' => NULL,
    'categories' => NULL,
  );

  // This is outside the properties array, as it should not be cached with the
  // object properties. The ting object is used to get extended information and
  // verify that the product is available, so it needs to be as fresh as
  // possible, hence it's not cached.
  private $tingObject = NULL;

  /**
   * Constructor that takes a ISBN and fetches the product from Publizon.
   *
   * If the information is not located the product cache.
   *
   * @param string $isbn
   *   ISBN to identify the product.
   * @param bool $reset
   *   If TRUE the cache is updated. Defaults to FALSE.
   *
   * @throws PublizonProductException
   */
  public function __construct($isbn, $reset = FALSE) {
    // Check cache for the properties values.
    if (!$reset && ($cache = cache_get($isbn, 'cache_publizon_product')) && time() < $cache->expire) {
      $this->properties = $cache->data;
    }
    else {
      // If ISBN is provided and not cached. The publizon web-service will be
      // asked for the product information.
      if (isset($isbn)) {
        $client = PublizonClient::getClient();
        $this->parse($client->getProduct($isbn));

        // The product may sometimes not contain any information (removed from
        // Publizon). But maybe the data well have information, so we store the
        // ISBN.
        $this->isbn = $isbn;

        // We cache the result for 24 hours.
        cache_set($isbn, $this->properties, 'cache_publizon_product', time() + 43200);
      }
      else {
        throw new PublizonProductException('ISBN was not provided when trying to create Publizon product.');
      }
    }
  }

  /**
   * Returns the cover image through an image cache preset.
   *
   * If the full size or raw cover image is needed simple call: $product->cover.
   *
   * If the product do not have a cover image a default one located in the files
   * folder name default_cover.jpg will be used.
   *
   * @param string $presetname
   *   Name of the image cache preset to run the image through.
   * @param bool $local_cache
   *   If cover is not defined, try to look in the local filesystem. There may
   *   be a copy on storage. This can be useful on user loans lists. Defaults to
   *   FALSE.
   *
   * @return string
   *   Path to the rendered image.
   */
  public function getCover($presetname, $local_cache = TRUE) {
    if (!isset($this->cover)) {
      // Check if cached image should be re-downloaded.
      return imagecache_create_url($presetname, file_directory_path() . '/default_cover.jpg');
    }
    if ($local_cache) {
      $path = file_directory_path() . '/' . $this->encodeFile();
      if (!file_exists($path)) {
        return imagecache_create_url($presetname, $path);
      }
    }
    return imagecache_create_url($presetname, $this->cover);
  }

  /**
   * Get ting object.
   *
   * JIT fetch a ting object from the data well that represents the publizon
   * product.
   *
   * @return TingObject
   *   Returns a ting object from the T!NG data well.
   */
  public function getTingObject() {
    if (!isset($this->tingObject)) {
      // If not fetched in this http request, search the data well for the
      // product.
      $this->tingObject = publizon_ting_find_object($this->isbn);
    }
    return $this->tingObject;
  }

  /**
   * Get the e-books file format.
   *
   * @return mixed
   *   The name of the format. If unknown format FALSE is returned.
   */
  public function getFormat() {
    $format = FALSE;
    switch ($this->format_id) {
      case '50':
        $format = 'PDF';
        break;

      case '58':
        $format = 'EPUB';
        break;
    }

    return $format;
  }

  /**
   * Wrapper function that fetch the product cover (image).
   *
   * It's fetched from the web-service and stored locally.
   *
   * @param string $url
   *   The location from where to fetch the cover image.
   *
   * @return string
   *   The local path where the image is located.
   */
  private function fetchCover($url) {
    // Check that the URL is a valid url.
    if (filter_var($url, FILTER_VALIDATE_URL, FILTER_FLAG_SCHEME_REQUIRED)) {
      return $this->downloadImage($url);
    }
  }

  /**
   * Download image from a remote location over http(s).
   *
   * @param string $src
   *   The location from where to fetch the cover image.
   *
   * @return string
   *   The local path where the image is located.
   */
  private function downloadImage($src) {
    // Build full path into the sites file folder.
    $path = file_directory_path() . '/' . $this->encodeFile();

    // Check if file exists locally, hence no need to download it.
    if (!file_exists($path)) {
      // Request the image file form the remote server over http(s).
      $result = drupal_http_request($src);

      // If the request succeeded, save the image.
      if ($result->code == 200) {
        $folder = dirname($path);
        // Create destination folder, if it does not exists.
        if (!file_check_directory($folder, FILE_CREATE_DIRECTORY)) {
          // The operation failed (might be permissions).
          $path = FALSE;
        }
        else {
          // Save the file and return the new file name.
          $path = file_save_data($result->data, $path, FILE_EXISTS_REPLACE);
        }
      }
    }
    else {
      // Check if the image should be re-downloaded (approx. every 24 hours).
      $created = filemtime($path);
      if ($created < time() - 43200) {
        // Remove image from the filesystem and image cache.
        unlink($path);
        imagecache_image_flush($path);

        // Call the download load function once more to re-download the image.
        $this->downloadImage($src);
      }
    }

    return $path;
  }

  /**
   * Encodes the products into a unique path where the cover image can be saved.
   *
   * @return string
   *   Unique filename based on the product ISBN.
   */
  private function encodeFile() {
    return 'covers/' . md5($this->isbn) . '.jpg';
  }

  /**
   * Converts XML response from Publizon into the object properties.
   *
   * @param SimpleXmlElement $xml
   *   The "data" part of the XML message return form Publizon web-service
   *   request to get product.
   */
  private function parse($xml) {
    $this->created = strtotime($xml->created_date);
    $this->modified = strtotime($xml->updated_date);
    $this->title = (string) $xml->title;
    $this->status = (((string) $xml->status->description) == 'Active') ? TRUE : FALSE;
    $this->language = (string) $xml->language;
    $this->teaser_link = (string) $xml->teaser->link;
    $this->isbn = (string) $xml->external_ids->id;
    $this->author = array(
      'firstname' => (string) $xml->contributors->first_name,
      'lastname' => (string ) $xml->contributors->family_name,
    );
    $this->format_id = (string) $xml->formats->format_id;
    $this->format = (string) $xml->formats->name;
    $this->bytes = (string) $xml->formats->size_bytes;
    $this->duration = (string) $xml->formats->duration_minutes;
    $this->price = (string) $xml->price;
    $this->publiser = (string) $xml->publisher->name;
    $this->published = strtotime((string) $xml->first_published);
    $this->description = (string) $xml->description;

    $categories = array();
    foreach ($xml->categories as $category) {
      $categories[] = (string) $category->category;
    }
    $this->categories = $categories;

    // Download image here or in __get
    $this->cover = $this->fetchCover((string) $xml->thumbnailimage);
    $this->cover_download_url = (string) $xml->thumbnailimage;
  }
}

/**
 * Custom Exception for Publizon Products is mainly thrown when the object is
 * give invalided parameters.
 */
class PublizonProductException extends PublizonException {}
