<?php
/**
 * @file
 * listen.tpl.php
 * This template shows the listen widget for listening
 * to an audio book.
 */

$path = drupal_get_path('module', 'reol_use_loan');
$player_path = $path . '/player';

drupal_add_css($player_path . '/lib/bootstrap-3.2.0-dist/css/bootstrap.min.css');
drupal_add_css($player_path . '/css/styles.css');

drupal_add_js($path . '/js/jquery-define.js');
drupal_add_js($player_path . '/scripts/bootstrap-slider.js');
drupal_add_js($player_path . '/scripts/bowser.min.js');
drupal_add_js($player_path . '/scripts/tooltip.js');
drupal_add_js($player_path . '/scripts/modernizr2.7.1.min.js');
drupal_add_js($player_path . '/scripts/dragdealer.js');
drupal_add_js($player_path . '/scripts/player-ui-default-1.0.2.js');
drupal_add_js($player_path . '/scripts/player-kernel-1.0.3.min.js');
drupal_add_js($path . '/js/player.js');
?>

<div data-role="audiobook-player" data-id="<?php echo $internal_order_number; ?>">

</div>
