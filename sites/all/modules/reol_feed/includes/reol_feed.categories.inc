<?php

/**
 * @file
 * Contains functions for generating the categories feed XMLs.
 */

/**
 * Generate feed for the categories.
 */
function reol_feed_feeds_categories() {
  $types = array(
    'ebook' => 'ereolen',
    'audiobook' => 'netlydbog',
  );
  foreach ($types as $type => $type_name) {
    $feed = new SimpleXMLElement('<feed></feed>');
    $categories = reol_category_feed($type);
    if ($categories) {
      foreach ($categories as $name => $category) {
        if (is_array($category)) {
          $item = $feed->addChild('item');
          $item->guid = md5($name);
          $item->source = $type_name;
          $item->title = $name;
          $searches = $item->addChild('searches');
          foreach ($category as $search) {
            if ($search instanceof ReolCategory) {
              $query = $searches->addChild('query');
              $query[0] = $search->query;
              $query['title'] = $search->title;
            }
          }
        }
      }
    }

    reol_feed_write_feed(array(
      'type' => $type,
      'filename' => 'categories.xml',
    ), $feed->asXML());
  }
}
