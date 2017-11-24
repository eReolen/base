<?php

/**
 * @file
 * Carousel articles placeholder.
 */
$classes = 'article-placeholder';
$node_url = $title = '';
$content = array(
  'body' => '',
);
$covers = array();

// Simply include the regular article teaser view, which we're trying to look
// like.
include 'node/node--article--view-mode--teaser.tpl.php';
?>
