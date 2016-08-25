<?php
/**
 * @file
 * Theming of carousel item.
 */

// As we have no way of altering the data sent to this template,
// we have to have code here. We are keeping it simple.
$cover_classes = '';
if (!isset($collection->placeholder)) {
  $entity = ding_entity_load($collection->id);
  $cover_classes = implode(' ', _wille_type_icon_classes(reol_base_get_type_name($entity->type), $entity->reply->on_quota));
}
?>
<li class="carousel-item <?php print $classes; ?>">
  <?php if ($path): ?>
    <a href="<?php print $path; ?>" class="carousel-item-link">
  <?php endif; ?>
      <div class="carousel-item-image <?php print $cover_classes; ?>"><?php print render($image); ?></div>
    <?php if ($title): ?>
      <div class="carousel-item-title"><?php print $title; ?></div>
    <?php endif; ?>
    <?php if ($creator): ?>
      <div class="carousel-item-creator"><?php print $creator; ?></div>
    <?php endif; ?>
  <?php if ($path): ?>
    </a>
  <?php endif; ?>
</li>
