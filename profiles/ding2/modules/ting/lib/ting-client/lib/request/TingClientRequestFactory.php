<?php

class TingClientRequestFactory {
	public function __construct($urls) {
		$this->urls = $urls;
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
		return new TingClientSearchRequest($this->urls['search']);
	}

	/**
	 * @return TingClientScanRequest
	 */
	public function getScanRequest() {
		return new TingClientScanRequest($this->urls['scan']);
	}

	/**
	 * @return TingClientCollectionRequest
	 */
	public function getCollectionRequest() {
		return new TingClientCollectionRequest($this->urls['collection']);
	}

	/**
	 * @return TingClientObjectRequest
	 */
	public function getObjectRequest() {
		return new TingClientObjectRequest($this->urls['object']);
	}

	/**
	 * @return TingClientSpellRequest
	 */
	public function getSpellRequest() {
		return new TingClientSpellRequest($this->urls['spell']);
	}

	/**
	 * @return TingClientObjectRecommendationRequest
	 */
	function getObjectRecommendationRequest() {
		return new TingClientObjectRecommendationRequest($this->urls['recommendation']);
	}

	/**
	 * @ return TingClientInfomediaArticleRequest
	 */
	function getInfomediaArticleRequest(){
		return new TingClientInfomediaArticleRequest($this->urls['infomedia']);
	}

	/**
	 * @return TingClientInfomediaReviewRequest
	 */
	function getInfomediaReviewRequest(){
		return new TingClientInfomediaReviewRequest($this->urls['infomedia']);
	}

	/**
	 * @return TingFulltextRequest
	 */
	function getFulltextRequest() {
		return new TingFulltextRequest($this->urls['object']);
	}
}
