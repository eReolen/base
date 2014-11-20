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

  foreach ($ids as $local_id) {
    $isbn = reol_base_get_isbn($local_id);
    // If we do not have an ISBN, we do not wish to handle it.
    if (!$isbn) {
      continue;
    }

    // Get the cover image from Publizon.
    $client = PublizonClient::getClient();

    $uri = $client->getCoverUri($isbn);

    // If no cover was found, return FALSE for this one.
    if (empty($uri)) {
      $covers[$local_id] = FALSE;
      continue;
    }

    // Try to download the image.
    $result = drupal_http_request($uri);

    // If download failed, return FALSE for this one.
    if ($result->code != 200) {
      $covers[$local_id] = FALSE;
      continue;
    }

    $filename = ting_covers_object_path($local_id);
    $directory = dirname($filename);

    // Build the destination folder tree if it doesn't already exist.
    if (!file_prepare_directory($directory, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS)) {
      watchdog('ting_covers', 'Failed to create directory: %directory', array('%directory' => $directory), WATCHDOG_ERROR);
      $covers[$local_id] = FALSE;
      continue;
    }

    // Try to save the file.
    $file = file_unmanaged_save_data($result->data, $filename, FILE_EXISTS_REPLACE);

    // If successfull, return file object for this one.
    if ($file) {
      $covers[$local_id] = $file;
    }
    // Else return FALSE.
    else {
      $covers[$local_id] = FALSE;
    }
  }

  return $covers;
}
