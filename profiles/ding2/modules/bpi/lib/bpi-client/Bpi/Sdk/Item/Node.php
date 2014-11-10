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
