<?php

/**
 * @file
 * Contains functions for generating all the feed XMLs.
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
    $e_item->addChild('guid')->{0} = "e_" . md5($search['query']);
    $e_item->addChild('source')->{0} = "ereolen";
    $e_item->addChild('title')->{0} = $search['title'];
    $e_item->addChild('query')->{0} = $search['query'];
    $e_books = $e_item->addChild('books');

    $a_item = $a_feed->addChild('item');
    $a_item->addChild('guid')->{0} = "a_" . md5($search['query']);
    $a_item->addChild('source')->{0} = "netlydbog";
    $a_item->addChild('title')->{0} = $search['title'];
    $a_item->addChild('query')->{0} = $search['query'];
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
      // The search from _ting_search_carousel_get_content fetches covers,
      // so we are safe to just get the file path, and use that.
      $book->addAttribute('cover', file_create_url(ting_covers_object_path($ting_object->id)));
      $book->addAttribute('isbn', reol_base_get_isbn($ting_object->localId));
      $book->{0} = $ting_object->title;
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
