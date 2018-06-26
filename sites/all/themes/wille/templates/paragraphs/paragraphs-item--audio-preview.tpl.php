<?php

/**
 * @file
 * Render a audio preview paragraph.
 *
 * @see sites/all/themes/orwell/templates/paragraphs/paragraphs-item--audio-preview.tpl.php
 */
?>
<div class="audio-preview <?php print $classes; ?>"<?php print $attributes; ?>>
  <?php print render($cover); ?>
  <div class="audio-preview__details">
    <div class="audio-preview__meta">
      <div class="audio-preview__title"><div><?php print t('Audio preview') ?>: <?php print $title; ?></div></div>
      <div class="audio-preview__author"><?php print $author; ?></div>
    </div>
    <div class="audio-preview__player" data-isbn="<?php print $isbn; ?>">
      <span class="audio-preview__time">
        <span class="audio-preview__played">00.00</span> / <span class="audio-preview__duration">00.00</span>
      </span>
      <button class="audio-preview__button">play</button>
      <div class="audio-preview__progress"><div class="audio-preview__progress__complete"></div></div>
    </div>
  </div>
</div>
