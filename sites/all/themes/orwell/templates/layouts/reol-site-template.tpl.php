<?php

/**
 * @file
 * Override reol default site template.
 */
?>
<div id="page<?php print $css_id ? " $css_id" : ''; ?>" class="<?php print $classes; ?>">
  <?php if (!empty($content['branding']) || !empty($content['header']) || !empty($content['navigation']) || !empty($content['top'])): ?>
    <header class="site-header">
      <?php if (!empty($content['branding'])): ?>
        <div class="top">
          <?php print render($content['top']); ?>
        </div>
        <section class="topbar">
          <div class="topbar__inner">
            <?php print render($content['branding']); ?>
          </div>
        </section>
      <?php endif; ?>

      <?php if (!empty($content['header'])): ?>
        <section class="header-wrapper">
          <div class="header-inner">
            <?php print render($content['header']); ?>
          </div>
        </section>
      <?php endif; ?>

      <?php if (!empty($content['navigation'])): ?>
        <section class="navigation-wrapper js-topbar-menu">
          <div class="navigation__inner">
            <?php print render($content['navigation']); ?>
          </div>
        </section>
      <?php endif; ?>
    </header>
  <?php endif; ?>

  <div class="main-content">
    <div class="main-content__inner">
      <?php print render($content['content']); ?>
    </div>
  </div>

  <?php if (!empty($content['footer'])): ?>
    <footer class="footer">
      <div class="footer__inner">
        <?php print render($content['footer']); ?>
      </div>
    </footer>
  <?php endif; ?>

  <?php if (!empty($content['bottom'])): ?>
    <div class="bottom">
      <?php print render($content['bottom']); ?>
    </div>
  <?php endif; ?>

</div>
