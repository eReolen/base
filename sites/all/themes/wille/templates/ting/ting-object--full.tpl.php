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

    <div class="ting-object-wrapper">

      <div class="ting-object-col-1">
        <div class="ting-object-cover">
          <?php echo render($content['group_ting_object_left_column']); ?>
        </div>
        <div class="ting-object-buttons">
          <?php echo render($content['group_ting_object_right_column']['group_ting_object_right_a']['ding_entity_buttons']); ?>
        </div>
      </div>

      <div class="ting-object-col-2">
        <div class="ting-object-type">
        <?php echo render($content['group_ting_object_right_column']['group_ting_object_meta']['ting_type']); ?>
        </div>

        <div class="ting-object-title">
          <?php echo render($content['group_ting_object_right_column']['group_ting_object_meta']['ting_title']); ?>
        </div>

        <div class="ting-object-author">
          <?php echo render($content['group_ting_object_right_column']['group_ting_object_meta']['ting_author']); ?>
        </div>

        <div class="ting-object-description">
          <?php if (!empty($content['group_ting_object_right_column']['ting_relations']['#groups']['dbcaddi:hasDescriptionFromPublisher'])) : ?>
            <?php
              unset($content['group_ting_object_right_column']['ting_relations']['#groups']['dbcaddi:hasDescriptionFromPublisher']['#title']);
              echo render($content['group_ting_object_right_column']['ting_relations']['#groups']['dbcaddi:hasDescriptionFromPublisher']);
          ?>
          <?php else: ?>
            <?php echo render($content['group_ting_object_right_column']['group_ting_object_meta']['ting_abstract']); ?>
          <?php endif; ?>
        </div>

        <div class="ting-object-series">
          <?php echo render($content['group_ting_object_right_column']['group_ting_object_meta']['ting_series']); ?>
        </div>

        <?php if ($also_available): ?>
          <div class="ting-object-also-available">
            <div class="field-label"><?php print t('Also available as'); ?>: </div>
            <?php echo render($also_available); ?>
          </div>
        <?php endif; ?>

        <div class="ting-object-subjects">
          <span><?php print t('Subjects'); ?></span><?php echo render($content['group_ting_object_right_column']['group_ting_object_meta']['ting_subjects']); ?>
        </div>
      </div>

      <div class="ting-object-bottom">
        <?php if (!empty($content['group_ting_object_right_column']['group_material_details'])) : ?>
          <div class="group-material-details field-group-div ting-object-collapsible-enabled  ting-object-details">
            <?php echo render($content['group_ting_object_right_column']['group_material_details']); ?>
          </div>
        <?php endif; ?>

        <?php if (!empty($content['group_ting_object_right_column']['ting_relations']['#groups']['dbcaddi:hasDescriptionFromPublisher'])) : ?>
          <div class="group-material-details field-group-div ting-object-collapsible-enabled text ting-object-abstract">
            <h2><span><?php print t('Description from DBC'); ?></span></h2>
            <?php echo render($content['group_ting_object_right_column']['group_ting_object_meta']['ting_abstract']); ?>
          </div>
        <?php endif; ?>
      </div>
    </div>

  <?php endif; ?>
</div>
