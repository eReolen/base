<?php

/**
 * @file
 * Page full view mode.
 */
?>
<div class="page <?php print $classes; ?>">
  <div class="content-wrapper">
    <div class="page__content">
      <h2 class="page__title"><?php print $title; ?></h2>
      <div class="page__body text">
        <?php print render($content['field_ereol_page_body']); ?>
      </div>
      <div class="page__files text">
        <?php print render($content['field_ereol_page_files']); ?>
      </div>
    </div>
  </div>
</div>
