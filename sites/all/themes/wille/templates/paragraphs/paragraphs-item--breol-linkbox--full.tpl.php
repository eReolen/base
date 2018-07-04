<?php

/**
 * @file
 * Default theme implementation for a single paragraph item.
 *
 * Available variables:
 * - $content: An array of content items. Use render($content) to print them
 *   all, or print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. By default the following classes are available, where
 *   the parts enclosed by {} are replaced by the appropriate values:
 *   - entity
 *   - entity-paragraphs-item
 *   - paragraphs-item-{bundle}
 *
 * Other variables:
 * - $classes_array: Array of html class attribute values. It is flattened into
 *   a string within the variable $classes.
 *
 * @see template_preprocess()
 * @see template_preprocess_entity()
 * @see template_process()
 */
?>

<a href="<?php print $href ?>" class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <div class="linkbox__content"<?php print $content_attributes; ?>>
    <?php if (!empty($header)): ?>
      <h3 class="linkbox__header"><?php print $header; ?></h3>
    <?php endif; ?>
    <?php if (!empty($title)): ?>
      <h2 class="linkbox__title"><?php print $title; ?></h2>
    <?php endif; ?>
  </div>
  <?php if (!empty($image_url)): ?>
    <div class="linkbox__image" style="background-image: url('<?php print $image_url; ?>');"></div>
  <?php endif; ?>
</a>
