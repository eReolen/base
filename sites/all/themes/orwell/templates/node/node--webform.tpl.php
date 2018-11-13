<?php

/**
 * @file
 * Webform template.
 */
?>
<div class="webform <?php print $classes; ?>">
  <h2 class="webform__title"><?php print $title; ?></h2>
  <?php print render($content); ?>
</div>
