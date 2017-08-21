<?php
namespace Bpi\Sdk\Item;

class Node extends BaseItem
{
    /**
     * @var array
     */
    protected $assets;

    /**
     * Get node assets (images)
     *
     * @return array
     */
    public function getAssets()
    {
        if (!$this->assets) {
            $assets = [];
            foreach ($this->getProperties() as $key => $val)
            {
                if (strpos($key, 'asset') !== FALSE)
                {
                    $assets[$key] = $val;
                }
            }
            $this->assets = $assets;
        }

        return $this->assets;
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
