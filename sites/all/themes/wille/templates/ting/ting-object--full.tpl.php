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
<div class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <?php if ('ting_collection' === $bundle): ?>
    <?php echo render($content); ?>
  <?php else : ?>

    <?php hide($content['group_ting_object_right_column']['group_material_details']); ?>
    <?php hide($content['group_ting_object_right_column']['ting_relations']); ?>

    <?php echo render($content['group_ting_object_left_column']); ?>

    <div class="ting-object-right">
      <div id="ting-object-ting-object-full-group-ting-object-meta" class="ting-object-right-meta group-ting-object-meta field-group-div">
        <?php echo render($content['group_ting_object_right_column']['group_ting_object_meta']['ting_type']); ?>
        <?php echo render($content['group_ting_object_right_column']['group_ting_object_meta']['ting_title']); ?>
        <?php echo render($content['group_ting_object_right_column']['group_ting_object_meta']['ting_author']); ?>

        <?php if (!empty($content['group_ting_object_right_column']['ting_relations']['#groups']['dbcaddi:hasDescriptionFromPublisher'])) : ?>
          <?php
            unset($content['group_ting_object_right_column']['ting_relations']['#groups']['dbcaddi:hasDescriptionFromPublisher']['#title']);
            echo render($content['group_ting_object_right_column']['ting_relations']['#groups']['dbcaddi:hasDescriptionFromPublisher']);
          ?>
        <?php else: ?>
          <?php echo render($content['group_ting_object_right_column']['group_ting_object_meta']['ting_abstract']); ?>
        <?php endif; ?>

        <?php echo render($content['group_ting_object_right_column']['group_ting_object_meta']['ting_series']); ?>
        <?php if ($also_available): ?>
          <div class="material__also_available field field-label-inline clearfix">
            <div class="field-label"><?php print t('Also available as'); ?>: </div>
            <?php echo render($also_available); ?>
          </div>
        <?php endif; ?>
        <?php echo render($content['group_ting_object_right_column']['group_ting_object_meta']['ting_subjects']); ?>
      </div>
      <div id="ting-object-ting-object-full-group-ting-object-right-a" class="ting-object-right-actions group-ting-object-right-a field-group-div">
        <?php echo render($content['group_ting_object_right_column']['group_ting_object_right_a']['ding_entity_buttons']); ?>
      </div>
    </div>

    <?php if (!empty($content['group_ting_object_right_column']['group_material_details'])) : ?>
      <div class="group-material-details field-group-div ting-object-collapsible-enabled">
        <?php echo render($content['group_ting_object_right_column']['group_material_details']); ?>
      </div>
    <?php endif; ?>

    <?php if (!empty($content['group_ting_object_right_column']['ting_relations']['#groups']['dbcaddi:hasDescriptionFromPublisher'])) : ?>
      <div class="group-material-details field-group-div ting-object-collapsible-enabled text">
        <h2><span><?php print t('Description from DBC'); ?></span></h2>
        <?php echo render($content['group_ting_object_right_column']['group_ting_object_meta']['ting_abstract']); ?>
      </div>
    <?php endif; ?>
  <?php endif; ?>
</div>
