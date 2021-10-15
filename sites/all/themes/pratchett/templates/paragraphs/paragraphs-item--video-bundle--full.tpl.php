<?php

  /**
   * @file
   * Render a video bundle paragraph.
   */
?>
<?php
  // @see https://drupal.stackexchange.com/a/32518
  $paragraphs_item_wrapper = $paragraphs_item->wrapper();
?>
<div class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <div class="content"<?php print $content_attributes; ?>>
    <div class="video_bundle__video-wrapper">
      <h2 class="video_bundle__title"><?php print $paragraphs_item_wrapper->field_video_title->value(); ?></h2>
      <div class="video_bundle__video">
        <?php
          print render($content['field_video_node']);
        ?>
      </div>
      <?php if (!empty($paragraphs_item_wrapper->field_video_description->value())): ?>
        <div class="video_bundle__description"><?php print $paragraphs_item_wrapper->field_video_description->value(); ?></div>
      <?php endif ?>
    </div>
    <?php // @fixme This will render another h2 header ?>
    <div class="video_bundle__carousel-wrapper material-carousel-colored">
      <?php
        print render($content['field_carousel']);
      ?>
    </div>
  </div>
</div>
