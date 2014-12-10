<?php

/**
 * @file
 * Template for view mode search_result of FAQ node type.
 */
?>

<div class="faq-search-result">
  <a href="<?php echo $link; ?>">
    <h3><?php echo $title; ?></h3>
    <div class="faq-answer">
      <?php echo render($content['body']); ?>
    </div>
  </a>
</div>
