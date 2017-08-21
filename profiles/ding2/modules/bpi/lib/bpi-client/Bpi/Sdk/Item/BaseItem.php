<?php
namespace Bpi\Sdk\Item;

/**
 * TODO please add a documentation for this class.
 */
class BaseItem
{
    /**
     * @var \SimpleXMLElement
     */
    protected $element;

    /**
     * @var array
     */
    protected $properties;

    public function __construct(\SimpleXMLElement $element)
    {
        $this->element = $element;
    }

    /**
     *
     * @return array of node properties
     */
    public function getProperties()
    {
        if (!$this->properties) {
            $properties = [];
            foreach ($this->element->xpath('properties/property') as $property) {
                $name = (string)$property['name'];
                $value = (string) $property;
                if (isset($properties[$name])) {
                    if (is_array($properties[$name])) {
                        $properties[$name][] = $value;
                    } else {
                        $properties[$name] = array($properties[$name], $value);
                    }
                } else {
                    $properties[$name] = $value;
                }
            };
            $this->properties = $properties;
        }

        return $this->properties;
    }
}
