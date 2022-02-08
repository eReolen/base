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

    <?php if (!empty($content['field_promoted_materials'])): ?>
      <div class="video_bundle__promoted-materials-wrapper">
        <div class="video_bundle__promoted-materials-header">
          <?php if (!empty($paragraphs_item_wrapper->field_promoted_materials_title->value())): ?>
            <div class="video_bundle__promoted-materials-title">
              <?php print $paragraphs_item_wrapper->field_promoted_materials_title->value(); ?>
            </div>
          <?php endif ?>
          <?php if (!empty($paragraphs_item_wrapper->field_search_string->value())): ?>
            <div class="video_bundle__promoted-materials-see-more">
              <?php $search_url = '/search/ting/'.rawurlencode($paragraphs_item_wrapper->field_search_string->value()); ?>
              <a href="<?php print $search_url ?>"><?php print t('See more') ?></a>
            </div>
          <?php endif ?>
        </div>

        <div class="video_bundle__promoted-materials-body">
          <?php print render($content['field_promoted_materials']); ?>
        </div>
      </div>
    <?php endif ?>
  </div>
</div>
