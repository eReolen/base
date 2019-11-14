<?php
/**
 * @file
 * Default audio player template.
 */
?>
<?php if (!is_null($internal_order_number)) : ?>
  <iframe src="<?php echo variable_get('publizon_player_url', ''); ?>?o=<?php echo $internal_order_number; ?>" class="player"></iframe>
<?php else : ?>
  <iframe src="<?php echo variable_get('publizon_player_url', ''); ?>?i=<?php echo $isbn; ?>" class="player"></iframe>
<?php endif; ?>
