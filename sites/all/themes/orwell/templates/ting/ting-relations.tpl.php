<?php

/**
 * @file
 * Default template file for ting_relations theme function.
 *
 * Available variables:
 *   - $attributes: Mainly string with the rendered class variables.
 *   - $attributes_array: Array with the attributes.
 *   - $title: The relation group title.
 *   - $source: The name of the type of relations in this group.
 *   - $relations: The relations inside this groups of relations, which should
 *     be rendered as ting_relation.
 */
?>
<div class="ting-relations">
  <?php if (!empty($title)): ?>
    <div class="ting-relations__title">
      <h2><?php print $title; ?>:</h2>
    </div>
  <?php endif; ?>
  <div class="ting-relations__content">
    <?php foreach ($relations as $relation) : ?>
      <?php print render($relation); ?>
    <?php endforeach; ?>
  </div>
</div>
