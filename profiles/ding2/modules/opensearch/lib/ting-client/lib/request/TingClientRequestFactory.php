<?php

class TingClientRequestFactory {

  public function __construct($urls, $auth = NULL) {
    $this->urls = $urls;
    $this->auth = $auth;
  }

  /**
   * Get certain webservice url.
   *
   * @param string $key
   *   WebService link identitifer as mapped in the ting.client.inc file,
   *   line 426.
   * @see ting.client.inc
   *
   * @return String
   *   Webservice url, if any. NULL if entry not found.
   */
  public function getRequestUrl($key){
    $url = isset($this->urls[$key]) ? $this->urls[$key] : NULL;

    return $url;
  }

  /**
   * @return TingClientSearchRequest
   */
  public function getSearchRequest() {
    return new TingClientSearchRequest($this->urls['search'], $this->auth);
  }

  /**
   * @return TingClientCollectionRequest
   */
  public function getCollectionRequest() {
    return new TingClientCollectionRequest($this->urls['collection'], $this->auth);
  }

  /**
   * @return TingClientObjectRequest
   */
  public function getObjectRequest() {
    return new TingClientObjectRequest($this->urls['object'], $this->auth);
  }

  /**
   * @return TingClientObjectRecommendationRequest
   */
  function getObjectRecommendationRequest() {
    return new TingClientObjectRecommendationRequest($this->urls['recommendation'], $this->auth);
  }

  /**
   * @return TingClientInfomediaArticleRequest
   */
  function getInfomediaArticleRequest(){
    return new TingClientInfomediaArticleRequest($this->urls['infomedia'], $this->auth);
  }

  /**
   * @return TingClientInfomediaReviewRequest
   */
  function getInfomediaReviewRequest(){
    return new TingClientInfomediaReviewRequest($this->urls['infomedia'], $this->auth);
  }

  /**
   * @return TingFulltextRequest
   */
  function getFulltextRequest() {
    return new TingFulltextRequest($this->urls['object'], $this->auth);
  }

  /**
   * @return TingCLientMarcXchangeRequest
   */
  function getMarcXchangeRequest() {
    return new TingClientMarcXchangeRequest($this->urls['object'], $this->auth);
  }
}
