<?php
/**
 * Created by PhpStorm.
 * User: Max
 * Date: 21.07.2015
 * Time: 12:34
 */

namespace Bpi\Sdk\Item;

/**
 * Class Facet
 * @package Bpi\Sdk\Item
 *
 * Single facet class
 */
class Facet
{

    /**
     * Facet name
     * @var string
     */
    private $facetName;

    /**
     * Array of terms in facet with amount of available items for each term
     * @var array
     */
    private $facetTerms;

    public function __construct()
    {
        $this->facetName = '';
        $this->facetTerms = array();
    }

    /**
     * Set facet name
     *
     * @param $facetName string
     * @return $this
     */
    public function setFacetName($facetName)
    {
        $this->facetName = $facetName;
        return $this;
    }

    /**
     * Get facet name
     *
     * @return string
     */
    public function getFacetName()
    {
        return $this->facetName;
    }

    /**
     * Add facet term
     *
     * @param $termName string
     * @param $termTitle string
     * @param $termAmount string
     * @return $this
     */
    public function addFacetTerm($termName, $termTitle, $termAmount)
    {
        $this->facetTerms[$termName] = new FacetTerm($termName, $termTitle, $termAmount);
        return $this;
    }

    /**
     * Get facet terms
     *
     * @return array
     */
    public function getFacetTerms()
    {
        return $this->facetTerms;
    }
}
