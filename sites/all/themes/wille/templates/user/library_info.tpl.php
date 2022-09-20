<?php

/**
 * @file
 * Template for user quota info.
 */
?>
<h2 class="user-quota-title"><?php print('Status'); ?></h2>
<div class="user-quota-info">
  <div class="user-quota-info__section">
    <div class="user-quota-info__section-inner">
      <p><?php print t('You have loaned'); ?><p>
      <ul>
        <li class="loans-left">
          <div class="loans-left__amount" style="font-size: 2.2rem">
            <?php print $ebook_loans; ?>
            <span style="font-size: 45%; display: block"><?php print t('out of @max_loans', ['@max_loans' => $max_ebook_loans]); ?></span>
          </div>
          <div class="loans-left__type">
            <?php print t('E-books'); ?>
          </div>
        </li>
        <li class="loans-left">
          <div class="loans-left__amount" style="font-size: 2.2rem">
            <?php print $audiobook_loans; ?>
            <span style="font-size: 45%; display: block"><?php print t('out of @max_loans', ['@max_loans' => $max_audiobook_loans]); ?></span>
          </div>
          <div class="loans-left__type">
            <?php print t('Audiobooks'); ?>
          </div>
        </li>
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
