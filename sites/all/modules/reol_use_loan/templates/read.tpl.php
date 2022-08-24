<?php

/**
 * @file
 * Default e-book reader template.
 *
 * @see https://docs.pubhub.dk/Reader/Pubhub_Reader_2.1.1.pdf
 */
?>
<script defer type="module" src="<?php print $reader_url; ?>/<?php print $reader_version; ?>/js/chunk-vendors.js"></script>
<script defer type="module" src="<?php print $reader_url; ?>/<?php print $reader_version; ?>/js/app.js"></script>
<script defer src="<?php print $reader_url; ?>/<?php print $reader_version; ?>/js/chunk-vendors-legacy.js" nomodule></script>
<script defer src="<?php print $reader_url; ?>/<?php print $reader_version; ?>/js/app-legacy.js" nomodule></script>

<?php
  $attributes = [
    'environment' => $reader_environment,
    'close-href' => 'javascript:window.history.back()',
    'search-enabled' => $reader_search_enabled ? 'true' : 'false',
    'annotations-enabled' => $reader_annotations_enabled ? 'true' : 'false',
    'content-selection-enabled' => $reader_content_selection_enabled ? 'true' : 'false',
    'mouse-swipe-navigation-enabled' => $reader_mouse_swipe_navigation_enabled ? 'true' : 'false',
  ];

  if (isset($order_number)) {
    $attributes['order-id'] = $order_number;
  }
  elseif (isset($isbn)) {
    $attributes['identifier'] = $isbn;
  }
?>

<div id="pubhub-reader" <?php print drupal_attributes($attributes) ?>></div>
