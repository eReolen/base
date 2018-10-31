<?php
namespace Bpi\Sdk\Item;

class Node extends BaseItem
{
    /**
     * @var array
     */
    protected $assets;

    /**
     * @var array
     */
    protected $tags;

    /**
     * Get node assets (images)
     *
     * @return array
     */
    public function getAssets()
    {
        if (!$this->assets) {
            $assets = array();

            foreach ($this->element->xpath('assets/file') as $asset) {
                $type = (string)$asset['type'];
                if (!isset($assets[$type])) {
                    $assets[$type] = array();
                }
                // Convert attributes to associative array.
                $properties = array();
                foreach ($asset->attributes() as $name => $value) {
                    $properties[$name] = (string)$value;
                }
                $assets[$type][] = $properties;
            }

            $this->assets = $assets;
        }

        return $this->assets;
    }

    /**
     * Get node tags.
     *
     * @return array
     */
    public function getTags()
    {
        if (!$this->tags) {
            $tags = array();

            foreach ($this->element->xpath('tags/tag') as $tag) {
                $name = (string)$tag['tag_name'];
                if (!empty($name)) {
                    $tags[] = $name;
                }
            }

            $this->tags = $tags;
        }
        return $this->tags;
    }

    public function syndicate()
    {
        // @todo implementation
    }

    public function push()
    {
        // @todo implementation
    }

    public function delete()
    {
        // @todo implementation
    }
}
