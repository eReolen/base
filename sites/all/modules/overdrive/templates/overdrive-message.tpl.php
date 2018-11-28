<?php
/**
 * @file
 * Default template for overdrive information message.
 */
?>
<div class="overdrive-message">
  <?php echo $message; ?>
  <div class="actions">
    <a class="action-button" data-modal-name="<?php echo $modal_id; ?>" target="_blank" href="<?php echo $uri; ?>">
      <?php echo t('Borrow it at eReolen Global', array(), array('context' => 'overdrive')) ?>
    </a>
    <a class="action-button modal-close" data-modal-name="<?php echo $modal_id; ?>" href="#">
      <?php echo t('Cancel', array(), array('context' => 'overdrive')); ?>
    </a>
  </div>
</div>

