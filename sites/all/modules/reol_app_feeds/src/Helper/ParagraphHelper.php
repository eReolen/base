<?php

namespace Drupal\reol_app_feeds\Helper;

use EntityFieldQuery;
use GuzzleHttp\Client;

/**
 * Paragraphs helper.
 */
class ParagraphHelper {
  // Nyeste nyheds karrusel.
  const PARAGRAPH_ARTICLE_CAROUSEL = 'article_carousel';
  // Lydprøve.
  const PARAGRAPH_AUDIO_PREVIEW = 'audio_preview';
  // Forfatterportræt.
  const PARAGRAPH_AUTHOR_PORTRAIT = 'author_portrait';
  // Forfattercitat.
  const PARAGRAPH_AUTHOR_QUOTE = 'author_quote';
  // Linkbox.
  const PARAGRAPH_LINKBOX = 'linkbox';
  // Materiale karrusel.
  const PARAGRAPH_MATERIAL_CAROUSEL = 'material_carousel';
  // Nyhedsbrevstilmelding.
  const PARAGRAPH_NEWSLETTER_SIGNUP = 'newsletter_signup';
  // Nyheds karrusel.
  const PARAGRAPH_PICKED_ARTICLE_CAROUSEL = 'picked_article_carousel';
  // Redaktøren anbefaler.
  const PARAGRAPH_RECOMMENDED_MATERIAL = 'recommended_material';
  // Litteratursiden anmeldelse.
  const PARAGRAPH_REVIEW = 'review';
  // Formidlingsboks.
  const PARAGRAPH_SPOTLIGHT_BOX = 'spotlight_box';
  // Video.
  const PARAGRAPH_VIDEO = 'video';
  // To elementer.
  const PARAGRAPH_TWO_ELEMENTS = 'two_elements';

  // Paragraph aliases.
  const PARAGRAPH_ALIAS_AUDIO = self::PARAGRAPH_AUDIO_PREVIEW;
  const PARAGRAPH_ALIAS_CAROUSEL = self::PARAGRAPH_MATERIAL_CAROUSEL;
  const PARAGRAPH_ALIAS_EDITOR = self::PARAGRAPH_RECOMMENDED_MATERIAL;
  const PARAGRAPH_ALIAS_LINK = self::PARAGRAPH_LINKBOX;
  const PARAGRAPH_ALIAS_THEME_LIST = self::PARAGRAPH_PICKED_ARTICLE_CAROUSEL;

  // @see https://docs.google.com/document/d/1lJ3VPAJf7DAbBWAQclRHfcltzZefUG3iGCec-z97KlA/edit?ts=5c4ef9d5#heading=h.u2ztxyfu4egy
  const VIEW_DOTTED = 'dotted';
  const VIEW_SCROLL = 'scroll';

  const VALUE_NONE = '';

  /**
   * The node helper.
   *
   * @var \Drupal\reol_app_feeds\Helper\NodeHelper
   */
  protected $nodeHelper;

  /**
   * Constructor.
   */
  public function __construct() {
    $this->nodeHelper = new NodeHelper();
  }

  /**
   * Get a list of paragraph ids on a list of nodes.
   *
   * @param array $nids
   *   The node ids.
   * @param string|null $node_type
   *   The optional node type.
   *
   * @return array
   *   The list of paragraphs.
   */
  public function getParagraphIds(array $nids, $node_type = NULL) {
    $paragraphIds = [];
    $accumulator = function (\ParagraphsItemEntity $paragraph) use (&$paragraphIds) {
      $paragraphIds[] = $paragraph->item_id;
    };

    $entity_type = NodeHelper::ENTITY_TYPE_NODE;
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', $entity_type)
      ->propertyCondition('status', NODE_PUBLISHED)
      ->propertyCondition('nid', $nids ?: [0], 'IN');
    if (NULL !== $node_type) {
      $query->entityCondition('bundle', $node_type);
    }
    $result = $query->execute();

    if (isset($result[$entity_type])) {
      $nodes = node_load_multiple(array_keys($result[$entity_type]));
      foreach ($nodes as $node) {
        $paragraph_fields = $this->getParagraphFields($node);
        foreach ($paragraph_fields as $field_name => $field) {
          $paragraphs = $this->loadParagraphs($node, $field_name);
          $this->processParagraphs($paragraphs, TRUE, $accumulator);
        }
      }
    }

    return $paragraphIds;
  }

  /**
   * Process paragraphs, optionally recursively and depth first.
   *
   * @param \ParagraphsItemEntity[] $paragraphs
   *   The paragraphs.
   * @param bool $recurse
   *   Whether to recursively process paragraphs.
   * @param callable $accumulator
   *   Accumulator to accumulate results.
   */
  private function processParagraphs(array $paragraphs, $recurse, callable $accumulator) {
    foreach ($paragraphs as $paragraph) {
      $accumulator($paragraph);
      if ($recurse) {
        $paragraphFields = $this->getParagraphFields($paragraph);
        foreach ($paragraphFields as $field_name => $field) {
          $paragraphs = $this->loadParagraphs($paragraph, $field_name);
          $this->processParagraphs($paragraphs, $recurse, $accumulator);
        }
      }
    }
  }

  /**
   * Get paragraphs fields on an entity (node or paragraph).
   *
   * @param object|\ParagraphsItemEntity $entity
   *   The entity.
   *
   * @return array
   *   The paragraph fields.
   */
  public function getParagraphFields($entity) {
    if ($entity instanceof \ParagraphsItemEntity) {
      $entity_type = NodeHelper::ENTITY_TYPE_PARAGRAPH;
      $bundle_name = $entity->bundle();
    }
    else {
      $entity_type = NodeHelper::ENTITY_TYPE_NODE;
      $bundle_name = $entity->type;
    }

    $paragraphFields = [];
    $fields = field_info_instances($entity_type, $bundle_name);
    foreach ($fields as $field_name => $info) {
      $field = field_info_field($field_name);
      if ($this->isParagraphsField($field)) {
        $paragraphFields[$field['field_name']] = $field;
      }
    }

    return $paragraphFields;
  }

  /**
   * Decide if a field is a paragraphs field.
   *
   * @param array|string $field
   *   The field.
   *
   * @return bool
   *   True iff the field is a paragraphs field.
   */
  private function isParagraphsField($field) {
    if (is_string($field)) {
      $field = field_info_field($field);
    }

    return 'paragraphs' === $field['type'];
  }

  /**
   * Load paragraphs from a paragraphs field on an entity (node or paragraph).
   *
   * @param object $entity
   *   The entity (a node or a paragraph).
   * @param string $field_name
   *   The field name.
   *
   * @return \ParagraphsItemEntity[]
   *   The paragraphs.
   */
  public function loadParagraphs($entity, $field_name) {
    $paragraphs = [];

    if ($this->isParagraphsField($field_name) && isset($entity->{$field_name}[LANGUAGE_NONE])) {
      $values = $entity->{$field_name}[LANGUAGE_NONE];
      $ids = array_column($values, 'value');

      $paragraphs = paragraphs_item_load_multiple($ids);

      // Sort the paragraphs in the same order as on the pages.
      NodeHelper::sortByIds($paragraphs, $ids, 'item_id');
    }

    return $paragraphs;
  }

  /**
   * Get data for a list of paragraphs.
   *
   * @param string|string[] $types
   *   The paragraphs bundle types.
   * @param array|null $paragraphIds
   *   The paragraph ids.
   * @param callable|null $filter
   *   The optional filter to apply to the list.
   *
   * @return array|\ParagraphsItemEntity[]
   *   The list of paragraphs.
   */
  public function getParagraphs($types, array $paragraphIds = NULL, callable $filter = NULL) {
    $types = [$types];
    $paragraphs = [];

    $entity_type = NodeHelper::ENTITY_TYPE_PARAGRAPH;
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', $entity_type)
      ->entityCondition('bundle', $types, 'IN')
      ->entityCondition('entity_id', $paragraphIds ?: [0], 'IN');
    $result = $query->execute();

    if (isset($result[$entity_type])) {
      $paragraphs = paragraphs_item_load_multiple(array_keys($result[$entity_type]));
      if (NULL !== $filter) {
        $paragraphs = array_filter($paragraphs, $filter);
      }
    }

    return $paragraphs;
  }

  /**
   * Get data for a list of paragraphs.
   *
   * @param string $type
   *   The paragraphs bundle type.
   * @param array $paragraphIds
   *   The paragraph ids.
   *
   * @return array
   *   The paragraphs data.
   */
  public function getParagraphsData($type, array $paragraphIds) {
    $paragraphs = $this->getParagraphs($type, $paragraphIds);
    $data = array_values(array_map([$this, 'getParagraphData'], $paragraphs));

    // Make sure that all items are numeric arrays.
    foreach ($data as &$datum) {
      if (static::isAssoc($datum)) {
        $datum = [$datum];
      }
    }

    // Flatten the data.
    return empty($data) ? [] : array_merge(...$data);
  }

  /**
   * Get data for a single paragraph.
   *
   * @param \ParagraphsItemEntity $paragraph
   *   The paragraph.
   *
   * @return array|null
   *   The paragraph data or null on unknown paragraph type.
   */
  public function getParagraphData(\ParagraphsItemEntity $paragraph) {
    $bundle = $paragraph->bundle();

    switch ($bundle) {
      case self::PARAGRAPH_ALIAS_AUDIO:
        return $this->getAudio($paragraph);

      case self::PARAGRAPH_ALIAS_CAROUSEL:
        return $this->getCarousel($paragraph);

      case self::PARAGRAPH_ALIAS_EDITOR:
        return $this->getEditor($paragraph);

      case self::PARAGRAPH_ALIAS_LINK:
        return $this->getLink($paragraph);

      case self::PARAGRAPH_REVIEW:
        return $this->getReview($paragraph);

      case self::PARAGRAPH_SPOTLIGHT_BOX:
        return $this->getSpotlightBox($paragraph);

      case self::PARAGRAPH_ARTICLE_CAROUSEL:
        return $this->getArticleCarousel($paragraph);

      case self::PARAGRAPH_ALIAS_THEME_LIST:
        return $this->getThemeList($paragraph);

      case self::PARAGRAPH_VIDEO:
        return $this->getVideo($paragraph);
    }

    return NULL;
  }

  /**
   * Get carousel data.
   *
   * @param \ParagraphsItemEntity $paragraph
   *   The paragraph.
   *
   * @see https://docs.google.com/document/d/1lJ3VPAJf7DAbBWAQclRHfcltzZefUG3iGCec-z97KlA/edit?ts=5c4ef9d5#bookmark=id.51b3v5z38ank
   *
   * @return array
   *   The carousel data.
   */
  private function getCarousel(\ParagraphsItemEntity $paragraph) {
    $data = [];

    if (isset($paragraph->field_carousel[LANGUAGE_NONE])) {
      foreach ($paragraph->field_carousel[LANGUAGE_NONE] as $index => $value) {
        $data[] = [
          'guid' => $this->getGuid($paragraph, $index),
          'type' => $this->getType($paragraph),
          'title' => $this->getTitle($value['title']),
          'view' => $this->getView($paragraph),
          'query' => $value['search'],
        ];
      }
    }

    return $data;
  }

  /**
   * Get article carousel (aka "Latest news").
   *
   * @param \ParagraphsItemEntity $paragraph
   *   The paragraph.
   *
   * @return array
   *   The article carousel data.
   */
  private function getArticleCarousel(\ParagraphsItemEntity $paragraph) {
    $list = [];
    // Cf. ereol_article_get_articles().
    $query = new EntityFieldQuery();
    $count = _reol_app_feeds_variable_get('reol_app_feeds_frontpage', 'max_news_count', 6);

    $entityType = NodeHelper::ENTITY_TYPE_NODE;
    $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'article')
      ->propertyCondition('status', NODE_PUBLISHED)
      ->propertyOrderBy('created', 'DESC')
      ->range(0, $count);
    $result = $query->execute();
    if (isset($result[$entityType])) {
      $nodes = entity_load($entityType, array_keys($result[$entityType]));
      $list = array_values(array_map([$this, 'getThemeData'], $nodes));
    }

    return [
      'guid' => $this->getGuid($paragraph),
      'type' => $this->getType($paragraph),
      'view' => $this->getView($paragraph),
      'list' => $list,
    ];
  }

  /**
   * Get list of all nodes referenced from af theme paragraph.
   *
   * @param \ParagraphsItemEntity $paragraph
   *   The paragraph.
   *
   * @see https://docs.google.com/document/d/1lJ3VPAJf7DAbBWAQclRHfcltzZefUG3iGCec-z97KlA/edit?ts=5c4ef9d5#bookmark=id.vpgrki5b8gg
   *
   * @return array
   *   The theme list data.
   */
  private function getThemeList(\ParagraphsItemEntity $paragraph) {
    // Get all items.
    //
    // Note: We may get more data than actually needed, but due to non-trivial
    // filtering on "identifiers" (see below) we have to load all items.
    //
    // @TODO: Can we improve this so we don't have to load all items and throw
    // away some of them?
    $items = $this->nodeHelper->loadReferences($paragraph, 'field_picked_articles');

    $list = array_values(array_map([$this, 'getThemeData'], $items));
    // Remove items with no identifiers.
    $list = array_values(array_filter($list, function (array $item) {
      return isset($item['identifiers']);
    }));

    // Slice the list to the maximum allowed length.
    $list = array_slice($list, 0, (int) _reol_app_feeds_variable_get('reol_app_feeds_frontpage', 'theme_list_max_length', 6));

    return [
      'guid' => $this->getGuid($paragraph),
      'type' => $this->getType($paragraph),
      'view' => $this->getView($paragraph),
      'list' => $list,
    ];
  }

  /**
   * Get theme data.
   *
   * @param object $node
   *   The node.
   *
   * @return array
   *   The theme data.
   * @throws \TingClientException
   * @see https://docs.google.com/document/d/1lJ3VPAJf7DAbBWAQclRHfcltzZefUG3iGCec-z97KlA/edit?ts=5c4ef9d5#bookmark=id.a1elwnwq3nk4
   *
   */
  public function getThemeData($node) {
    $view = $this->nodeHelper->getFieldValue($node, 'field_image_teaser', 'value') ? 'image' : 'covers';
    $contentType = $this->nodeHelper->getFieldValue($node, 'field_article_type', 'value');
    $type = $this->nodeHelper->getThemeType($contentType);

    $image = !empty($node->field_ding_news_list_image) ? $this->nodeHelper->getImage($node->field_ding_news_list_image, 'app_news_image') : static::VALUE_NONE;
    $identifiers = $this->nodeHelper->getTingIdentifiers($node, 'field_ding_news_materials');

    // Hack for eReolen Go!
    if ('breol_news' === $node->type) {
      $view = 'image';
      $image = !empty($node->field_breol_cover_image) ? $this->nodeHelper->getImage($node->field_breol_cover_image) : static::VALUE_NONE;

      // Get identifiers from carousel queries.
      $carousels = $this->nodeHelper->getFieldValue($node, 'field_carousels', NULL, TRUE);
      $identifiers = [];
      foreach ($carousels as $carousel) {
        module_load_include('inc', 'opensearch', 'opensearch.client');
        $result = opensearch_do_search($carousel['search']);
        foreach ($result->collections as $collection) {
          /** @var \TingCollection $collection */
          /** @var \TingEntity $object */
          $object = $collection->getPrimary_object();
          $identifier = $object->getId();
          if (!in_array($identifier, $identifiers)) {
            $identifiers[] = $identifier;
          }
        }
        // Only get identifiers from the first query.
        break;
      }
    }

    return [
      'guid' => $node->nid,
      'type' => $type,
      'title' => $this->getTitle($node->title),
      'view' => $view,
      'image' => $image,
      'body' => $this->nodeHelper->getBody($node),
      'identifiers' => $identifiers,
    ];
  }

  /**
   * Get link data.
   *
   * @param \ParagraphsItemEntity $paragraph
   *   The paragraph.
   *
   * @see https://docs.google.com/document/d/1lJ3VPAJf7DAbBWAQclRHfcltzZefUG3iGCec-z97KlA/edit?ts=5c4ef9d5#bookmark=id.q902hu2tcy3i
   *
   * @return array
   *   The link data.
   */
  private function getLink(\ParagraphsItemEntity $paragraph) {
    $buttonText = $this->nodeHelper->getFieldValue($paragraph, 'field_button_text', 'value');
    if (empty($buttonText)) {
      $buttonText = _reol_app_feeds_variable_get('reol_app_feeds_frontpage', 'link_button_text', self::VALUE_NONE);
    }

    return [
      'guid' => $this->getGuid($paragraph),
      'type' => $this->getType($paragraph),
      'title' => $this->getTitle($this->nodeHelper->getFieldValue($paragraph, 'field_link', 'title')),
      'url' => $this->getAbsoluteUrl($this->nodeHelper->getFieldValue($paragraph, 'field_link', 'url')),
      'color' => ltrim($this->nodeHelper->getFieldValue($paragraph, 'field_link_color', 'rgb'), '#'),
      'subtitle' => $this->nodeHelper->getFieldValue($paragraph, 'field_link_text', 'value'),
      'button_text' => $buttonText,
    ];
  }

  /**
   * Get absolute url.
   *
   * @param string $url
   *   The (relative) url.
   *
   * @return string
   *   The absolute url.
   */
  private function getAbsoluteUrl($url) {
    return url($url, ['absolute' => TRUE]);
  }

  /**
   * Get review data.
   *
   * @param \ParagraphsItemEntity $paragraph
   *   The paragraph.
   *
   * @see https://docs.google.com/document/d/1lJ3VPAJf7DAbBWAQclRHfcltzZefUG3iGCec-z97KlA/edit?ts=5c4ef9d5#bookmark=id.qh5qjlx68dde
   *
   * @return array
   *   The review data.
   */
  private function getReview(\ParagraphsItemEntity $paragraph) {
    return [
      'guid' => $this->getGuid($paragraph),
      'type' => 'review_list',
      'view' => $this->getView($paragraph),
      'list' => $this->getReviewList(),
    ];
  }

  /**
   * Get review list.
   *
   * @param int $count
   *   The number of reviews.
   *
   * @see https://docs.google.com/document/d/1lJ3VPAJf7DAbBWAQclRHfcltzZefUG3iGCec-z97KlA/edit?ts=5c4ef9d5#bookmark=id.i6m7t7hau5bo
   *
   * @return array
   *   The review list data.
   */
  public function getReviewList($count = 1) {
    $list = [];
    if ($reviews = reol_review_get_random_reviews(NULL, $count)) {
      foreach ($reviews as $review) {
        // @var \TingEntity $ting
        $ting = $review->ting_entity;
        $creator = $ting->getCreators() ? implode(', ', $ting->getCreators()) : self::VALUE_NONE;

        $source = preg_match('@//litteratursiden.dk/@', $review->link) ? 'Litteratursiden' : $review->link;
        $list[] = [
          'guid' => $review->rrid,
          'type' => 'review',
          'identifier' => $review->ding_entity_id,
          'title' => $review->title,
          'creator' => $creator,
          'description' => $review->description,
          'source' => $source,
          'url' => $review->link,
        ];
      }
    }

    return [
      [
        'guid' => self::VALUE_NONE,
        'type' => 'review_list',
        'view' => self::VIEW_DOTTED,
        'list' => $list,
      ],
    ];
  }

  /**
   * Get spotlight box.
   *
   * @param \ParagraphsItemEntity $paragraph
   *   The paragraph.
   *
   * @return array
   *   The spotlight box data.
   */
  public function getSpotlightBox(\ParagraphsItemEntity $paragraph) {
    $list = $this->getVideoList($paragraph);
    $videos = empty($list) ? [] : [
      [
        'guid' => ParagraphHelper::VALUE_NONE,
        'type' => 'video_list',
        'view' => ParagraphHelper::VIEW_DOTTED,
        'list' => $list,
      ],
    ];
    $links = array_values(array_map([$this, 'getLink'], $this->loadParagraphs($paragraph, 'field_spotlight_row_2')));

    $editor = self::VALUE_NONE;
    $item = $this->getEditor($paragraph);
    if ($item['list']) {
      $item['type'] = 'editor_recommends_list';
      $item['guid'] .= '-editor';
      $editor = $item;
    }

    return [
      'guid' => $this->getGuid($paragraph),
      'type' => $this->getType($paragraph),
      'view' => $this->getView($paragraph),
      'videos' => $videos,
      'reviews' => $this->getReviewList(),
      'links' => $links,
      'editor' => $editor,
    ];
  }

  /**
   * Get editor data.
   *
   * @param \ParagraphsItemEntity $paragraph
   *   The paragraph.
   *
   * @see https://docs.google.com/document/d/1lJ3VPAJf7DAbBWAQclRHfcltzZefUG3iGCec-z97KlA/edit?ts=5c4ef9d5#bookmark=id.isl1hf5mbnf
   *
   * @return array
   *   The editor data.
   */
  public function getEditor(\ParagraphsItemEntity $paragraph) {
    return [
      'guid' => $this->getGuid($paragraph),
      'type' => $this->getType($paragraph),
      'view' => $this->getView($paragraph),
      'list' => $this->getEditorList($paragraph),
    ];
  }

  /**
   * Get editor list data.
   *
   * @param \ParagraphsItemEntity $paragraph
   *   The paragraph id.
   *
   * @see https://docs.google.com/document/d/1lJ3VPAJf7DAbBWAQclRHfcltzZefUG3iGCec-z97KlA/edit?ts=5c4ef9d5#bookmark=id.e3uva6eizbp1
   *
   * @return array
   *   The editor list data.
   */
  private function getEditorList(\ParagraphsItemEntity $paragraph) {
    $subParagraphIds = $this->nodeHelper->getFieldValue($paragraph, 'field_spotlight_row_3', 'value', TRUE);
    $subParagraphs = $this->getParagraphs(ParagraphHelper::PARAGRAPH_RECOMMENDED_MATERIAL, $subParagraphIds);
    $list = array_values(array_map(function (\ParagraphsItemEntity $subParagraph) {
      return [
        'guid' => $this->getGuid($subParagraph),
        'type' => 'editor_recommends',
        'title' => $this->getTitle($this->nodeHelper->getTextFieldValue($subParagraph, 'field_rec_title')),
        'identifier' => $this->nodeHelper->getTingIdentifierFromUrl($this->nodeHelper->getTextFieldValue($subParagraph, 'field_rec_material')),
      ];
    }, $subParagraphs));

    return $list;
  }

  /**
   * Get video data.
   *
   * @param \ParagraphsItemEntity $paragraph
   *   The paragraph.
   *
   * @see https://docs.google.com/document/d/1lJ3VPAJf7DAbBWAQclRHfcltzZefUG3iGCec-z97KlA/edit?ts=5c4ef9d5#bookmark=id.aw3cqhhwfwa0
   *
   * @return array
   *   The video data.
   */
  protected function getVideo(\ParagraphsItemEntity $paragraph) {
    // Wrap all videos in a fake list element.
    return [
      'guid' => $this->getGuid($paragraph),
      'type' => $this->getType($paragraph),
      'view' => $this->getView($paragraph),
      'list' => $this->getVideoList($paragraph),
    ];
  }

  /**
   * Get video list data.
   *
   * @param \ParagraphsItemEntity $paragraph
   *   The paragraph.
   *
   * @see https://docs.google.com/document/d/1lJ3VPAJf7DAbBWAQclRHfcltzZefUG3iGCec-z97KlA/edit?ts=5c4ef9d5#bookmark=id.3ugapu7oybq
   *
   * @return array
   *   The view list data.
   */
  public function getVideoList(\ParagraphsItemEntity $paragraph) {
    $list = [];

    $sub_paragraphs_field_name = NULL;
    $sub_paragraphs_video_field_name = NULL;

    switch ($paragraph->bundle()) {
      case ParagraphHelper::PARAGRAPH_SPOTLIGHT_BOX:
        $sub_paragraphs_field_name = 'field_spotlight_primary';
        $sub_paragraphs_video_field_name = 'field_video';
        break;

      case ParagraphHelper::PARAGRAPH_TWO_ELEMENTS:
        $sub_paragraphs_field_name = 'field_two_elements_primary';
        $sub_paragraphs_video_field_name = 'field_breol_video';
        break;
    }

    if (isset($sub_paragraphs_field_name, $sub_paragraphs_video_field_name)) {
      $subParagraphIds = $this->nodeHelper->getFieldValue($paragraph, $sub_paragraphs_field_name, 'value', TRUE);
      $subParagraphs = $this->getParagraphs(ParagraphHelper::PARAGRAPH_VIDEO, $subParagraphIds);
      $list = array_values(array_map(function (\ParagraphsItemEntity $subParagraph) use ($sub_paragraphs_video_field_name) {
        $video = $this->nodeHelper->loadReferences($subParagraph, 'field_video_node', FALSE);
        $url = $this->nodeHelper->getFieldValue($video, $sub_paragraphs_video_field_name, 'uri');

        return [
          'guid' => $this->getGuid($subParagraph),
          'type' => $this->getType($subParagraph),
          'title' => $this->getTitle($video->title),
          'image' => self::VALUE_NONE,
          'source' => $this->getVideoSource($url),
          'url' => $this->nodeHelper->getFileUrl($url),
        ];
      }, $subParagraphs));
    }

    return $list;
  }

  /**
   * Get video source.
   *
   * @param string $url
   *   The video source url.
   *
   * @see https://docs.google.com/document/d/1lJ3VPAJf7DAbBWAQclRHfcltzZefUG3iGCec-z97KlA/edit?ts=5c4ef9d5#bookmark=id.3ugapu7oybq
   *
   * @return string
   *   The video source.
   */
  private function getVideoSource($url) {
    if (preg_match('/(?P<source>youtube)/', $url, $matches)) {
      return $matches['source'];
    }

    return self::VALUE_NONE;
  }

  /**
   * Get audio data.
   *
   * @param \ParagraphsItemEntity $paragraph
   *   The paragraph.
   *
   * @see https://docs.google.com/document/d/1lJ3VPAJf7DAbBWAQclRHfcltzZefUG3iGCec-z97KlA/edit?ts=5c4ef9d5#bookmark=id.4115gxb54gcf
   *
   * @return array|null
   *   The audio data.
   */
  private function getAudio(\ParagraphsItemEntity $paragraph) {
    $url = $this->nodeHelper->getTextFieldValue($paragraph, 'field_preview_material');
    $identifier = $this->nodeHelper->getTingIdentifierFromUrl($url);
    if (NULL !== $identifier) {
      $ting = ding_entity_load($identifier);
      if ($ting) {
        $isbn = $ting->getIsbn();
        $isbn = reset($isbn);

        $metadata = $this->getAudioMetadata($isbn);

        return [
          'guid' => $this->getGuid($paragraph),
          'type' => $this->getType($paragraph),
          'identifier' => $identifier,
          'title' => $this->getTitle($ting->getTitle()),
          'url' => isset($metadata['url']) ? $metadata['url'] : NULL,
          'metadata' => isset($metadata['metadata']) ? $metadata['metadata'] : NULL,
        ];
      }
    }

    return NULL;
  }

  /**
   * Get audio metadata.
   *
   * Note: The Publizon product client (\PublizonProductClient) does not
   * provide information on audio clip size and format so we perform a few
   * http requests to get this information.
   *
   * Warning: this performs 2 http requests!
   *
   * @param string $isbn
   *   The isbn.
   *
   * @return array|null
   *   The audio metadata if any. Keys: 'url', 'metadata'.
   */
  private function getAudioMetadata($isbn) {
    $cache_key = __METHOD__ . '-' . $isbn;

    if ($cached = cache_get($cache_key)) {
      return $cached->data;
    }

    try {
      $metadata = [];

      $metadataUrl = 'https://audio.api.streaming.pubhub.dk/v1/samples/' . $isbn;
      $audioUrl = 'https://audio.api.streaming.pubhub.dk/Sample.ashx?isbn=' . $isbn;

      $client = new Client();
      $response = $client->get($metadataUrl);
      $data = json_decode((string) $response->getBody(), TRUE);

      $metadata['length'] = $data['duration'];

      // Get size of audio sample.
      $response = $client->head($audioUrl);
      $header = $response->getHeader('content-range');
      $contentRange = reset($header);
      if (preg_match('@bytes (?P<range_start>[0-9]+)-(?P<range_end>[0-9]+)/(?P<size>[0-9]+)@',
                     $contentRange, $matches)) {
        $metadata['size'] = (int) $matches['size'];
      }

      // Get audio format.
      $header = $response->getHeader('content-type');
      $metadata['format'] = reset($header);

      $result = ['url' => $audioUrl, 'metadata' => $metadata];

      // Store result in cache.
      cache_set($cache_key, $result);

      return $result;
    }
    catch (\Exception $exception) {
      // We don't want any exceptions to break the feed.
    }

    return NULL;
  }

  /**
   * Get guid (generally unique id) for a paragraph.
   *
   * The guid is NOT guaranteed bo be globally unique.
   *
   * @param \ParagraphsItemEntity $paragraph
   *   The paragraph.
   * @param int|null $delta
   *   The delta (index).
   *
   * @return string
   *   The guid.
   */
  public function getGuid(\ParagraphsItemEntity $paragraph, $delta = NULL) {
    $guid = $paragraph->identifier();
    if (NULL !== $delta) {
      $guid .= '-' . $delta;
    }

    return $guid;
  }

  /**
   * Get data type for a paragraph.
   *
   * @param \ParagraphsItemEntity $paragraph
   *   The paragraph.
   *
   * @return string|null
   *   The paragraph type.
   */
  private function getType(\ParagraphsItemEntity $paragraph) {
    $bundle = $paragraph->bundle();

    switch ($bundle) {
      case self::PARAGRAPH_ALIAS_AUDIO:
        return 'audio_sample';

      case self::PARAGRAPH_AUTHOR_PORTRAIT:
        return 'author_portrait';

      case self::PARAGRAPH_AUTHOR_QUOTE:
        return 'author_quote';

      case self::PARAGRAPH_ALIAS_CAROUSEL:
        return 'carousel';

      case self::PARAGRAPH_ALIAS_EDITOR:
        return 'editor';

      case self::PARAGRAPH_ALIAS_LINK:
        return 'link';

      case self::PARAGRAPH_REVIEW:
        return 'review';

      case self::PARAGRAPH_SPOTLIGHT_BOX:
        return 'spotlight_box';

      case self::PARAGRAPH_ARTICLE_CAROUSEL:
      case self::PARAGRAPH_ALIAS_THEME_LIST:
        return 'theme_list';

      case self::PARAGRAPH_VIDEO:
        return 'video';
    }

    return NULL;
  }

  /**
   * Get view for a paragraph.
   *
   * @param \ParagraphsItemEntity $paragraph
   *   The paragraph.
   *
   * @see https://docs.google.com/document/d/1lJ3VPAJf7DAbBWAQclRHfcltzZefUG3iGCec-z97KlA/edit?ts=5c4ef9d5#heading=h.u2ztxyfu4egy
   *
   * @return string
   *   The view.
   */
  public function getView(\ParagraphsItemEntity $paragraph) {
    $bundle = $paragraph->bundle();

    switch ($bundle) {
      case self::PARAGRAPH_ALIAS_CAROUSEL:
        return self::VIEW_SCROLL;

      case self::PARAGRAPH_ALIAS_THEME_LIST:
      case self::PARAGRAPH_AUTHOR_PORTRAIT:
      case self::PARAGRAPH_AUTHOR_QUOTE:
      case self::PARAGRAPH_ALIAS_EDITOR:
      case self::PARAGRAPH_ALIAS_LINK:
      case self::PARAGRAPH_REVIEW:
      case self::PARAGRAPH_SPOTLIGHT_BOX:
      case self::PARAGRAPH_ARTICLE_CAROUSEL:
      case self::PARAGRAPH_VIDEO:
        return self::VIEW_DOTTED;
    }

    return self::VIEW_SCROLL;
  }

  /**
   * Get real paragraph type from an alias.
   *
   * @param string $alias
   *   The alias.
   *
   * @return string
   *   The paragraph type.
   */
  public function getParagraphType($alias) {
    switch ($alias) {
      case 'audio':
        return self::PARAGRAPH_ALIAS_AUDIO;

      case 'author_portrait':
        return self::PARAGRAPH_AUTHOR_PORTRAIT;

      case 'author_quote':
        return self::PARAGRAPH_AUTHOR_QUOTE;

      case 'carousel':
        return self::PARAGRAPH_ALIAS_CAROUSEL;

      case 'editor':
        return self::PARAGRAPH_ALIAS_EDITOR;

      case 'link':
        return self::PARAGRAPH_ALIAS_LINK;

      case 'picked_article_carousel':
        return self::PARAGRAPH_ALIAS_THEME_LIST;

      case 'review':
        return self::PARAGRAPH_REVIEW;

      case 'spotlight_box':
        return self::PARAGRAPH_SPOTLIGHT_BOX;

      case 'theme':
        return self::PARAGRAPH_ARTICLE_CAROUSEL;

      case 'theme_list':
        return self::PARAGRAPH_ALIAS_THEME_LIST;

      case 'video':
        return self::PARAGRAPH_VIDEO;
    }

    return $alias;
  }

  /**
   * Decode html entities in title.
   *
   * @param string $title
   *   The title.
   *
   * @return string
   *   The title with html entities decoded.
   */
  public function getTitle($title) {
    return html_entity_decode($title);
  }

  /**
   * Check if an array is associative.
   *
   * @param array $arr
   *   The array to check.
   *
   * @return bool
   *   True iff the array is associative.
   *
   * @see https://stackoverflow.com/a/173479
   */
  public static function isAssoc(array $arr = NULL) {
    if (NULL === $arr || [] === $arr) {
      return FALSE;
    }
    ksort($arr);
    return array_keys($arr) !== range(0, count($arr) - 1);
  }

}
