<?php
/**
 * @file panels-pane.tpl.php
 * Main panel pane template
 *
 * Variables available:
 * - $pane->type: the content type inside this pane
 * - $pane->subtype: The subtype, if applicable. If a view it will be the
 *   view name; if a node it will be the nid, etc.
 * - $title: The title of the content
 * - $content: The actual content
 * - $links: Any links associated with the content
 * - $more: An optional 'more' link (destination only)
 * - $admin_links: Administrative links associated with the content
 * - $feeds: Any feed icons or associated with the content
 * - $display: The complete panels display object containing all kinds of
 *   data including the contexts and all of the other panes being displayed.
 */
?>
<div class="<?php print $classes; ?>" <?php print $id; ?> <?php print $attributes; ?>>

  <div class="user-banner">
    <div class="user-banner__content">
      <?php print $welcome_text_part_1; ?><span>,<br/></span>
      <?php print $welcome_text_part_2; ?>
    </div>
    <div class="user-banner__logout">
      <a href="/user/logout" class="__link"><?php print(t('Logout')); ?></a>
    </div>
    <div class="user-banner__bg"></div>
    <div class="user-banner__overlay"></div>
  </div>

  <div class="organic-element organic-element--user">
    <?php print $organic_svg ?>
  </div>
  <div class="pane-content user-main-content">
    <?php print render($content); ?>
  </div>
</div>
