<?php

/**
 * @file
 * Template to render objects from the Ting database.
 *
 * Available variables:
 * - $object: The TingClientObject instance we're rendering.
 * - $content: Render array of content.
 */
 // dpm($content);
?>

<?php if (!empty($content['ting_primary_object'])) : ?>
  <?php print render($content['ting_primary_object']); ?>
<?php else : ?>
  <div class="material material--teaser <?php print $classes; ?> clearfix"<?php print $attributes; ?>>
    <div class="material__cover material__cover--teaser">
      <?php echo render($content['group_ting_object_teaser_left']['ting_cover']); ?>
    </div>
    <div class="material__content text">
      <div class="material__rating">
        <?php echo render($content['group_ting_object_teaser_right']['ding_entity_rating_action']); ?>
        <?php echo render($content['group_ting_object_teaser_right']['ding_entity_rating_result']); ?>
      </div>
      <div class="material__title">
        <?php echo render($content['group_ting_object_teaser_right']['ting_title']); ?>
      </div>
      <div class="material__author">
        <?php echo render($content['group_ting_object_teaser_right']['ting_author']); ?>
      </div>
      <div class="material__abstract">
        <?php echo render($content['group_ting_object_teaser_right']['ting_abstract']); ?>
      </div>
      <div class="material__subjects">
        <?php echo render($content['group_ting_object_teaser_right']['ting_subjects']); ?>
      </div>
      <div class="material__series material__series--desktop">
        <?php echo render($content['group_ting_object_teaser_right']['ting_series']); ?>
      </div>
    </div>
  </div>
<?php endif; ?>
