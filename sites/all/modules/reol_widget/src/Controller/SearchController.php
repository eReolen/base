<?php

namespace Drupal\reol_widget\Controller;

use OpenSearch\OpenSearchTingSearchResult;
use Ting\Search\TingSearchCommonFields;
use Ting\Search\TingSearchSort;

/**
 * Search controller.
 */
class SearchController {

  /**
   * Search action.
   */
  public function search() {
    try {
      $this->extractQueryFromUrl();
      $parameters = drupal_get_query_parameters();

      if (empty($parameters['query'])) {
        throw new \RuntimeException('Empty query');
      }

      $query = $parameters['query'];
      $page = max(1, isset($parameters['page']) ? (int) $parameters['page'] : 0);
      $results_per_page = min(100, max(1, isset($parameters['results_per_page']) ? (int) $parameters['results_per_page'] : 10));
      $sort = $this->getSort($parameters);

      $keys = $query;
      $conditions = reol_search_conditions_callback($keys);
      if (isset($conditions['facets'])) {
        // @TODO: Is this the right way to handle facets?
        module_load_include('inc', 'opensearch', 'TingSearchCqlDoctor.class');
        $cqlDoctor = new \TingSearchCqlDoctor($keys);
        $query = '(' . $cqlDoctor->string_to_cql() . ')';
        // Extend query with selected facets.
        foreach ($conditions['facets'] as $facet) {
          $facet = explode(':', $facet, 2);
          if ($facet[0]) {
            $facet_array[] = $facet[0] . '="' . rawurldecode($facet[1]) . '"';
          }
        }

        $query .= ' AND ' . implode(' AND ', $facet_array);
      }

      $query = ting_start_query()
        ->withFullTextQuery($query)
        ->withCount($results_per_page)
        ->withPage($page)
        ->withTermsPrFacet(variable_get('ting_search_number_of_facets', 25));
      if (isset($sort['field'], $sort['direction'])) {
        $query = $query->withSort($sort['field'], $sort['direction']);
      }

      $result = $query->execute();

      $meta = NULL;
      $data = NULL;
      $links = NULL;
      if ($result->getNumCollections() > 0) {
        $collections = $result->getTingEntityCollections();
        $covers = $this->getCovers($collections);
        $meta = $this->getMetadata($result, $page);
        $links = $this->getLinks($result, $page);

        foreach ($result->getTingEntityCollections() as $collection) {
          /** @var \TingCollection $collection */
          /** @var \TingEntity $object */
          $object = $collection->getPrimary_object();
          $cover = $covers[$collection->getId()] ?? NULL;
          $url = url('ting/object/' . $collection->getId(), ['absolute' => TRUE]);
          $data[] = [
            'id' => $collection->getId(),
            'title' => $collection->getTitle(),
            'cover' => $cover,
            'abstract' => $object->getAbstract(),
            'ac_source' => $object->ac_source,
            'classification' => $object->classification,
            'contributors' => $object->contributors,
            'contributors' => $object->getContributors(),
            'creators' => $object->creators,
            'creators' => $object->getCreators(),
            'date' => $object->date,
            'description' => $object->description,
            'extent' => $object->extent,
            'isPartOf' => $object->isPartOf,
            'isbn' => $object->isbn,
            'language' => $object->language,
            'localId' => $object->localId,
            'ownerId' => $object->ownerId,
            'relations' => $object->relations,
            'serieDescription' => $object->serieDescription,
            'serieNumber' => $object->serieNumber,
            'serieTitle' => $object->serieTitle,
            'subjects' => $object->subjects,
            'type' => $object->type,
            'online_url' => $object->online_url,
            'url' => $url,
          ];
        }
      }

      // @see http://jsonapi.org/
      return [
        'meta' => $meta,
        'links' => $links,
        'data' => $data,
      ];
    }
    catch (\Exception $exception) {
      drupal_add_http_header('status', '400 Bad Request');
      return [
        'errors' => [
          'status' => 400,
          'title' => $exception->getMessage(),
        ],
      ];
    }
  }

  /**
   * Extract query from ereolen.dk search url.
   *
   * Note: reol_search_conditions_callback uses $_REQUEST.
   */
  private function extractQueryFromUrl() {
    $parameters = drupal_get_query_parameters();
    if (isset($parameters['url'])) {
      $url = parse_url($parameters['url']);

      // Extract search query from ting search url.
      if (preg_match('@/search/ting/(?P<query>.+)@', $url['path'], $matches)) {
        $_REQUEST['query'] = $_GET['query'] = urldecode($matches['query']);
      }

      // Merge in query from url.
      if (isset($url['query'])) {
        parse_str($url['query'], $query);
        $_GET += $query;
        $_REQUEST += $query;
      }
    }
  }

  /**
   * Get list of cover urls from search result.
   *
   * @param TingCollection[] $collections
   *   The collections.
   * @param string $imageStyle
   *   The image style.
   *
   * @return array
   *   The covers.
   */
  private function getCovers(array $collections, $imageStyle = 'ding_list_medium') {
    $ids = array_map(function (\TingCollection $collection) {
      return $collection->getId();
    }, $collections);

    return array_map(function ($uri) use ($imageStyle) {
      $uri = image_style_url($imageStyle, $uri);

      return file_create_url($uri);
    }, ting_covers_get($ids));
  }

  /**
   * Get search result metadata.
   *
   * @param \OpenSearch\OpenSearchTingSearchResult $result
   *   The search result.
   * @param int $page
   *   The page.
   *
   * @return array
   *   The metadata.
   */
  private function getMetadata(OpenSearchTingSearchResult $result, $page) {
    return [
      'page' => $page,
      'count' => (int) $result->getNumCollections($collections),
    ];
  }

  /**
   * Get links.
   */
  private function getLinks(OpenSearchTingSearchResult $result, $page) {
    $query = drupal_get_query_parameters();

    $links['self'] = $this->getUrl($query);
    if ($result->hasMoreResults()) {
      $links['next'] = $this->getUrl(['page' => $page + 1]);
    }
    if ($page > 1) {
      $links['prev'] = ($page > 2) ? $this->getUrl(['page' => $page - 1]) : $this->getUrl([], ['page']);
      $links['first'] = $this->getUrl([], ['page']);
    }

    return $links;
  }

  /**
   * Get an absolute url to the current path.
   *
   * @param array $query
   *   The query to add.
   * @param array $unset
   *   Any query parameter names to unset.
   *
   * @return string
   *   The absolute url.
   */
  private function getUrl(array $query = [], array $unset = []) {
    $query = $query + drupal_get_query_parameters();
    foreach ($unset as $key) {
      unset($query[$key]);
    }
    return url(current_path(), ['absolute' => TRUE, 'query' => $query]);
  }

  /**
   * Map from search field to TingSearchCommonFields constants.
   *
   * @var array
   *
   * @see _opensearch_search_map_common_sort_fields()
   */
  private static $searchFields = [
    'acquisitionDate' => 'acquisitionDate',
    // Supported by _opensearch_search_map_common_sort_fields().
    'author' => TingSearchCommonFields::AUTHOR,
    'date' => TingSearchCommonFields::DATE,
    'title' => TingSearchCommonFields::TITLE,
  ];

  /**
   * Get sort field and direction.
   *
   * @param array $parameters
   *   The query string parameters.
   * @param string $defaultField
   *   The default search field.
   * @param string $defaultDirection
   *   The default search direction.
   *
   * @return array|null
   *   The sort if any.
   */
  private function getSort(array $parameters, $defaultField = 'acquisitionDate', $defaultDirection = 'desc') {
    $field = strtolower($parameters['sort']['field'] ?? $defaultField);
    $direction = strtolower($parameters['sort']['direction'] ?? $defaultDirection);

    // Check that sort field is valid. Otherwise, use default.
    if (!isset(self::$searchFields[$field])) {
      if (!isset(self::$searchFields[$defaultField])) {
        return NULL;
      }
      $field = $defaultField;
    }
    $field = self::$searchFields[$field];

    // Make sure that direction is valid.
    $direction = (0 === strcasecmp(TingSearchSort::DIRECTION_DESCENDING, $direction))
      ? TingSearchSort::DIRECTION_DESCENDING
      : TingSearchSort::DIRECTION_ASCENDING;

    return ['field' => $field, 'direction' => $direction];
  }

}
