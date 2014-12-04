<?php

/**
 * @file
 * Contains functions for generating the frontpage feed XMLs.
 */

/**
 * Generate feed for the frontpage items.
 */
function reol_feed_feeds_frontpage() {
  // Prepare XML.
  $e_feed = new SimpleXMLElement('<feed></feed>');
  $a_feed = new SimpleXMLElement('<feed></feed>');

  // Add news to feeds.
  reol_feed_feeds_add_items('article', $e_feed, $a_feed, 'reol_feed_feeds_add_news_item');

  // Add video to feeds.
  reol_feed_feeds_add_items('video', $e_feed, $a_feed, 'reol_feed_feeds_add_video');

  // Add author portraits to feeds.
  reol_feed_feeds_add_items('author_portrait', $e_feed, $a_feed, 'reol_feed_feeds_add_author_portrait');

  // Add review to feeds.
  module_load_include('inc', 'reol_review', 'includes/reol_review.reviews');
  $reviews = reol_review_get_reviews();
  foreach ($reviews as $t => $type_reviews) {
    // Determine where to put it.
    $feed = $e_feed;
    if ($t == 'audiobook') {
      $feed = $a_feed;
    }

    // Add x reviews.
    while (count($type_reviews) && $added < variable_get('reol_feed_frontpage_item_count', 2)) {
      $review_key = array_rand($type_reviews);
      reol_feed_feeds_add_review($feed, $type_reviews[$review_key]);
      unset($type_reviews[$review_key]);
    }
  }

  // Write feeds.
  reol_feed_write_feed(array(
    'type' => 'ebook',
    'filename' => 'frontpage.xml',
  ), $e_feed->asXML());
  reol_feed_write_feed(array(
    'type' => 'audiobook',
    'filename' => 'frontpage.xml',
  ), $a_feed->asXML());
}

/**
 * Add items to feed.
 *
 * @param string $type
 *   The node type to add.
 * @param SimpleXMLElement $e_feed
 *   The ebook feed to add to.
 * @param SimpleXMLElement $a_feed
 *   The audiobook feed to add to.
 * @param callable $add_callback
 *   The callback for adding the item to feed.
 */
function reol_feed_feeds_add_items($type, $e_feed, $a_feed, $add_callback) {
  $feed_item_count = variable_get('reol_feed_frontpage_item_count', 2);
  // Add item to feeds.
  $item_array = array(
    (object) array(
      'feed' => $e_feed,
      'items' => reol_feed_get_latest($type, 'ebook', $feed_item_count),
    ),
    (object) array(
      'feed' => $a_feed,
      'items' => reol_feed_get_latest($type, 'audiobook', $feed_item_count),
    ),
  );

  // Add the videos found to feed.
  foreach ($item_array as $type) {
    foreach ($type->items as $node) {
      $add_callback($type->feed, $node);
    }
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
  $item->guid = $node->nid;
  $item->type = "news";
  $item->date = $node_wrapper->created->value();
  $item->title = $node_wrapper->title->value();

  // To make sure that we get either summary, or trimmed body,
  // do it this way:
  $body = field_get_items('node', $node, 'body');
  $summary = field_view_value('node', $node, 'body', $body[0], 'teaser');
  $item->description = strip_tags($summary['#markup']);

  $body = $node_wrapper->body->value();
  $item->content = strip_tags($body['safe_value']);

  global $base_url;

  $node_link = $item->addChild('link');
  $node_link->{0} = $base_url . '/node/' . $node->nid;
  $node_link->addAttribute('type', 'content');

  $thumb = $node_wrapper->field_ding_news_list_image->value();
  $thumb_link = $item->addChild('link');
  $thumb_link->{0} = file_create_url($thumb['uri']);
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

      $isbn = $isbns->addChild('isbn');
      $isbn->{0} = reol_base_get_isbn($ting_object->localId);
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
  $item->guid = $node->nid;
  $item->type = "video";
  $item->date = $node_wrapper->created->value();
  $item->title = $node_wrapper->title->value();

  $body = $node_wrapper->body->value();
  $item->description = strip_tags($body['safe_value']);

  global $base_url;

  $node_link = $item->addChild('link');
  $node_link->{0} = $base_url . '/node/' . $node->nid;
  $node_link->addAttribute('type', 'content');

  $file_value = $node_wrapper->field_video->value();
  $files = entity_load('file', array($file_value['fid']));
  $file = $files[$file_value['fid']];

  $view = file_view($file, 'video_frontpage');
  $thumb_link = $item->addChild('link');
  $thumb_link->{0} = file_create_url($view['file']['#path']);
  $thumb_link->addAttribute('type', 'thumbnail');
}

/**
 * Add an author portrait to feed.
 *
 * @param SimpleXMLElement $feed
 *   The element to add the author portrait to.
 * @param StdClass $node
 *   The author portrait object.
 */
function reol_feed_feeds_add_author_portrait($feed, $node) {
  $node_wrapper = entity_metadata_wrapper('node', $node);

  $item = $feed->addChild('item');
  $item->guid = $node->nid;
  $item->type = "author";
  $item->date = $node_wrapper->created->value();
  $item->title = $node_wrapper->title->value();

  $body = $node_wrapper->body->value();
  $item->description = strip_tags($body['safe_value']);

  global $base_url;

  $node_link = $item->addChild('link');
  $node_link->{0} = $base_url . '/node/' . $node->nid;
  $node_link->addAttribute('type', 'content');

  $thumb = $node_wrapper->field_portrait->value();
  $thumb_link = $item->addChild('link');
  $thumb_link->{0} = file_create_url($thumb['uri']);
  $thumb_link->addAttribute('type', 'thumbnail');
}

/**
 * Add a review to feed.
 *
 * @param SimpleXMLElement $feed
 *   The element to add the review to.
 * @param StdClass $review
 *   The review object.
 */
function reol_feed_feeds_add_review($feed, $review) {
  $item = $feed->addChild('item');

  $ting_object = ding_entity_load($review->ding_entity_id);

  $item->guid = $review->nid;
  $item->type = "review";
  $item->title = $ting_object->title;
  $item->date = $review->credate;
  $item->description = $review->description;
  $authors = $ting_object->getCreators();
  $item->author = $authors[0];

  global $base_url;

  $node_link = $item->addChild('link');
  $node_link->{0} = $review->link;
  $node_link->addAttribute('type', 'content');

  // Make sure we have cover.
  ting_covers_load(array($ting_object->id));

  $cover_uri = file_create_url(ting_covers_object_path($ting_object->id));

  $thumb_link = $item->addChild('link');
  $thumb_link->{0} = $cover_uri;
  $thumb_link->addAttribute('type', 'thumbnail');

  $isbn = $item->addChild('isbn');
  $isbn->{0} = reol_base_get_isbn($ting_object->localId);
  $isbn->addAttribute('cover', $cover_uri);
}
