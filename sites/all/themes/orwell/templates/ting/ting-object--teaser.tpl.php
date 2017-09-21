<?php
/**
 * @file
 * Template to render objects from the Ting database.
 *
 * Available variables:
 * - $object: The TingClientObject instance we're rendering.
 * - $content: Render array of content.
 */
?>
<div class="material material--teaser <?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <div class="material--teaser__cover">
    <?php echo render($content['group_ting_object_teaser_left']['ting_cover']); ?>
  </div>
  <div class="material--teaser__content text">
    <div class="material--teaser__title">
      <?php echo render($content['group_ting_object_teaser_right']['ting_title']); ?>
    </div>
    <div class="material--teaser__author">
      <?php echo render($content['group_ting_object_teaser_right']['ting_author']); ?>
    </div>
    <div class="material--teaser__abstract">
      <?php echo render($content['group_ting_object_teaser_right']['ting_abstract']); ?>
    </div>
    <div class="material--teaser__subjects">
      <?php echo render($content['group_ting_object_teaser_right']['ting_subjects']); ?>
    </div>
  </div>
</div>
