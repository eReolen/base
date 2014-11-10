<?php
namespace Bpi\Sdk\Item;

use Bpi\Sdk\Document;

class BaseItem
{
    protected $document;

    public function __construct(Document $document)
    {
        $this->document = $document;
    }

    /**
     *
     * @return array of node properties
     */
    public function getProperties()
    {
        $properties = array();
        $this->document->walkProperties(function($e) use(&$properties) {
            if (isset($properties[$e['name']])) {
                if (is_array($properties[$e['name']])) {
                    $properties[$e['name']][] = $e['@value'];
                } else {
                    $properties[$e['name']] = array($properties[$e['name']], $e['@value']);
                }
            } else {
                $properties[$e['name']] = $e['@value'];
            }
        });


        return $properties;
    }
}
