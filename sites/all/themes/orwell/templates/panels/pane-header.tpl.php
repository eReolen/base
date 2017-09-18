<?php

/**
 * @file
 * Theme implementation to display the header block on a Drupal page.
 *
 * Additional items can be added via theme_preprocess_pane_header(). See
 * template_preprocess_pane_header() for examples.
 */
 ?>
 <div class="branding">
   <?php if (!empty($logo)): ?>
     <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo" class="branding__logo">
       <img src="sites/all/themes/orwell/svg/eReolen_Logo.svg" alt="<?php print t('Home'); ?>" />
     </a>
   <?php endif; ?>
 </div>
