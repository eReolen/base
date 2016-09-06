<div id="page<?php print $css_id ? " $css_id" : ''; ?>" class="<?php print $classes; ?>">
  <?php if (!empty($content['branding']) || !empty($content['header']) || !empty($content['navigation'])): ?>
    <header class="site-header">
      <div class="site-header__inner">
        <?php if (!empty($content['branding'])): ?>
          <section class="topbar">
            <div class="topbar-inner">
              <div class="logo">
                <a href="/">eReolen Go!</a>
                <div class="top-burger"><i class="icon-menu"></i></div>
              </div>
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
      </div>
    </header>
  <?php endif; ?>

  <div class="navigation">
    <?php if (!empty($content['navigation'])): ?>
      <section class="navigation-wrapper">
        <div class="navigation-inner">
          <?php print render($content['navigation']); ?>
        </div>
      </section>
    <?php endif; ?>
  </div>

  <div class="main-header">
    <div class="main-content-header__inner">
      <?php print render($content['content_header']); ?>
    </div>
  </div>

  <div class="organic-element organic-element--content">
    <?php print $organic_svg ?>
  </div>

  <div class="main-content-wrapper">
    <div class="main-content-wrapper__inner">
      <?php print render($content['content']); ?>
    </div>
  </div>

  <?php if (!empty($content['footer'])): ?>

    <div class="organic-element organic-element--footer">
      <?php print $organic_svg ?>
    </div>

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
