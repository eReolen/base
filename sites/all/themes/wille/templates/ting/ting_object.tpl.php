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
  <?php hide($content['group_ting_object_right_column']['group_material_details']); ?>
  <?php hide($content['group_ting_object_right_column']['ting_relations']); ?>
  <?php echo render($content); ?>
  <?php if (!empty($content['group_ting_object_right_column']['group_material_details'])) : ?>
    <div class="group-material-details field-group-div ting-object-collapsible-enabled">
        <?php echo render($content['group_ting_object_right_column']['group_material_details']); ?>
    </div>
  <?php endif; ?>
  <?php if (!empty($content['group_ting_object_right_column']['ting_relations']['#groups']['dbcaddi:hasDescriptionFromPublisher'])) : ?>
    <div class="ting-object-related-item last ting-object-collapsible-enabled">
        <?php echo render($content['group_ting_object_right_column']['ting_relations']['#groups']['dbcaddi:hasDescriptionFromPublisher']); ?>
    </div>
  <?php endif; ?>
</div>
