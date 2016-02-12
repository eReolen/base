<?php
namespace Bpi\Sdk\Item;

class Node extends BaseItem
{
    /**
     * Get node assets (images)
     *
     * @return array
     */
    public function getAssets()
    {
        $result = array();
        foreach ($this->getProperties() as $key => $val)
        {
            if (strpos($key, 'asset') !== FALSE)
            {
                $result[$key] = $val;
            }
        }

        return $result;
    }

    /**
     * Get node tags.
     *
     * @return array
     */
    public function getTags()
    {
        $tags = array();
        $this->document->walkTags(function($e) use(&$tags) {
            if (!empty($e['tag_name'])) {
                $tags[] = $e['tag_name'];
            }
        });

        return $tags;
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
