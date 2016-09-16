<?php

/**
 * @file
 * Page callbacks for fancy box.
 */

/**
 * News page callback.
 */
function breol_news_page_news_page() {
  $items = 5;
  $news_query = new EntityFieldQuery();
  $news_query
    ->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'breol_news')
    ->propertyCondition('status', 1)
    ->propertyOrderBy('changed', 'DESC')
    ->pager($items, 1);

  $other_query = new EntityFieldQuery();
  $other_query
    ->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', array('link', 'breol_video'))
    ->propertyCondition('status', 1)
    ->propertyOrderBy('changed', 'DESC')
    ->pager($items, 1);

  $news_res = $news_query->execute();
  $other_res = $other_query->execute();

  // Zip the results together into one alternating array.
  $res = array();
  while (!empty($news_res['node']) || !empty($other_res['node'])) {
    if (!empty($news_res['node'])) {
      $res[] = array_shift($news_res['node']);
    }
    if (!empty($other_res['node'])) {
      $res[] = array_shift($other_res['node']);
    }
  }

  $index = 0;
  $nodes = array();
  $layouts = array();
  while (isset($res[$index])) {
    list($first, $second) = array_slice($res, $index, 2);
    $index += 2;

    $layouts += _breol_news_page_row_layout($first, $second);
    $nodes[] = $first->nid;
    if (isset($second)) {
      $nodes[] = $second->nid;
    }
  }
  $nodes = node_load_multiple($nodes);

  $vars = array(
    'fancy_box' => theme(
      'breol_fancy_box',
      array(
        'nodes' => $nodes,
        'layout' => $layouts,
      )
    ),
    'pager' => theme('pager', array('element' => 1)),
    'image_file' => '',
  );

  if ($fid = variable_get('breol_news_page_image', NULL)) {
    $vars['image_file'] = file_load($fid);
  }

  return theme('breol_news_page', $vars);
}

/**
 * Figure out the layout of a row.
 */
function _breol_news_page_row_layout($first, $second = null) {
  $layouts = array();
  $items = array($first, $second);
  $size_map = array(
    'breol_news' => 'a',
    'breol_video' => 'm',
    'link' => 's',
  );
  if ($second) {
    $sizes = $size_map[$first->type] . $size_map[$second->type];
    // Default spacing pushes to insert.
    $push_count = 1;
    switch ($sizes) {
      case 'mm':
        // Two large, no room for pushes.
        $push_count = 0;
        break;

      case 'ss':
        // Two small, push twice.
        $push_count = 2;
        break;

      case 'aa':
        // Pick a random medium/small combination.
        $sizes = array_rand(array('sm', 'ms'));
        break;

      default:
        if (strpos($sizes, 'a') !== FALSE) {
          // We have one any size, make it the opposite of the other.
          $sizes = strtr($sizes, 'a', strpos($sizes, 's') === FALSE ? 's' : 'm');

        }
    }

    foreach (str_split($sizes) as $index => $size) {
      $layouts[$items[$index]->nid] = array(
        'type' => $size == 's' ? 'small' : 'medium',
        'attributes' => array(
          'class' => array(
            'fancy-box-item',
          ),
        ),
      );
    }

    for ($i = 0; $i < $push_count; $i++) {
      switch (_breol_news_page_pingpong()) {
        case -1:
          $layouts[$first->nid]['attributes']['class'][] = 'fancy-box__push-left';
          break;

        case 0:
          $layouts[$first->nid]['attributes']['class'][] = 'fancy-box__push-right';
          break;

        case 1:
          $layouts[$second->nid]['attributes']['class'][] = 'fancy-box__push-right';
          break;
      }
    }

  }
  else {
    // Only one item, we're at the end, so just add it.
    $layouts[$first->nid] = array(
      'type' => $first->type == 'link' ? 'small' : 'medium',
      'attributes' => array(
        'class' => array(
          'fancy-box-item',
        ),
      ),
    );
  }
  return $layouts;
}

/**
 * Return ping pong value.
 *
 * Like this: -1 -> 0 -> 1 -> 0 -> -1
 */
function _breol_news_page_pingpong() {
  static $direction = 1;
  static $current = 1;

  if ($current == 1 || $current == -1) {
    $direction *= -1;
  }

  return $current += $direction;
}
