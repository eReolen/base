<?php
/**
 * @file
 * reader.tpl.php
 * Custom page for implementing the reader.
 */
?>
<!doctype html>
<html>
<head>
  <title>Pubhub Online Reader</title>
  <meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1">
  <meta name="viewport" content="width=device-width, initial-scale=1.0, minimum-scale=1.0, maximum-scale=1.0, user-scalable=no">
  <meta name="format-detection" content="telephone=no" />
  <meta name="google" value="notranslate" />
  <meta http-equiv="cache-control" content="no-cache, no-store">
  <meta http-equiv="pragma" content="no-cache">
  <meta http-equiv="expires" content="-1">
  <link rel="stylesheet" type="text/css" href="<?php echo variable_get('publizon_reader_url', ''); ?>/scripts/reader-<?php echo $reader_version ?>/css">
  <script src="<?php echo variable_get('publizon_reader_url', ''); ?>/scripts/reader-<?php echo $reader_version; ?>/js" type="text/javascript"></script>
</head>
<body>
<div
  <?php if (isset($retailer_order_number)) : ?>
    data-id="<?php echo $retailer_order_number; ?>"
  <?php elseif (isset($isbn)) : ?>
    data-isbn="<?php echo $isbn; ?>"
  <?php endif; ?>
  id="reader-container" data-reader-version="<?php echo $reader_version ?>" data-url="<?php echo variable_get('publizon_reader_stream_url', ''); ?>" data-images-url="<?php echo variable_get('publizon_reader_url', ''); ?>"></div>

  <script src="/<?php echo drupal_get_path('module', 'reol_use_loan') . '/js/reader_standalone.js'; ?>" type="text/javascript"></script>
</body>
</html>
