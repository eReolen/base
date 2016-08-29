<?php
/**
 * @file
 * Template file for ting_relations theme function.
 *
 * Render relations bare.
 */
?>
<?php foreach ($relations as $relation) : ?>
  <?php print render($relation); ?>
<?php endforeach; ?>
