<?php

  /**
   * @file
   * Template to render objects from the Ting database.
   *
   * Available variables:
   * - $object: The TingClientObject instance we're rendering.
   * - $content: Render array of content.
   */

  // Move the groups to where the template (./ting_object.tpl.php) expects them.
  $content['group_ting_object_left_column'] = $content['group_ting_left_col_search'];
  unset($content['group_ting_left_col_search']);

  $content['group_ting_object_right_column'] = $content['group_ting_right_col_search'];
  unset($content['group_ting_right_col_search']);
?>

<?php
  // Replace abstract with description from publisher if available.
  if (!empty($content['group_ting_object_right_column']['group_info']['ting_relations']['#groups']['dbcaddi:hasDescriptionFromPublisher'])){
    $content['group_ting_object_right_column']['group_info']['ting_abstract'] = $content['group_ting_object_right_column']['group_info']['ting_relations']['#groups']['dbcaddi:hasDescriptionFromPublisher'];
    // Wrap the description to make it look like the abstract.
    $content['group_ting_object_right_column']['group_info']['ting_abstract']['#prefix'] = '<div class="material__abstract field-name-ting-abstract">';
    $content['group_ting_object_right_column']['group_info']['ting_abstract']['#suffix'] = '</div>';
    unset($content['group_ting_object_right_column']['group_info']['ting_relations']['#groups']['dbcaddi:hasDescriptionFromPublisher']);
  }
?>
<?php require __DIR__.'/ting_object.tpl.php'; ?>
