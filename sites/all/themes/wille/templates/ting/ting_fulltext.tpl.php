<?php

/**
 * @file
 * Rendering of fulltext.
 */
?>
<div class="ting-fulltext-wrapper">
  <div class="ting-fulltext-inner-wrapper">
    <?php if (isset($variables['element']['#fields']['title'])) : ?>
      <h3 class="page-title"> <?php print $variables['element']['#fields']['title']; ?></h3>
    <?php endif; ?>

    <?php if (isset($variables['element']['#fields']['section'])) :?>
      <?php for ($i = 0; $i < $variables['element']['#fields']['section_count']; $i++) : ?>
        <section class="description<?php if ($variables['element']['#fields']['section_count'] == $i + 1) { print ' last'; } ?>">
          <?php $section = $variables['element']['#fields']['section'][$i]; ?>
          <?php if (isset($section['title'])) : ?>
            <h4 class="title"><?php print $section['title']; ?></h4>
          <?php endif; ?>
          <?php if (isset($section['para'])) : ?>
            <?php foreach ($section['para'] as $para) : ?>
              <p class="paragraph"><?php print $para; ?></p>
            <?php endforeach; ?>
          <?php endif; ?>
        </section>
      <?php endfor; ?>
    <?php endif; ?>
</div>
</div>
