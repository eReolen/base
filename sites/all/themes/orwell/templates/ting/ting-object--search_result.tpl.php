<?php

/**
 * @file
 * Template to render objects in search results.
 */

// Move the groups to where the template expects them.
$content['group_ting_object_teaser_left'] = $content['group_ting_left_col_search'];
unset($content['group_ting_left_col_search']);

$content['group_ting_object_teaser_right'] = $content['group_ting_right_col_search'];
unset($content['group_ting_right_col_search']);

// Simply include the right template.
require 'ting-object--teaser.tpl.php';
