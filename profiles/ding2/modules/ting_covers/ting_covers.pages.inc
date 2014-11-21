<?php
/**
 * @file
 * Retrieves covers for ting objects and returns them in the correct format
 * based on configuration.
 */

/**
 * Return the URL for the cover of an object.
 */
function ting_covers_objects() {
  $cover_request = array();

  foreach ($_POST['coverData'] as $cover_info) {
    $cover_request[$cover_info['id']] = array(
      'image_style' => $cover_info['image_style'],
    );
  }

  $covers = ting_covers_load($cover_request);
  array_walk($covers, function(&$elem, $key) {
    $elem['id'] = "" . $key;
  });

  // Return all image information.
  drupal_json_output(array_values($covers));
}
