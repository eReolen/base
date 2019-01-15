<?php

/**
 * @file
 * Promoted review paragraph bundle.
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
<div class="review <?php print $classes; ?>">
  <a href="<?php print render($content['field_promoted_review_link'][0]['#element']['url']); ?>" target="_blank">
    <div class="review__wrapper">
      <div class="review__cover">
        <div class="ting-cover-wrapper">
            <div class="ting-cover ting-cover-processed">
              <?php print render($content['field_billede'][0]); ?>
            </div>
          </div>
      </div>
      <div class="review__content">
        <div class="review__head">
          <h4><?php print render($content['field_titel'][0]); ?></h4>
        </div>
        <div class="ting-cover-wrapper">
          <div class="ting-cover ting-cover-processed">
            <?php print render($content['field_billede'][0]); ?>
          </div>
        </div>
        <div class="review__meta">
          <?php print render($content['field_tekst'][0]); ?>
        </div>
      </div>
    </div>
    <?php print $icons; ?>
  </a>
</div>
