<?php
?>
<div class="container">
  <div class="fancy-box">
    <?php foreach($nodes as $index => $node) : ?>
      <div <?php print(drupal_attributes($layout[$index]['attributes'])); ?>>
        <?php print(breol_fancy_box_render_node($node, $layout[$index])); ?>
      </div>
    <?php endforeach; ?>
  </div>
</div>
