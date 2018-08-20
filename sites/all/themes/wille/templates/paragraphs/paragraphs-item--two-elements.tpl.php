<?php

/**
 * @file
 * Render two elements paragraph.
 */
?>
<div class="two-elements <?php print $classes; ?>"<?php print $attributes; ?>>
  <div class="two-elements--primary">
    <?php print render($content['field_two_elements_primary']) ?>
  </div>
  <div class="two-elements--secondary">
    <?php print render($content['field_two_elements_secondary']) ?>
  </div>
</div>
