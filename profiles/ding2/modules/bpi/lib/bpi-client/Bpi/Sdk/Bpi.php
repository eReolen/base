<?php
require_once __DIR__ . '/../../vendor/autoload.php';

class Bpi
{
    /**
     *
     * @var \Goutte\Client
     */
    protected $client;

    /**
     *
     * @var \Bpi\Sdk\Authorization
     */
    protected $authorization;

    /**
     *
     * @var \Bpi\Sdk\Document
     */
    protected $endpoint;

    /**
     *
     * @var \Bpi\Sdk\Document
     */
    protected $current_document;

    /**
     * Create Bpi Client
     *
     * @param string $endpoint URL
     * @param string $agency_id Agency ID
     * @param string $api_key App key
     * @param string $secret_key
     */
    public function __construct($endpoint, $agency_id, $api_key, $secret_key)
    {
        $this->client = new \Goutte\Client();
        $this->authorization = new \Bpi\Sdk\Authorization($agency_id, $api_key, $secret_key);
        $this->current_document = $this->endpoint = $this->createDocument();
        $this->endpoint->loadEndpoint($endpoint);
    }

    /**
     * Create new document
     *
     * @return \Bpi\Sdk\Document
     */
    protected function createDocument()
    {
        return new \Bpi\Sdk\Document($this->client, $this->authorization);
    }

    /**
     * Get list of node based on some conditions
     *
     * @param array $queries available keys are: amount, offset, filter, sort
     *   filter and sort requires nested arrays
     * @return \Bpi\Sdk\NodeList
     */
    public function searchNodes(array $queries = array())
    {
        $nodes = $this->createDocument();
        $endpoint = clone $this->endpoint;
        $endpoint->firstItem('name', 'node')
            ->link('collection')
            ->get($nodes);

        $nodes->firstItem('type', 'collection')
            ->query('refinement')
            ->send($nodes, $queries);

        $this->current_document = $nodes;

        return new \Bpi\Sdk\NodeList($nodes);
    }

    /**
     * Push new node to BPI
     *
     * @param array $data
     * @throws \InvalidArgumentException
     * @return \Bpi\Sdk\Item\Node
     */
    public function push(array $data)
    {
        $node = $this->createDocument();
        $nodes = clone $this->endpoint;
        $nodes->firstItem('name', 'node')
            ->template('push')
            ->eachField(function ($field) use ($data) {
                if (!isset($data[(string)$field]))
                    throw new \InvalidArgumentException(sprintf('Field [%s] is required', (string) $field));

                $field->setValue($data[(string) $field]);
            })->post($node);

        $this->current_document = $node;

        return new \Bpi\Sdk\Item\Node($node);
    }

    /**
     * Mark node as syndicated
     *
     * @param string $id BPI node ID
     * @return boolean operation status
     */
    public function syndicateNode($id)
    {
        $result = $this->createDocument();

        $endpoint = clone $this->endpoint;
        $endpoint->firstItem('name', 'node')
            ->query('syndicated')
            ->send($result, array('id' => $id));

        $this->current_document = $result;

        return $result->status()->isSuccess();
    }

    /**
     * Mark node as deleted
     *
     * @param string $id BPI node ID
     * @return boolean operation status
     */
    public function deleteNode($id)
    {
        $result = $this->createDocument();

        $endpoint = clone $this->endpoint;
        $endpoint->firstItem('name', 'node')
            ->query('delete')
            ->send($result, array('id' => $id));

        $this->current_document = $result;

        return $result->status()->isSuccess();
    }

    /**
     * Get statistics
     * Parameterformat: Y-m-d
     *
     * @param string $dateFrom
     * @param string $dateTo
     */
    public function getStatistics($dateFrom, $dateTo)
    {
        $result = $this->createDocument();
        $endpoint = clone $this->endpoint;
        $endpoint->firstItem('name', 'node')
            ->query('statistics')
            ->send($result, array('dateFrom'=>$dateFrom, 'dateTo'=>$dateTo));

        $this->current_document = $result;

        return new \Bpi\Sdk\Item\BaseItem($result);
    }

    /**
     * Get single Node by ID
     *
     * @param string $id BPI node ID
     * @return \Bpi\Sdk\Item\Node
     */
    public function getNode($id)
    {
        $result = $this->createDocument();

        $endpoint = clone $this->endpoint;
        $endpoint->firstItem('name', 'node')
            ->query('item')
            ->send($result, array('id' => $id));

        $this->current_document = $result;

        return new \Bpi\Sdk\Item\Node($result);
    }

    /**
     * Get list of dictionaries
     *
     * @return array
     */
    public function getDictionaries()
    {
        $result = $this->createDocument();

        $endpoint = clone $this->endpoint;
        $endpoint->firstItem('name', 'profile')
            ->link('dictionary')
            ->get($result);

        $this->current_document = $result;

        $dictionary = array();
        foreach ($result as $item)
        {
            $properties = array();
            $item->walkProperties(function($property) use (&$properties){
                $properties[$property['name']] = $property['@value'];
            });

            $dictionary[$properties['group']][] = $properties['name'];
        }

        return $dictionary;
    }

    /**
     *
     * @return \Bpi\Sdk\Document
     */
    public function _getCurrentDocument()
    {
        return $this->current_document;
    }
}
