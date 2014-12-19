<?php
/**
 * @file
 * latest.tpl.php
 * This template shows latest titles.
 */

?>
<div class="latest-titles">
  <?php $first = "first "; ?>
  <?php foreach ($ting_objects as $k => $ting_object) : ?>
    <?php $last = $k == count($ting_objects) - 1 ? 'last ' : ''; ?>
    <?php $zebra = $k % 2 == 0 ? 'odd' : 'even'; ?>
    <div class="latest-title <?php echo $first; ?><?php echo $last; ?><?php echo $zebra; ?>"><?php echo render($ting_object); ?></div>
    <?php $first = ''; ?>
  <?php endforeach; ?>
</div>
