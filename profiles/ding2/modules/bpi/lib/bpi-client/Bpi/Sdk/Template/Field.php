<?php
namespace Bpi\Sdk\Template;

class Field
{
    /**
     *
     * @var \DOMNode
     */
    protected $node;

    /**
     * Field value.
     *
     * @var mixed
     */
    protected $value;

    /**
     * 
     * @param \DOMNode $node
     */
    public function __construct(\DOMNode $node)
    {
        $this->node = $node;
    }

    /**
     * Name of the field.
     *
     * @return string
     */
    public function __toString()
    {
        return $this->node->getAttribute('name');
    }

    /**
     * Set value for the field.
     *
     * @param mixed $value
     */
    public function setValue($value)
    {
        $this->value = $value;
    }

    /**
     * Copy current filed name/value to external list.
     *
     * @param array $list
     */
    public function assignToList(array &$list)
    {
        $list[(string) $this] = $this->value;
    }
}
