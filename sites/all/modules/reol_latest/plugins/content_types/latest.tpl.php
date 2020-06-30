<?php

/**
 * @file
 * Latest.tpl.php
 * This template shows latest titles.
 */
?>
<div class="latest-titles">
  <?php $first = "first "; ?>
  <?php foreach ($ting_objects as $k => $ting_object) : ?>
    <?php $last = $k == count($ting_objects) - 1 ? 'last ' : ''; ?>
    <?php $zebra = $k % 2 == 0 ? 'odd' : 'even'; ?>
    <a href="<?php echo $ting_object['link']; ?>" class="latest-title <?php echo $first; ?><?php echo $last; ?><?php echo $zebra; ?>"><?php echo render($ting_object['view']); ?></a>
    <?php $first = ''; ?>
  <?php endforeach; ?>
</div>
