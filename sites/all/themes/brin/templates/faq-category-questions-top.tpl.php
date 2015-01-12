<?php

/**
 * @file
 * Template file for the questions section of the FAQ page if set to show
 * categorized questions at the top of the page.
 */

?>
<div class="faq-menu">
  <a class="faq-header-link" href="#category-<?php echo $term->tid; ?>">
    <span class="faq-header">
      <?php print $header_title; ?> (<?php print $question_count; ?>)
    </span>
  </a>
</div>
