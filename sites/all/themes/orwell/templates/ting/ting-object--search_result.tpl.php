<?php

/**
 * @file
 * Template to render objects in search results.
 */

// Move the groups to where the template expects them.
$content['group_ting_object_teaser_left'] = $content['group_ting_left_col_search'];
unset($content['group_ting_left_col_search']);

$content['group_ting_object_teaser_right'] = $content['group_ting_right_col_search'];
unset($content['group_ting_right_col_search']);

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
      <div class="material__language">
        <div class="field field-name-ting-details-language field-type-ting-details-language field-label-inline">
          <div class="field-items">
            <div class="field-item even">
                <spann class="field-label"><?php echo t('Language'); ?>:</spann> <?php echo $object->getLanguage() ?>
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>
<?php endif; ?>
