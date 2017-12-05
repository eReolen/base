<?php
namespace Bpi\Sdk;

use Bpi\Sdk\Facets;
use Bpi\Sdk\Item\FacetTerm;
use Bpi\Sdk\Item\Node;
use Bpi\Sdk\Item\Facet;

/**
 * TODO please add a general description about the purpose of this class.
 */
class NodeList implements \Iterator, \Countable
{
    /**
     * @var \Bpi\Sdk\SimpleXMLElement|\SimpleXMLElement
     */
    private $element;

    /**
     * Total amount of items on server
     *
     * @var int
     */
    public $total = 0;

    /**
     * @var int
     *
     * Position in nodes array.
     */
    private $position = 0;

    /**
     * @var array
     */
    protected $nodes = [];

    protected $facets = [];

    /**
     *
     * @param SimpleXMLElement $element
     */
    public function __construct(\SimpleXMLElement $element)
    {
        $this->element = $element;
        try {
            $collection = $this->element->xpath('/bpi/item[@type = "collection"]')[0];
            $this->total = (int)($collection->xpath('properties/property[@name = "total"]')[0]);

            foreach ($this->element->xpath('/bpi/item[@type = "entity"]') as $node) {
                $this->nodes[] = new Node($node);
            }
        } catch (Exception\EmptyList $e) {
        }
    }

    /**
     * Iterator interface implementation
     *
     * @group Iterator
     */
    public function rewind()
    {
        $this->position = 0;
    }

    /**
     * Returns same instance but with internal pointer to current item in collection
     *
     * @group Iterator
     */
    public function current()
    {
        return $this->nodes[$this->position];
    }

    /**
     * Key of current iteration position
     *
     * @group Iterator
     */
    public function key()
    {
        return $this->position;
    }

    /**
     * Iterate to next item
     *
     * @group Iterator
     */
    public function next()
    {
        $this->position++;
    }

    /**
     * Checks if is ready for iteration
     *
     * @group Iterator
     * @return boolean
     */
    public function valid()
    {
        return isset($this->nodes[$this->position]);
    }

    /**
     *
     * @return integer
     */
    public function count()
    {
        return count($this->nodes);
    }

    /**
     * Get facets.
     *
     * @return Facets
     */
    public function getFacets()
    {
        if (!$this->facets) {
            $facets = new Facets();
            foreach ($this->element->xpath('/bpi/item[@type = "facet"]') as $el) {
                $facet = new Facet();
                $facet->setFacetName((string)$el['name']);
                foreach ($el->xpath('properties/property') as $property) {
                    $facet->addFacetTerm((string)$property['name'], (string)$property['title'], (int)$property);
                }
                $facets->addFacet($facet);
            }
            $this->facets = $facets;
        }

        return $this->facets;
    }
}
