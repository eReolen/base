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
  foreach ($searches as $search) {

    $e_item = NULL;
    $e_books = NULL;
    $a_item = NULL;
    $a_books = NULL;
    $offset = 0;
    do {
      $results = ting_search_carousel_get_entities($search['query'], $offset, 50);
      foreach ($results['entities'] as $ting_object) {
        // Determine where to put this book.
        $books = NULL;
        if (reol_base_get_type_name($ting_object->type) == "audiobook") {
          if (!$a_item) {
            $a_item = $a_feed->addChild('item');
            $a_item->guid = "a_" . md5($search['query']);
            $a_item->title = $search['title'];
            $a_item->query = $search['query'];
            $a_item->source = 'netlydbog';
            $a_books = $a_item->addChild('books');
          }
          $books = $a_books;
        }
        else {
          if (!$e_item) {
            $e_item = $e_feed->addChild('item');
            $e_item->guid = "e_" . md5($search['query']);
            $e_item->title = $search['title'];
            $e_item->query = $search['query'];
            $e_item->source = 'ereolen';
            $e_books = $e_item->addChild('books');
          }
          $books = $e_books;
        }

        $book = $books->addChild('book');
        $book[0] = $ting_object->title;
        // The search from _ting_search_carousel_get_content fetches covers,
        // so we are safe to just get the file path, and use that.
        $book->addAttribute('cover', file_create_url(ting_covers_object_path($ting_object->id)));
        $book->addAttribute('isbn', reol_base_get_isbn($ting_object->localId));
      }
      $offset = $results['next_offset'];
    } while ($offset > -1);
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
