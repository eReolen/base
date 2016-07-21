<div <?php if (!empty($css_id)) { print ' id="$css_id"'; } ?>>
  <?php if (!empty($content['header'])): ?>
    <div class="stacked-section header">
      <div class="header__inner">
        <?php print render($content['header']); ?>
      </div>
    </div>
  <?php endif; ?>

  <?php if (!empty($content['before_content'])): ?>
    <div class="stacked-section before-content">
      <div class="before-content__inner">
        <?php print render($content['before_content']); ?>
      </div>
    </div>
  <?php endif; ?>

  <?php if (!empty($content['main_content'])): ?>
    <div class="stacked-section main-content">
      <div class="main-content__inner">
        <?php print render($content['main_content']); ?>
      </div>
    </div>
  <?php endif; ?>

  <?php if (!empty($content['after_content'])): ?>
    <div class="stacked-section after-content">
      <div class="after-content__inner">
        <?php print render($content['after_content']); ?>
      </div>
    </div>
  <?php endif; ?>

  <?php if (!empty($content['bottom'])): ?>
    <div class="stacked-section bottom">
      <div class="bottom__inner">
        <?php print render($content['bottom']); ?>
      </div>
    </div>
  <?php endif; ?>
</div>
