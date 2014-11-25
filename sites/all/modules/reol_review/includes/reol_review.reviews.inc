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
  $types = reol_base_get_type_name();
  $found = array();
  foreach ($types as $type => $n) {
    $found[$type] = array();
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
      $isbn = reol_base_convert_to_isbn($result->isbn);
      if (!$isbn) {
        continue;
      }

      // TODO We should be able to do this when we go into production, as
      // it should be true for all titles from Publizon.
      // $ting_result = ting_do_search("term.identifier=" . $isbn);
      // For now, we just search for ISBN.
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
