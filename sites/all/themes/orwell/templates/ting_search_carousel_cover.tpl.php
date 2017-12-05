<?php

/**
 * @file
 * Render cover placeholder.
 *
 * This template is only used for placeholders, so render it as much like
 * ting_object in compact display mode as needed by the styling.
 *
 * Use non-breaking spaces to ensure that title and creator uses as much space
 * as the real thing.
 */
?>
<div class="ting-object view-mode-compact imagestyle-ereol-cover-base clearfix">
  <div class="ting-cover-wrapper">
    <div class="ting-cover ting-cover-processed search-carousel-cover-image">
      <?php print render($image); ?>
    </div>
  </div>
  <div class="group-overlay field-group-div">
    <div class="field field-name-ting-title field-type-ting-title field-label-hidden">
      <h2><?php print $title; ?>&nbsp;</h2>
    </div>
    <div class="field field-name-ting-author field-type-ting-author field-label-hidden">
      <div class="field-item even"><?php print $creator; ?>&nbsp;</div>
    </div>
  </div>
</div>
