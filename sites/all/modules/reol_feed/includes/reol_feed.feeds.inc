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
    $e_item->addChild('guid', "e_" . md5($search['query']));
    $e_item->addChild('source', "ereolen");
    $e_item->addChild('title', $search['title']);
    $e_item->addChild('query', $search['query']);
    $e_books = $e_item->addChild('books');

    $a_item = $a_feed->addChild('item');
    $a_item->addChild('guid', "a_" . md5($search['query']));
    $a_item->addChild('source', "netlydbog");
    $a_item->addChild('title', $search['title']);
    $a_item->addChild('query', $search['query']);
    $a_books = $a_item->addChild('books');

    $results = _ting_search_carousel_get_content($index);

    foreach ($results as $result) {
      $ting_object = ding_entity_load($result->id);

      // Determine where to put this book.
      $books = $e_books;
      if (reol_base_get_type_name($ting_object->type) == "audiobook") {
        $books = $a_books;
      }

      $book = $books->addChild('book', $ting_object->title);
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
 * Generate feed for the frontpage items.
 */
function reol_feed_feeds_frontpage() {
  // Prepare XML.
  $e_feed = new SimpleXMLElement('<feed></feed>');
  $a_feed = new SimpleXMLElement('<feed></feed>');

  $feed_item_count = variable_get('reol_feed_frontpage_item_count', 2);
  // Add news to feeds.
  $news_array = array(
    (object) array(
      'feed' => $e_feed,
      'items' => reol_feed_get_latest('article', 'ebook', $feed_item_count),
    ),
    (object) array(
      'feed' => $a_feed,
      'items' => reol_feed_get_latest('article', 'audiobook', $feed_item_count),
    ),
  );

  // Add the news found to feed.
  foreach ($news_array as $type) {
    foreach ($type->items as $node) {
      reol_feed_feeds_add_news_item($type->feed, $node);
    }
  }

  // Add video to feeds.
  $video_array = array(
    (object) array(
      'feed' => $e_feed,
      'items' => reol_feed_get_latest('video', 'ebook', $feed_item_count),
    ),
    (object) array(
      'feed' => $a_feed,
      'items' => reol_feed_get_latest('video', 'audiobook', $feed_item_count),
    ),
  );

  // Add the videos found to feed.
  foreach ($video_array as $type) {
    foreach ($type->items as $node) {
      reol_feed_feeds_add_video($type->feed, $node);
    }
  }

  // Add author portraits to feeds.
  for ($i = 0; $i < $feed_item_count; $i++) {
    $e_item = $e_feed->addChild('item');

    $a_item = $e_feed->addChild('item');

  }

  // Add review to feeds.
  for ($i = 0; $i < $feed_item_count; $i++) {
    $e_item = $e_feed->addChild('item');

    $a_item = $e_feed->addChild('item');

  }
}

/**
 * Add a news item to a feed.
 *
 * @param SimpleXMLElement $feed
 *   The element to add news item to.
 * @param StdClass $node
 *   The news item object.
 */
function reol_feed_feeds_add_news_item($feed, $node) {
  $node_wrapper = entity_metadata_wrapper('node', $node);

  $item = $feed->addChild('item');
  $item->addChild('guid', $node->nid);
  $item->addChild('source', "ereolen");
  $item->addChild('type', "news");
  $item->addChild('date', $node_wrapper->created->value());
  $item->addChild('title', $node_wrapper->title->value());

  // To make sure that we get either summary, or trimmed body,
  // do it this way:
  $body = field_get_items('node', $node, 'body');
  $summary = field_view_value('node', $node, 'body', $body[0], 'teaser');
  $item->addChild('description', strip_tags($summary['#markup']));

  $body = $node_wrapper->body->value();
  $item->addChild('content', strip_tags($body['safe_value']));

  global $base_url;

  $node_link = $item->addChild('link', $base_url . '/node/' . $node->nid);
  $node_link->addAttribute('type', 'content');

  $thumb = $node_wrapper->field_ding_news_list_image->value();
  $thumb_link = $item->addChild('link', file_create_url($thumb['uri']));
  $thumb_link->addAttribute('type', 'thumbnail');

  // Add ISBN numbers of referenced titles.
  $isbns = $item->addChild('isbns');

  $lang = field_language('node', $node, 'field_ding_news_materials');
  $materials = $node->field_ding_news_materials[$lang];

  if ($materials) {
    // Add referenced materials.
    foreach ($materials as $material) {
      $tid = $material['value']->endpoints[$lang][1]['entity_id'];
      $ting_objects = entity_load('ting_object', array($tid));
      $ting_object = $ting_objects[$tid];

      // Make sure we have cover.
      ting_covers_load(array($ting_object->id));

      $isbn = $isbns->addChild('isbn', reol_base_get_isbn($ting_object->localId));
      $isbn->addAttribute('cover', file_create_url(ting_covers_object_path($ting_object->id)));
    }
  }
}

/**
 * Add a video to a feed.
 *
 * @param SimpleXMLElement $feed
 *   The element to add video to.
 * @param StdClass $node
 *   The video object.
 */
function reol_feed_feeds_add_video($feed, $node) {
  $node_wrapper = entity_metadata_wrapper('node', $node);

  $item = $feed->addChild('item');
  $item->addChild('guid', $node->nid);
  $item->addChild('source', "ereolen");
  $item->addChild('type', "video");
  $item->addChild('date', $node_wrapper->created->value());
  $item->addChild('title', $node_wrapper->title->value());

  $body = $node_wrapper->body->value();
  $item->addChild('description', strip_tags($body['safe_value']));

  global $base_url;

  $node_link = $item->addChild('link', $base_url . '/node/' . $node->nid);
  $node_link->addAttribute('type', 'content');

  $file_value = $node_wrapper->field_video->value();
  $files = entity_load('file', array($file_value['fid']));
  $file = $files[$file_value['fid']];

  $view = file_view($file, 'video_frontpage');
  $thumb_link = $item->addChild('link', file_create_url($view['file']['#path']));
  $thumb_link->addAttribute('type', 'thumbnail');
}
