<?php
/**
 * @file
 * Template to render objects from the Ting database.
 *
 * Available variables:
 * - $object: The TingClientObject instance we're rendering.
 * - $content: Render array of content.
 */
 // dpm($content);
 /*//<?php print render($content); ?>*/
?>
<?php if ($bundle == 'ting_collection') : ?>
  <div class="content-wrapper content-wrapper--material">
    <?php print render($content); ?>
  </div>
<?php else : ?>
  <div class="content-wrapper content-wrapper--material">
    <div class="material material--full<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
      <div class="material__cover">
        <?php echo render($content['group_ting_object_left_column']['ting_cover']); ?>
      </div>
      <div class="material__content">
        <div class="material__rating">
          <?php echo render($content['group_ting_object_right_column']['ding_entity_rating_action']); ?>
          <?php echo render($content['group_ting_object_right_column']['ding_entity_rating_result']); ?>
        </div>
        <div class="material__title">
          <?php echo render($content['group_ting_object_right_column']['ting_title']); ?>
        </div>
        <div class="material__author">
          <?php echo render($content['group_ting_object_right_column']['ting_author']); ?>
        </div>
        <div class="material__abstract text desktop-only">
          <?php echo render($content['group_ting_object_right_column']['ting_abstract']); ?>
        </div>
        <div class="material__subjects text">
          <?php echo render($content['group_ting_object_right_column']['ting_subjects']); ?>
        </div>
        <div class="material__series material__series--desktop desktop-only">
          <?php echo render($content['group_ting_object_right_column']['ting_series']); ?>
        </div>
        <div class="material__buttons material__buttons--desktop mobile-only">
          <?php echo render($content['group_ting_object_right_column']['ding_entity_buttons']); ?>
        </div>
      </div>
      <div class="material__series mobile-only">
        <?php echo render($content['group_ting_object_right_column']['ting_series']); ?>
      </div>
      <div class="material__buttons desktop-only">
        <?php echo render($content['group_ting_object_right_column']['ding_entity_buttons']); ?>
      </div>
      <div class="detail mobile-only">
        <div class="material__abstract text">
          <?php echo render($content['group_ting_object_right_column']['ting_abstract']); ?>
        </div>
      </div>
      <?php if (!empty($content['group_material_details'])) : ?>
        <div class="detail">
          <div class="material__details js-collaps">
            <?php echo render($content['group_material_details']); ?>
          </div>
        </div>
      <?php endif; ?>
      <?php if (!empty($content['ting_relations']['#groups']['dbcaddi:hasDescriptionFromPublisher'])) : ?>
        <div class="detail">
          <div class="material__details text js-collaps">
            <?php echo render($content['ting_relations']['#groups']['dbcaddi:hasDescriptionFromPublisher']); ?>
          </div>
        </div>
      <?php endif; ?>
      <?php if (!empty($content['group_on_this_site'])) : ?>
        <div class="detail">
          <div class="material__details js-collaps">
            <?php echo render($content['group_on_this_site']); ?>
          </div>
        </div>
      <?php endif; ?>
      <?php if (!empty($content['ting_relations']['#groups']['dbcaddi:hasReview'])) : ?>
        <div class="detail">
          <div class="material__details text js-collaps">
            <?php echo render($content['ting_relations']['#groups']['dbcaddi:hasReview']); ?>
          </div>
        </div>
      <?php endif; ?>
    </div>
  </div>
<?php endif; ?>
