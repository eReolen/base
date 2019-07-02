<?php

/**
 * @file
 * Template for view mode default of Breol News node type.
 */
?>

<div class="article article--breol-news--teaser" <?php print $attributes; ?>>
  <h2<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>

  <div class="content"<?php print $content_attributes; ?>>
    <a href="<?php print $node_url; ?>">
      <?php
        // We hide the comments and links now so that we can render them later.
        hide($content['comments']);
        hide($content['links']);
        print render($content);
      ?>
    </a>
  </div>
</div>
