<?php
/**
 * @file
 * Theming of carousel item.
 */

// As we have no way of altering the data sent to this template,
// we have to have code here. We are keeping it simple.
$entity = ding_entity_load($collection->id);
$classes = implode(' ', _wille_type_icon_classes(reol_base_get_type_name($entity->type), $entity->reply->on_quota));
?>
<li class="carousel-item">
  <a href="/ting/collection/<?php print $collection->id; ?>" class="carousel-item-image <?php print $classes; ?>"><img src="<?php print $collection->image; ?>" alt="" width="200" height="290"/></a>
  <a href="/ting/collection/<?php print $collection->id; ?>" class="carousel-item-title"><?php print check_plain($collection->title); ?></a>
  <a href="/ting/collection/<?php print $collection->id; ?>" class="carousel-item-creator"><?php print check_plain($collection->creator); ?></a>
</li>
