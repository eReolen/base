<div class="article article--teaser article--teaser--medium">
  <div class="article--teaser__type"><?php print($teaser_type); ?></div>
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
  <div class="article--teaser__caption">
    <?php print($teaser_caption); ?>
  </div>
  <?php print($teaser_link); ?>
</div>
