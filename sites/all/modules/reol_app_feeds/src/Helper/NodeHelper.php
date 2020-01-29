<?php

namespace Drupal\reol_app_feeds\Helper;

use EntityFieldQuery;

/**
 * Node helper.
 */
class NodeHelper {
  const ENTITY_TYPE_NODE = 'node';
  const ENTITY_TYPE_PARAGRAPH = 'paragraphs_item';

  /**
   * Get value of a field.
   *
   * If the requested field does not exist, NULL will be returned.
   *
   * Note: This function is very similar to what the `entity_metadata_wrapper`
   * provides, but this function handles non-existing fields gracefully.
   *
   * @param object $entity
   *   The entity (a node or a \ParagraphsItemEntity).
   * @param string $field_name
   *   The field names.
   * @param string|null $sub_field_name
   *   The optional sub-field names.
   * @param bool $multiple
   *   If set, multiple field values will be returned as an array. Otherwise,
   *   only the first value will be returned.
   *
   * @return array|mixed|null
   *   The field value.
   */
  public function getFieldValue($entity, $field_name, $sub_field_name = NULL, $multiple = FALSE) {
    if (!isset($entity->{$field_name}[LANGUAGE_NONE])) {
      return NULL;
    }

    $values = $entity->{$field_name}[LANGUAGE_NONE];

    if (NULL !== $sub_field_name) {
      $values = array_column($values, $sub_field_name);
    }

    return $multiple ? $values : reset($values);
  }

  /**
   * Get text value of a field.
   *
   * @param object $entity
   *   The entity.
   * @param string $field_name
   *   The field names.
   * @param string|null $sub_field_name
   *   The optional sub-field names.
   * @param bool $multiple
   *   If set, multiple field values will be returned as an array. Otherwise,
   *   only the first value will be returned.
   *
   * @return array|mixed|null
   *   The text field value.
   */
  public function getTextFieldValue($entity, $field_name, $sub_field_name = NULL, $multiple = FALSE) {
    $values = $this->getFieldValue($entity, $field_name, $sub_field_name, TRUE);
    $values = array_map([$this, 'getTextValue'], $values);

    return $multiple ? $values : reset($values);
  }

  /**
   * Get list of paragraphs on a node.
   *
   * @param object $entity
   *   The entity.
   *
   * @return array|\ParagraphsItemEntity[]
   *   The paragraphs.
   */
  public function getParagraphs($entity) {
    $paragraphs = [];

    $helper = new ParagraphHelper();

    $fields = $helper->getParagraphFields($entity);
    foreach ($fields as $field_name => $field) {
      $paragraphs += $helper->loadParagraphs($entity, $field_name);
    }

    return $paragraphs;
  }

  /**
   * Get text value.
   *
   * @param mixed $value
   *   The value.
   *
   * @return string|null
   *   The text value if any.
   */
  private function getTextValue($value) {
    return isset($value['safe_value']) ? $value['safe_value'] : NULL;
  }

  /**
   * Get body text value from a node.
   *
   * @param object $node
   *   The node.
   *
   * @return string|null
   *   The body text value if any.
   */
  public function getBody($node) {
    return $this->getTextFieldValue($node, 'body', NULL, FALSE);
  }

  /**
   * Get image url.
   *
   * @param array|null $value
   *   The value.
   * @param string|null $image_style_name
   *   An optional image style to apply if it exists.
   *
   * @return string[]|string|null
   *   The image url(s).
   */
  public function getImage(array $value = null, $image_style_name = NULL) {
    if (NULL === $value) {
      return NULL;
    }
    if (isset($value[LANGUAGE_NONE])) {
      $value = $value[LANGUAGE_NONE];
    }
    if (!isset($value['uri'])) {
      return NULL;
    }
    $uri = $value['uri'];

    return (NULL !== $image_style_name && !empty(image_style_load($image_style_name)))
      ? image_style_url($image_style_name, $uri)
      : $this->getFileUrl($uri);
  }

  /**
   * Get an absolute url from a "public:/" url.
   *
   * @param string $url
   *   The file url.
   *
   * @return bool|string
   *   The absolute url if any.
   */
  public function getFileUrl($url) {
    return file_create_url($url);
  }

  /**
   * Get ting identifiers.
   *
   * @param object $entity
   *   The entity.
   * @param string $field_name
   *   The field name.
   *
   * @return string[]
   *   A list of identifiers.
   */
  public function getTingIdentifiers($entity, $field_name) {
    if (!isset($entity->{$field_name}[LANGUAGE_NONE])) {
      return [];
    }

    $relations = $this->getFieldValue($entity, $field_name, 'value', TRUE);

    $ids = array_map(function ($relation) {
      if ((isset($relation->relation_type) && 'ting_reference' === $relation->relation_type)
        && (isset($relation->endpoints[LANGUAGE_NONE][1]['entity_type']) && 'ting_object' === $relation->endpoints[LANGUAGE_NONE][1]['entity_type'])
      ) {
        return $relation->endpoints[LANGUAGE_NONE][1]['entity_id'];
      }

      return NULL;
    }, $relations);

    $result = db_query('SELECT o.ding_entity_id FROM {ting_object} o WHERE o.tid in (:ids)', [':ids' => $ids]);
    $identifiers = $result->fetchCol();

    return array_values($identifiers);
  }

  /**
   * Get a ting identifier from a url.
   *
   * @param string $url
   *   The url.
   *
   * @return string|null
   *   The identifier if any.
   */
  public function getTingIdentifierFromUrl($url) {
    return preg_match('@/object/(?P<identifier>.+)$@', $url, $matches) ? urldecode($matches['identifier']) : NULL;
  }

  /**
   * Load nodes from references.
   *
   * @param object|\ParagraphsItemEntity $entity
   *   The entity.
   * @param string $field_name
   *   The field name.
   * @param bool $multiple
   *   It set, load multiple references. Otherwise, load just one.
   *
   * @return mixed
   *   A single node or a list of nodes if any.
   */
  public function loadReferences($entity, $field_name, $multiple = TRUE) {
    if (!isset($entity->{$field_name}[LANGUAGE_NONE])) {
      return NULL;
    }
    $values = $entity->{$field_name}[LANGUAGE_NONE];
    $nids = array_column($values, 'target_id');
    $nodes = node_load_multiple($nids);

    return $multiple ? $nodes : reset($nodes);
  }

  /**
   * Load nodes ordered by specified order of node ids.
   *
   * @param array $nids
   *   The node ids.
   * @param int $status
   *   The optional node status.
   *
   * @return array
   *   An array of node objects indexed by nid.
   */
  public function loadNodes(array $nids, $status = NODE_PUBLISHED) {
    $entity_type = self::ENTITY_TYPE_NODE;
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', $entity_type)
      ->propertyCondition('status', $status)
      ->entityCondition('entity_id', $nids + [0]);
    $result = $query->execute();

    $nodes = isset($result[$entity_type]) ? node_load_multiple(array_keys($result[$entity_type])) : [];

    self::sortByIds($nodes, $nids);

    return $nodes;
  }

  /**
   * Sort a list of items (typically a list of nodes) by id.
   *
   * @param objects[] $items
   *   The items.
   * @param array $ids
   *   The ids to sort by.
   * @param string $id_key
   *   The optional id key in the items.
   */
  public static function sortByIds(array &$items, array $ids, $id_key = 'nid') {
    // Order by index in $nids.
    uasort($items, function ($a, $b) use ($ids, $id_key) {
      $a = array_search($a->{$id_key}, $ids);
      $b = array_search($b->{$id_key}, $ids);

      return $a - $b;
    });
  }

  /**
   * Map from article content type to theme type.
   *
   * @var array
   */
  private static $themeTypes = [
    'article' => 'theme',
    'author_portrait' => 'author_theme',
    'news' => 'theme',
  ];

  /**
   * Get theme type.
   *
   * @param string $contentType
   *   The content type.
   *
   * @see https://docs.google.com/document/d/1lJ3VPAJf7DAbBWAQclRHfcltzZefUG3iGCec-z97KlA/edit?ts=5c4ef9d5#heading=h.u2ztxyfu4egy
   *
   * @return string
   *   The theme type.
   */
  public function getThemeType($contentType) {
    return self::$themeTypes[$contentType] ?? 'theme';
  }

}
