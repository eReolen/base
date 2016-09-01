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
      <p><?php print t('Loans you got left:'); ?><p>
      <ul>
        <li class="loans-left">
          <div class="loans-left__amount">
            <?php print $max_ebook_loans; ?>
          </div>
          <div class="loans-left__type">
            <?php print t('E-books'); ?>
          </div>
        </li>
        <li class="loans-left">
          <div class="loans-left__amount">
            <?php print $max_audiobook_loans; ?>
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
