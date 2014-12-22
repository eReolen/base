<?php
/**
 * @file
 * Template file for carousel collection.
 */

// As we have no way of altering the data sent to this template,
// we have to have code here. We are keeping it simple.
$entity = ding_entity_load($collection->id);
$type = reol_base_get_type_name($entity->type);

?>
<li class="rs-carousel-item">
  <a href="ting/collection/<?php print $collection->id; ?>" class="rs-carousel-item-image type-icon type-icon-<?php echo $type; ?>"><img src="<?php print $collection->image; ?>" alt=""/></a>
  <a href="ting/collection/<?php print $collection->id; ?>" class="rs-carousel-item-title"><?php print check_plain($collection->title); ?></a>
</li>
