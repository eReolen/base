<?php

/**
 * @file
 * Template implementation for ding-availability-type.
 *
 * Available variables:
 * - label: Label for the type.
 * - links: The availability links.
 */
?>
<?php foreach ($links as $link) : ?>
  <?php print render($link['link']); ?>
<?php endforeach; ?>
