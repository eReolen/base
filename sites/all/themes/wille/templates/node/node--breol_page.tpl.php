<?php

/**
 * @file
 * Template for view mode default of Breol Page node type.
 */
?>
<div class="article article--breol_page">
  <h2 class="title article--breol_page--title">
    <?php print $title; ?>
  </h2>
  <?php print render($content['body']); ?>
</div>
