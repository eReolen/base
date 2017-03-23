<div class="article article--teaser article--teaser--small <?php print $classes; ?>">
  <?php if (!empty($content['field_breol_cover_image'])) :?>
    <?php print render($content['field_breol_cover_image']); ?>
  <?php endif; ?>
  <?php if (!empty($content['field_breol_video'])) :?>
    <?php print render($content['field_breol_video']); ?>
    <i class="icon-play play_icon"></i>
  <?php endif; ?>
  <div class="article--teaser__title">
    <?php print($teaser_title); ?>
  </div>
  <div class="article--teaser__overlay" <?php if(!empty($rgba_background)) print $rgba_background; ?>></div>
  <div class="article--teaser__caption">
    <?php print($teaser_caption); ?>
  </div>
  <?php print(render($teaser_link)); ?>
</div>
