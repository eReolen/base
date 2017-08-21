<?php
namespace Bpi\Sdk\Item;

/**
 * Class FacetTerm
 * @package Bpi\Sdk\Item
 *
 * Single facet term class
 */
class FacetTerm
{

    /**
     * @var string
     */
    private $name;

    /**
     * @var string
     */
    private $title;

    /**
     * @var int
     */
    private $amount;

    public function __construct($name, $title, $amount)
    {
        $this->name = $name;
        $this->title = $title ? $title : $name;
        $this->amount = $amount;
    }

    /**
     * Set name
     *
     * @param $name string
     * @return $this
     */
    public function setName($name)
    {
        $this->name = $name;
        return $this;
    }

    /**
     * Get name
     *
     * @return string
     */
    public function getName()
    {
        return $this->name;
    }

    /**
     * Set title
     *
     * @param $title string
     * @return $this
     */
    public function setTitle($title)
    {
        $this->title = $title;
        return $this;
    }

    /**
     * Get title
     *
     * @return string
     */
    public function getTitle()
    {
        return $this->title;
    }

    /**
     * Set amount
     *
     * @param $amount int
     * @return $this
     */
    public function setAmount($amount)
    {
        $this->amount = $amount;
        return $this;
    }

    /**
     * Get amount
     *
     * @return int
     */
    public function getAmount()
    {
        return $this->amount;
    }
}
