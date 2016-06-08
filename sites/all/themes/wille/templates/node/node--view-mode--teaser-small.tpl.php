<div class="article article--teaser article--teaser--small">
  <?php if (!empty($content['field_breol_cover_image'])) :?>
    <?php print render($content['field_breol_cover_image']); ?>
  <?php endif; ?>
  <?php if (!empty($content['field_breol_video'])) :?>
    <?php print render($content['field_breol_video']); ?>
  <?php endif; ?>
  <div class="article--teaser__overlay"></div>
</div>
