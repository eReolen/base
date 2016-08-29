<?php

/**
 * Render relation groups bare.
 */
?>
<?php foreach ($groups as $ns => $relations): ?>
  <?php print render($relations); ?>
<?php endforeach; ?>
