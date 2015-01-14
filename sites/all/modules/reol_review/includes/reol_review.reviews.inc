<?php

/**
 * @file
 * Functionality specific for fetching stuff from litteratursiden.dk
 */

/**
 * Ensure that reviews are updated.
 */
function _reol_review_ensure_reviews() {
  // Refresh every 12 hours.
  if (($cache = cache_get('reol_review:reviews')) && (($cache->created + 12 * 60 * 60) > REQUEST_TIME)) {
    return;
  }

  $outdated = (variable_get('reol_review_reviews_next_update', 0)) < REQUEST_TIME;
  if ($outdated || !variable_get('reol_review_reviews', FALSE)) {
    // Prepare found array.
    $found = array();
    reol_review_alter_found($found);

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
        module_load_include('client.inc', 'ting');
        $ting_result = ting_do_search($isbn);
        if ($ting_result) {
          // If we have found exactly one.
          // If more have been found we cannot count on the results.
          if ($ting_result->numTotalObjects == 1) {
            list($result->ding_entity_id) = array_keys($ting_result->collections);
            $ting_entity = ding_entity_load($result->ding_entity_id);

            // Make sure the title does exist in publizon
            // and that the title has a cover.
            $product = publizon_get_product_cover($ting_entity->localId);

            // If not, we ignore this one.
            if (!$product) {
              continue;
            }

            $type = reol_base_get_type_name($ting_entity->type);
            if ($type) {
              $found[reol_base_get_type_name($ting_entity->type)][] = $result;
            }
          }
        }
        else {
          watchdog('reol_review', 'Ting search failed.', array(), WATCHDOG_WARNING);
        }
      }
    }

    variable_set('reol_review_reviews', $found);
    variable_set('reol_review_reviews_next_update', REQUEST_TIME + 12 * 60 * 60);
  }
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
  $feed_url = variable_get('reol_review_litteratursiden_feed', 'http://www.litteratursiden.dk/service/recommendations');
  if ($feed_url) {
    $feed_url = drupal_parse_url($feed_url);
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
  return array();
}

/**
 * Get a random review.
 *
 * @param string $type
 *   The type to get a random review for.
 *   If not set, return one random result in all types
 *
 * @return StdClass
 *   The review randomly chosen.
 */
function reol_review_get_random_review($type = FALSE) {
  $reviews = reol_review_get_reviews();
  // Reviews are indexed by type. Create an array of all reviews, regardless
  // of type.
  $all_reviews = array();
  if ($type) {
    $all_reviews = $reviews[$type];
  }
  else {
    $all_reviews = call_user_func_array('array_merge', array_values($reviews));
  }

  return count($all_reviews) ? $all_reviews[array_rand($all_reviews)] : FALSE;
}
