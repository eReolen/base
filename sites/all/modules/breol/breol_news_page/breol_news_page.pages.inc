<?php

/**
 * @file
 * Page callbacks for fancy box.
 */

/**
 * News page callback.
 */
function breol_news_page_news_page() {
  $items = 30;
  $news_query = new EntityFieldQuery();
  $news_query
    ->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'breol_news')
    ->propertyCondition('status', 1)
    ->propertyOrderBy('changed', 'DESC')
    ->pager($items, 1);
  $news_res = $news_query->execute();

  if ($news_res['node']) {
    $nodes = node_load_multiple(array_keys($news_res['node']));
    $build = node_view_multiple($nodes, 'teaser');
  }

  $image_file = '';
  if ($fid = variable_get('breol_news_page_image', NULL)) {
    $image_file = file_load($fid);
  }

  return array(
    '#theme' => 'breol_news_page',
    '#content' => $build,
    '#image_file' => $image_file,
    '#pager' => array(
      '#theme' => 'pager',
      '#element' => 1,
    ),
  );
}
