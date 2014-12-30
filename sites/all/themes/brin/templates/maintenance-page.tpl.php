<?php
/**
 * @file
 * Brin theme implementation to display a single Drupal page while offline.
 */
?>
<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">

<head>
  <title><?php print $head_title; ?></title>
  <?php print $head; ?>
  <?php print $styles; ?>
  <?php print $scripts; ?>
</head>

<body class="<?php print $classes; ?>">
  <div id="page" class="reol-site-template">
    <header class="site-header">
      <div class="top"></div>
      <section class="topbar">
        <div class="topbar-inner">
          <div class="logo">
            <a href="/" title="Hjem" rel="home">
              <img src="/sites/all/themes/brin/logo.png" alt="Hjem">
            </a>
          </div>
        <div class="panel-pane pane-block pane-menu-menu-tabs-menu">
    </header>
    <div class="content-wrapper">
      <div class="content-inner">
        <div class="panel-pane pane-page-content">
          <div class="pane-content">
            <div class="panel-flexible default-layout clearfix">
              <div class="panel-flexible-inside default-layout-inside">
                <h2><?php echo t('Site offline'); ?></h2>
                <p><?php print $content; ?></p>
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>
</body>
</html>
