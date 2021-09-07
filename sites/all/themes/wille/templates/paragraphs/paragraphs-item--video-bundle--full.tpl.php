<?php

  /**
   * @file
   * Render a video bundle paragraph.
   */
?>
<div class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <div class="content"<?php print $content_attributes; ?>>
    <?php
      print render($content);
    ?>
  </div>
</div>
