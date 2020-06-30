<?php

/**
 * @file
 * Render button paragraph.
 */
?>
<div class='see-all-news'>
  <?php
  print l($button_text, '/nyheder', array(
    'attributes' => array(
      'class' => 'more-link btn',
    ),
    'query' => $button_query,
  )); ?>
</div>
