<?php

/**
 * @file
 * Functionality specific for fetching stuff from litteratursiden.dk
 */

/**
 * Get reviews.
 *
 * @return array
 *   Array of titles found for each type.
 */
function reol_review_get_reviews() {
  module_load_include('client.inc', 'ting');

  // See if we have the results cached.
  $found = &drupal_static(__FUNCTION__);
  if (isset($found)) {
    return $found;
  }
  else {
    if ($cache = cache_get('reol_review:reviews')) {
      return $cache->data;
    }
    $found = array();
  }

  // Make sure we have arrays for each type.
  $types = reol_base_get_type_name();
  foreach ($types as $type => $n) {
    if (!isset($found[$type])) {
      $found[$type] = array();
    }
  }

  $find_num = variable_get('reol_review_find_reviews_count_min', 2);
  $find_multiplier = variable_get('reol_review_find_reviews_count_multiplier', 10);
  $call_max = variable_get('reol_review_feed_try_limit', 25);
  $call_count = 0;

  // We define a function for determining whether or not
  // we are done. This allows for a prettier while statement.
  $done = function($found, $find_num, $call_count, $call_max) {
    if ($call_count >= $call_max) {
      return TRUE;
    }
    foreach ($found as $f) {
      // If we have not found enough for this type.
      if (count($f) < $find_num) {
        return FALSE;
      }
    }
    return TRUE;
  };

  // Keep looking while we have not found enough items yet.
  while (!$done($found, $find_num, $call_count, $call_max)) {
    $results = reol_review_fetch_reviews($find_num * $find_multiplier, $call_count * $find_num * $find_multiplier);
    $call_count++;

    // Go through results, only adding the ones that we can find in our data.
    foreach ($results as $result) {
      // Malformed results might appear, ignore them.
      if (!isset($result->isbn)) {
        continue;
      }
      $isbn = reol_base_convert_to_isbn($result->isbn);
      if (!$isbn) {
        continue;
      }

      // We have to explicitly search for each title, instead
      // of searching for more at a time, as the ISBN-number they are
      // found on is not necessarily their own, it could be the physical
      // books ISBN. Therefore there is no way to map a result to the
      // one fetched from Ding, if searches are not done on each result.
      $ting_result = ting_do_search($isbn);
      // If we have found exactly one.
      // If more have been found we cannot count on the results.
      if ($ting_result->numTotalObjects == 1) {
        list($result->ding_entity_id) = array_keys($ting_result->collections);
        $ting_entity = ding_entity_load($result->ding_entity_id);
        $type = reol_base_get_type_name($ting_entity->type);
        if ($type) {
          $found[reol_base_get_type_name($ting_entity->type)][] = $result;
        }
      }
    }
  }

  // Cache result, but only for 12 hours.
  cache_set('reol_review:reviews', $found, 'cache', time() + 12 * 60 * 60);
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
