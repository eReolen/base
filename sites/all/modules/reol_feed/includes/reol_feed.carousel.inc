<?php

/**
 * @file
 * Contains functions for generating the carousel feed XMLs.
 */

/**
 * Generate feed for the carousel.
 */
function reol_feed_feeds_carousel() {
  $searches = variable_get('ting_carousel_search_queries', array());

  // Prepare XML.
  $e_feed = new SimpleXMLElement('<feed></feed>');
  $a_feed = new SimpleXMLElement('<feed></feed>');

  // Fetch all objects, and add to relevant feeds.
  foreach ($searches as $index => $search) {
    // Add item to feed.
    $e_item = $e_feed->addChild('item');
    $e_item->guid = "e_" . md5($search['query']);
    $e_item->source = "ereolen";
    $e_item->title = $search['title'];
    $e_item->query = $search['query'];
    $e_books = $e_item->addChild('books');

    $a_item = $a_feed->addChild('item');
    $a_item->guid = "a_" . md5($search['query']);
    $a_item->source = "netlydbog";
    $a_item->title = $search['title'];
    $a_item->query = $search['query'];
    $a_books = $a_item->addChild('books');

    $results = _ting_search_carousel_get_content($index);

    foreach ($results as $result) {
      $ting_object = ding_entity_load($result->id);

      // Determine where to put this book.
      $books = $e_books;
      if (reol_base_get_type_name($ting_object->type) == "audiobook") {
        $books = $a_books;
      }

      $book = $books->addChild('book');
      $book->{0} = $ting_object->title;
      // The search from _ting_search_carousel_get_content fetches covers,
      // so we are safe to just get the file path, and use that.
      $book->addAttribute('cover', file_create_url(ting_covers_object_path($ting_object->id)));
      $book->addAttribute('isbn', reol_base_get_isbn($ting_object->localId));
    }

    // Write feeds.
    reol_feed_write_feed(array(
      'type' => 'ebook',
      'filename' => 'carousel.xml',
    ), $e_feed->asXML());
    reol_feed_write_feed(array(
      'type' => 'audiobook',
      'filename' => 'carousel.xml',
    ), $a_feed->asXML());
  }
}

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
    if (!$categories) {
      continue;
    }

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
            $query->{0} = $search->query;
            $query['title'] = $search->title;
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
