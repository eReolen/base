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

<?php if (!empty($content['ting_primary_object'])) : ?>
  <?php print render($content['ting_primary_object']); ?>
<?php else : ?>
  <div class="material material--teaser <?php print $classes; ?> clearfix"<?php print $attributes; ?>>
    <div class="material__cover material__cover--teaser">
      <?php echo render($content['ting_cover']); ?>
    </div>
    <div class="material__content text">
      <div class="material__title">
        <?php echo render($content['group_text']['group_inner']['ting_title']); ?>
      </div>
      <div class="material__author">
        <?php echo render($content['group_text']['group_inner']['ting_author']); ?>
      </div>
      <div class="material__language">
        <?php echo $object->getLanguage() ?>
      </div>
      <div class="material__abstract">
        <?php if (!empty($content['ting_relations']['#groups']['dbcaddi:hasDescriptionFromPublisher'])): ?>
          <?php unset($content['ting_relations']['#groups']['dbcaddi:hasDescriptionFromPublisher']['#title']); ?>
          <?php echo render($content['ting_relations']['#groups']['dbcaddi:hasDescriptionFromPublisher']); ?>
        <?php else: ?>
          <?php echo render($content['group_text']['ting_abstract']); ?>
        <?php endif ?>
      </div>
      <div class="material__subjects">
        <?php echo render($content['group_text']['group_inner']['ting_details_subjects']); ?>
      </div>
      <div class="material__series material__series--desktop">
        <?php echo render($content['group_text']['group_inner']['ting_series']); ?>
      </div>
    </div>
  </div>
<?php endif; ?>
