<?php

  /**
   * @file
   * Render a video bundle paragraph.
   */
?>
<div class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <div class="content"<?php print $content_attributes; ?>>
    <div class="video_bundle__video-wrapper">
      <?php // @todo How do we render a raw field value? ?>
      <h2 class="video_bundle__header"><?php print $field_video_title[0]['safe_value']; ?></h2>
      <div class="video_bundle__video"><?php print render($content['field_video_node']); ?></div>
      <?php if (isset($field_video_description[0]['safe_value'])): ?>
        <div class="video_bundle__description"><?php print $field_video_description[0]['safe_value']; ?></div>
      <?php endif ?>
    </div>
    <?php // @todo This will render another h2 header ?>
    <div class="video_bundle__carousel"><?php print render($content['field_carousel']); ?></div>
  </div>
</div>
