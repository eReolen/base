<?php

/**
 * @file
 * Template to render objects from the Ting database.
 *
 * Available variables:
 * - $object: The TingClientObject instance we're rendering.
 * - $content: Render array of content.
 */
?>
<?php if ($bundle == 'ting_collection') : ?>
  <div class="content-wrapper content-wrapper--material">
    <?php print render($content); ?>
  </div>
<?php else : ?>
  <div class="content-wrapper content-wrapper--material">
    <div class="material material--full<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
      <div class="material__aside">
        <div class="material__cover">
          <?php echo render($content['group_ting_object_left_column']['ting_cover']); ?>
        </div>

        <div class="material__buttons material__buttons--desktop mobile-only">
          <?php echo render($content['group_ting_object_right_column']['group_ting_object_right_a']['ding_entity_buttons']); ?>
        </div>

        <div class="material__buttons desktop-only">
          <?php echo render($content['group_ting_object_right_column']['group_ting_object_right_a']['ding_entity_buttons']); ?>
        </div>
      </div>

      <div class="material__content">
        <div class="material__title">
          <?php echo render($content['group_ting_object_right_column']['group_ting_object_meta']['ting_title']); ?>
        </div>

        <div class="material__author">
          <?php echo render($content['group_ting_object_right_column']['group_ting_object_meta']['ting_author']); ?>
        </div>

        <?php if (!empty($content['group_ting_object_right_column']['ting_relations']['#groups']['dbcaddi:hasDescriptionFromPublisher'])) : ?>
          <div class="material__details text">
            <?php
              unset($content['group_ting_object_right_column']['ting_relations']['#groups']['dbcaddi:hasDescriptionFromPublisher']['#title']);
              echo render($content['group_ting_object_right_column']['ting_relations']['#groups']['dbcaddi:hasDescriptionFromPublisher']);
            ?>
          </div>
        <?php else: ?>
          <div class="material__abstract text">
            <?php echo render($content['group_ting_object_right_column']['group_ting_object_right_c']['ting_abstract']); ?>
          </div>
        <?php endif; ?>

        <div class="material__subjects text">
          <?php echo render($content['group_ting_object_right_column']['group_ting_object_right_c']['ting_subjects']); ?>
        </div>

        <div class="material__series material__series--desktop desktop-only">
          <?php echo render($content['group_ting_object_right_column']['group_ting_object_right_c']['ting_series']); ?>
        </div>

        <?php if ($also_available): ?>
          <div class="material__also_available material__buttons--desktop">
            <span class="material__also_available_label"><?php print t('Also available as'); ?>: </span>
            <?php echo render($also_available); ?>
          </div>
        <?php endif; ?>
      </div>

      <div class="material__series mobile-only">
        <?php echo render($content['group_ting_object_right_column']['group_ting_object_right_c']['ting_series']); ?>
      </div>

      <?php if (!empty($content['group_ting_object_right_column']['group_material_details'])) : ?>
        <div class="detail">
          <div class="material__details js-collaps">
            <?php echo render($content['group_ting_object_right_column']['group_material_details']); ?>
          </div>
        </div>
      <?php endif; ?>

      <?php // Render abstract if not already rendered above ?>
      <?php if (!empty($content['group_ting_object_right_column']['ting_relations']['#groups']['dbcaddi:hasDescriptionFromPublisher'])) : ?>
        <div class="detail">
          <div class="material__details text js-collaps">
            <div class="ting_abstract material__abstract">
              <h2>
                <?php print t('Description from DBC'); ?>
              </h2>
              <div class="ting-relations__content">
                <?php echo render($content['group_ting_object_right_column']['group_ting_object_right_c']['ting_abstract']); ?>
              </div>
            </div>
          </div>
        </div>
      <?php endif; ?>

      <?php if (!empty($content['group_ting_object_right_column']['group_on_this_site'])) : ?>
        <div class="detail">
          <div class="material__details js-collaps">
            <?php echo render($content['group_ting_object_right_column']['group_on_this_site']); ?>
          </div>
        </div>
      <?php endif; ?>

      <?php if (!empty($content['group_ting_object_right_column']['ting_relations']['#groups']['dbcaddi:hasReview'])) : ?>
        <div class="detail">
          <div class="material__details text js-collaps">
            <?php echo render($content['group_ting_object_right_column']['ting_relations']['#groups']['dbcaddi:hasReview']); ?>
          </div>
        </div>
      <?php endif; ?>

    </div>
  </div>
<?php endif; ?>
