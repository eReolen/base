<?php
/**
 * @File
 */
?>
<ul class="subject-menu">
  <?php foreach ($nodes as $key => $node) : ?>
    <li class="subject-item"><?php print drupal_render($content[$key]); ?></li>
  <?php endforeach; ?>
</ul>
