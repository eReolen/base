<?php

/**
 * @file
 * Template for view mode default of Breol News node type.
 */

// Start by hiding all vontent.
hide($content);
?>

<div class="article article--breol-news">
  <div class="article__cover">
    <div class="article__cover__image" style="background-image: url(<?php print($file_uri); ?>)">
      <div class="article__cover__image__overlay"></div>
      <div class="article__content">
        <h2><?php print($node->title); ?></h2>
        <?php print render($content['body']); ?>
      </div>
    </div>
  </div>
  <div class="article__carousel">
    <h1>In here the carousel will be placed</h1>
  </div>
</div>
