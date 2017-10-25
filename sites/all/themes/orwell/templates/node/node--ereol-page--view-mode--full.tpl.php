<?php

/**
 * @file
 * Page full view mode.
 */
dpm($content);
?>
<div class="page <?php print $classes; ?>">
  <div class="content-wrapper">
    <div class="page__content">
      <h2 class="page__title"><?php print $title; ?></h2>
      <div class="page__body text">
        <?php print render($content['body']); ?>
      </div>
    </div>
  </div>
</div>
