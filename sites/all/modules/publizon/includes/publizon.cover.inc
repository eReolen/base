<?php
/**
 * @file
 * Ding cover provider for Publizon.
 */

/**
 * Get covers for an array of ids.
 *
 * @TODO
 */
function publizon_cover_get($ids) {
  $covers = array();

  foreach ($ids as $isbn) {
    // Get the cover image from Publizon.
    $client = PublizonClient::getClient();

    $uri = $client->getCoverUri($isbn);

    // If no cover was found, return FALSE for this one.
    if (empty($uri)) {
      $covers[$isbn] = FALSE;
      continue;
    }

    // Try to download the image.
    $result = drupal_http_request($uri);

    // If download failed, return FALSE for this one.
    if ($result->code != 200) {
      $covers[$isbn] = FALSE;
      continue;
    }

    $filename = ting_covers_object_path($isbn);
    $directory = dirname($filename);

    // Build the destination folder tree if it doesn't already exist.
    if (!file_prepare_directory($directory, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS)) {
      watchdog('ting_covers', 'Failed to create directory: %directory', array('%directory' => $directory), WATCHDOG_ERROR);
      $covers[$isbn] = FALSE;
      continue;
    }

    // Try to save the file.
    $file = file_unmanaged_save_data($result->data, $filename, FILE_EXISTS_REPLACE);

    // If successfull, return file object for this one.
    if ($file) {
      $covers[$isbn] = $file;
    }
    // Else return FALSE.
    else {
      $covers[$isbn] = FALSE;
    }
  }

  return $covers;
}
