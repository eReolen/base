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

  <main class="main-content">
    <a id="main-content" tabindex="-1"></a>
    <div class="main-content__inner">
      <?php print render($content['content']); ?>
    </div>
  </main>

  <?php if (!empty($content['footer'])): ?>
    <footer class="footer">
      <div class="footer__brand">

          <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo" class="branding__logo">
            <img src="/<?php print path_to_theme(); ?>/assets/svg/eReolen-Red.svg" alt="<?php print t('Home'); ?>" />
          </a>

      </div>
      <div class="footer__inner">
        <?php print render($content['footer']); ?>
      </div>

      <div class="footer__ddf">

          <a href="<?php print t('https://detdigitalefolkebibliotek.dk'); ?>" title="<?php print t('The Digital Public Library'); ?>" id="ddf-logo">
            <img src="/<?php print path_to_theme(); ?>/assets/svg/DetDigitaleFolkebibliotek_logo_RGB_neg.svg" alt="<?php print t('The Digital Public Library'); ?>" />
          </a>
          <p>
            <?php print t('eReolen is a part of The Digital Public Library'); ?><br/>
            <a href="<?php print t('https://detdigitalefolkebibliotek.dk'); ?>"><?php print t('Read more at detdigitalefolkebibliotek.dk'); ?></a>
          </p>

      </div>
    </footer>
  <?php endif; ?>

  <?php if (!empty($content['bottom'])): ?>
    <div class="bottom">
      <?php print render($content['bottom']); ?>
    </div>
  <?php endif; ?>

</div>
