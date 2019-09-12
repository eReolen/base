<?php

namespace Drupal\reol_widget\Controller;

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

      if (!isset($parameters['query'])) {
        throw new \Exception('Empty query');
      }

      $query = $parameters['query'];
      $page = max(1, isset($parameters['page']) ? (int) $parameters['page'] : 0);
      $results_per_page = min(100, max(1, isset($parameters['results_per_page']) ? (int) $parameters['results_per_page'] : 10));

      $keys = $query;
      $conditions = reol_search_conditions_callback($keys);

      module_load_include('inc', 'opensearch', 'TingSearchCqlDoctor.class');
      $cqlDoctor = new \TingSearchCqlDoctor($keys);
      $query = '(' . $cqlDoctor->string_to_cql() . ')';
      $options['numFacets'] = variable_get('ting_search_number_of_facets', 25);
      // Extend query with selected facets.
      if (isset($conditions['facets']) && $conditions['facets'] != NULL) {
        $facets = $conditions['facets'];
        foreach ($facets as $facet) {
          $facet = explode(':', $facet, 2);
          if ($facet[0]) {
            $facet_array[] = $facet[0] . '="' . rawurldecode($facet[1]) . '"';
          }
        }

        $query .= ' AND ' . implode(' AND ', $facet_array);
      }

      module_load_include('inc', 'opensearch', 'opensearch.client');
      $result = opensearch_do_search($query, $page, $results_per_page, $options);

      $meta = NULL;
      $data = NULL;
      $links = NULL;
      if ($result) {
        $covers = $this->getCovers($result);
        $meta = $this->getMetadata($result, $page, $conditions, $query);
        $links = $this->getLinks($result, $page, $results_per_page);

        foreach ($result->collections as $collection) {
          /** @var \TingCollection $collection */
          /** @var \TingEntity $object */
          $object = $collection->getPrimary_object();
          $cover = isset($covers[$collection->getId()]) ? $covers[$collection->getId()] : NULL;
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
        'max_age' => 3600,
        'content' => [
          'meta' => $meta,
          'links' => $links,
          'data' => $data,
        ]
      ];
    }
    catch (\Exception $exception) {
      drupal_add_http_header('status', '400 Bad Request');
      drupal_json_output([
        'errors' => [
          'status' => 400,
          'title' => $exception->getMessage(),
        ],
      ]);
      drupal_exit();
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
   * @param \TingClientSearchResult $result
   *   The search result.
   * @param string $imageStyle
   *   The image style.
   *
   * @return array
   *   The covers.
   */
  private function getCovers(\TingClientSearchResult $result, $imageStyle = 'ding_list_medium') {
    $ids = [];
    foreach ($result->collections as $collection) {
      $ids[] = $collection->getId();
    }

    return array_map(function ($uri) use ($imageStyle) {
      $uri = image_style_url($imageStyle, $uri);

      return file_create_url($uri);
    }, ting_covers_get($ids));
  }

  /**
   * Get search result metadata.
   */
  private function getMetadata(\TingClientSearchResult $result, $page, $conditions, $query) {
    if (!$result) {
      return NULL;
    }

    return [
      'page' => $page,
      'count' => (int) $result->numTotalCollections,
      // 'conditions' => $conditions,
      // 'query' => $query,
      // 'url' => isset($_GET['url']) ? $_GET['url'] : null,.
    ];
  }

  /**
   * Get links.
   */
  private function getLinks(\TingClientSearchResult $result, $page) {
    $query = drupal_get_query_parameters();

    $links['self'] = $this->getUrl($query);
    if (isset($result->more) && $result->more) {
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

}
