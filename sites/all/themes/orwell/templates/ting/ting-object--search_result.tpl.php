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
      <div class="material__metadata">
        <div class="material__language">
          <?php echo $object->getLanguage() ?>
        </div>

        <?php if (isset($series['number'], $series['series'])): ?>
          <div class="material__number-in-series">
            <span class="material__series-number"><?php echo $series['number']; ?></span><span class="material__series-series"><?php echo $series['series']; ?></span>
          </div>
        <?php endif ?>
      </div>

      <div class="material__title">
        <?php echo render($content['group_ting_object_teaser_right']['ting_title']); ?>
      </div>
      <div class="material__author">
        <?php echo render($content['group_ting_object_teaser_right']['ting_author']); ?>
      </div>
  </div>
<?php endif; ?>
