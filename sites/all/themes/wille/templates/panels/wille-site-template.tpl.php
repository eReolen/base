<?php

/**
 * @file
 * Todo missing short description in doc comment.
 */
?>
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

  <div class="organic-element organic-element--content"></div>

  <?php // @see ../cover-image.tpl.php ?>
  <?php $node = 'node' === arg(0) ? node_load(arg(1)) : NULL ?>
  <?php if (!$is_front && is_object($node) && 'inspiration' === $node->type): ?>
    <?php $wrapper = entity_metadata_wrapper('node', $node);
    $color = $wrapper->field_app_feed_color->value()['rgb'] ?? 'none';
    $image = $wrapper->field_app_feed_image->value();
    $image_url = isset($image['uri']) ? sprintf('url(%s)', file_create_url($image['uri'])) : 'none';
    $text_color = 'none' !== $color && '#000000' === reol_base_get_contrast_color($color) ? 'text-color-dark' : 'text-color-light';
    ?>
    <div class="banner-wrapper banner-wrapper--<?php print $node->type; ?> <?php print $text_color; ?>" style="background-color: <?php print $color; ?>">
      <div class="banner banner--<?php print $node->type?>" style="background-image: <?php print $image_url; ?>">
        <h2 class="title"><?php print $node->title; ?></h2>
      </div>
    </div>
  <?php endif ?>

  <div class="main-content-wrapper">
    <div class="main-content-wrapper__inner">
      <?php print render($content['content']); ?>
    </div>
  </div>

  <?php if (!empty($content['footer'])): ?>

    <footer class="footer">
      <div class="footer__inner">
        <?php print render($content['footer']); ?>
      </div>
      <div class="footer__ddf">
        <a href="<?php print t('https://detdigitalefolkebibliotek.dk'); ?>" title="<?php print t('The Digital Public Library'); ?>" id="ddf-logo">
          <img src="/<?php print path_to_theme(); ?>/assets/svg/DetDigitaleFolkebibliotek_logo_RGB_neg.svg" alt="<?php print t('The Digital Public Library'); ?>" />
        </a>
        <p>
          <?php print t('eReolenGO is a part of The Digital Public Library'); ?><br/>
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
