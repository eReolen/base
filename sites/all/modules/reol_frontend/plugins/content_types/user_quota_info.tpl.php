<?php

/**
 * @file
 * Template for user quota info.
 *
 * @todo library-info is a legacy class.
 */
?>
<div class="library-info user-quota-info">
  <h2 class="pane-title"><?php echo t('Restrictions'); ?></h2>
<ul>
<li><?php echo $max_ebook_loans_text; ?></li>
<li><?php echo $max_audiobook_loans_text; ?></li>
<li><?php echo $max_reservations_text; ?></li>
<li><?php echo $extra_info_text; ?></li>
</ul>
<div>&nbsp;</div>
</div>
