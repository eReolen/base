<?php

/**
 * @file
 * Functionality specific for fetching stuff from litteratursiden.dk
 */

/**
 * Update array of reviews in cache.
 */
function reol_review_update_reviews() {
  module_load_include('client.inc', 'ting');
  $found = array();
  $find_num = variable_get('reol_review_find_reviews_count_min', 10);
  $find_multiplier = variable_get('reol_review_find_reviews_count_multiplier', 4);
  $call_max = variable_get('reol_review_feed_try_limit', 25);
  $call_count = 0;

  // Keep looking while we have not found enough items yet.
  while (count($found) < $find_num || $call_count >= $call_max) {
    $results = reol_review_fetch_reviews($find_num * $find_multiplier, $call_count * $find_num * $find_multiplier);
    $call_count++;

    // Go through results, only adding the ones that we can find in our data.
    foreach ($results as $result) {
      // Malformed results might appear, ignore them.
      $isbn = reol_base_convert_to_isbn($result->isbn);
      if (!$isbn) {
        continue;
      }

      $ting_result = ting_do_search("term.identifier=" . $isbn);
      // If we have found exactly one.
      // If more have been found we cannot count on the results.
      if ($ting_result->numTotalObjects == 1) {
        list($result->ding_entity_id) = array_keys($ting_result->collections);
        $found[] = $result;
      }
    }
  }

  return $found;
}

/**
 * Fetch reviews from Litteratursiden.
 *
 * @param int $items
 *   Number of items to return.
 * @param int $start
 *   Offset to start list at.
 *
 * @return array
 *   The data returned from feed.
 */
function reol_review_fetch_reviews($items, $start) {
  $feed_url = drupal_parse_url(variable_get('reol_review_litteratursiden_feed', 'http://www.litteratursiden.dk/service/recommendations'));
  $feed_url['query']['count'] = $items;
  $feed_url['query']['offset'] = $start;

  $ch = curl_init();

  curl_setopt($ch, CURLOPT_HEADER, 0);
  // Set curl to return the data instead of printing it to the browser.
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($ch, CURLOPT_URL, url($feed_url['path'], $feed_url));
  $data = curl_exec($ch);
  curl_close($ch);
  return json_decode($data);
}
