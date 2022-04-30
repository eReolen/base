<?php

/**
 * @file
 * Default e-book reader template.
 *
 * @see https://docs.pubhub.dk/Reader/2.1.0/Pubhub_Reader_2.1.0.pdf
 */
?>
<script defer type="module" src="<?php print $reader_url; ?>/<?php print $reader_version; ?>/js/chunk-vendors.js"></script>
<script defer type="module" src="<?php print $reader_url; ?>/<?php print $reader_version; ?>/js/app.js"></script>
<script defer src="<?php print $reader_url; ?>/<?php print $reader_version; ?>/js/chunk-vendors-legacy.js" nomodule></script>
<script defer src="<?php print $reader_url; ?>/<?php print $reader_version; ?>/js/app-legacy.js" nomodule></script>

<?php if (isset($order_number)) : ?>
  <div id="pubhub-reader" environment="<?php print $reader_environment ?>" close-href="javascript:window.history.back()" order-id="<?php echo $order_number; ?>"></div>
<?php elseif (isset($isbn)) : ?>
  <div id="pubhub-reader" environment="<?php print $reader_environment ?>" close-href="javascript:window.history.back()" identifier="<?php echo $isbn; ?>"></div>
<?php endif; ?>
