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
  <div class="material__cover material__cover--teaser">
    <?php echo render($content['group_ting_left_col_collection']['ting_cover']); ?>
  </div>
  <div class="material__content text">
    <div class="material__title">
      <?php echo render($content['group_ting_right_col_collection']['ting_title']); ?>
    </div>
    <div class="material__author">
      <?php echo render($content['group_ting_right_col_collection']['ting_author']); ?>
    </div>
    <div class="material__language">
      <?php echo $object->getLanguage() ?>
    </div>
    <div class="material__abstract">
      <?php if (!empty($content['group_ting_right_col_collection']['ting_relations']['#groups']['dbcaddi:hasDescriptionFromPublisher'])) : ?>
        <?php unset($content['group_ting_right_col_collection']['ting_relations']['#groups']['dbcaddi:hasDescriptionFromPublisher']['#title']); ?>
        <div class="material__description-from-publisher"><?php echo render($content['group_ting_right_col_collection']['ting_relations']['#groups']['dbcaddi:hasDescriptionFromPublisher']); ?></div>
      <?php else: ?>
        <?php echo render($content['group_ting_right_col_collection']['ting_abstract']); ?>
      <?php endif; ?>
    </div>
    <div class="material__subjects">
      <?php echo render($content['group_ting_right_col_collection']['ting_subjects']); ?>
    </div>
    <div class="material__series">
      <?php echo render($content['group_ting_object_right_column']['ting_series']); ?>
    </div>
  </div>
</div>
