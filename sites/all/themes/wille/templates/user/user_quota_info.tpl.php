<?php
/**
 * @file
 * Template for user quota info.
 */

?>
<div class="user-quota-info">
  <div class="user-quota-info__section">
    <div class="user-quota-info__section-inner">
      <p><?php print t('Loans you got left:'); ?><p>
      <ul>
        <li><?php print $max_ebook_loans; ?> <?php print t('E-books'); ?></li>
        <li><?php print $max_audiobook_loans; ?> <?php print t('Audiobooks'); ?></li>
      </ul>
    </div>
  </div>
  <div class="user-quota-info__section">
    <div class="user-quota-info__section-inner">
      <p><?php print t('If you have no loans left, you can loan these:'); ?><p>
      <?php print t('<a href="@url">See exempt loans</a>', array('@url' => $extra_link)); ?>
    </div>
  </div>
</div>
