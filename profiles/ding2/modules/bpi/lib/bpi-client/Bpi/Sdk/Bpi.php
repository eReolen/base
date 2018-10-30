<?php

use Bpi\Sdk\Authorization;
use Bpi\Sdk\Exception\SDKException;
use Bpi\Sdk\Item\BaseItem;
use Bpi\Sdk\Item\Node;
use Bpi\Sdk\NodeList;
use GuzzleHttp\Client as GuzzleHttpClient;
use GuzzleHttp\Exception\ClientException as GuzzleClientException;

/**
 * TODO please add a general description about the purpose of this class.
 */
// @codingStandardsIgnoreLine
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
     * @var string
     */
    protected $endpoint;

    /**
     * Create Bpi Client
     *
     * @param string $endpoint URL
     * @param string $agencyId Agency ID
     * @param string $publicKey App key
     * @param string $secret
     */
    public function __construct($endpoint, $agencyId, $publicKey, $secret)
    {
        $this->endpoint = $endpoint;
        $this->authorization = new Authorization($agencyId, $publicKey, $secret);
    }

    private function request($method, $url, array $data = [])
    {
        try {
            $this->client = new GuzzleHttpClient([
                'base_uri' => $this->endpoint,
                'headers' => [
                    'Auth' => $this->authorization->toHTTPHeader(),
                ],
            ]);

            $result = $this->client->request($method, $url, $data);

            return $result;
        } catch (GuzzleClientException $e) {
            throw new SDKException($e->getMessage(), $e->getCode(), $e);
        }
    }

    /**
     * Get list of node based on some conditions
     *
     * @param array $queries available keys are: amount, offset, filter, sort
     *   filter and sort requires nested arrays
     * @return \Bpi\Sdk\NodeList
     */
    public function searchNodes(array $query = array())
    {
        $result = $this->request('GET', '/node/collection', [
            'query' => $query,
        ]);
        $element = new \SimpleXMLElement((string)$result->getBody());

        return new NodeList($element);
    }

    /**
     * Push new node to BPI
     *
     * @param array $data TODO please add some documentation of this property.
     * @throws \InvalidArgumentException
     * @return \Bpi\Sdk\Item\Node
     */
    public function push(array $data)
    {
        $result = $this->request('POST', '/node', ['form_params' => $data]);
        $element = new \SimpleXMLElement((string)$result->getBody());

        return new Node($element->item[0]);
    }

    /**
     * Mark node as syndicated
     *
     * @param string $id BPI node ID
     * @return boolean operation status
     */
    public function syndicateNode($id)
    {
        $result = $this->request('GET', '/node/syndicated', ['query' => ['id' => $id]]);

        return $result->getStatusCode() === 200;
    }

    /**
     * Mark node as deleted
     *
     * @param string $id BPI node ID
     * @return boolean operation status
     */
    public function deleteNode($id)
    {
        $result = $this->request('GET', '/node/delete', ['query' => ['id' => $id]]);

        return $result->getStatusCode() === 200;
    }

    /**
     * Get statistics
     * Parameterformat: Y-m-d
     *
     * TODO How about using DateTimes here and convert to string when calling the
     * API?
     *
     * @param string $dateFrom
     * @param string $dateTo
     */
    public function getStatistics($dateFrom, $dateTo)
    {
        $result = $this->request('GET', '/statistics', ['query' => ['dateFrom' => $dateFrom, 'dateTo' => $dateTo]]);
        $element = new \SimpleXMLElement((string)$result->getBody());

        return new BaseItem($element->item[0]);
    }

    /**
     * Get single Node by ID
     *
     * @param string $id BPI node ID
     * @return \Bpi\Sdk\Item\Node
     */
    public function getNode($id)
    {
        $result = $this->request('GET', '/node/item/' . $id);
        $element = new \SimpleXMLElement((string)$result->getBody());

        return new Node($element->item[0]);
    }

    /**
     * Get list of dictionaries
     *
     * @return array
     */
    public function getDictionaries()
    {
        $result = $this->request('GET', '/profile/dictionary');
        $element = new \SimpleXMLElement((string)$result->getBody());

        $dictionary = [];
        foreach ($element->xpath('/bpi/item') as $item) {
            $group = (string)$item->xpath('properties/property[@name = "group"]')[0];
            $name = (string)$item->xpath('properties/property[@name = "name"]')[0];
            if (!isset($dictionary[$group])) {
                $dictionary[$group] = [];
            }
            $dictionary[$group][] = $name;
        }

        return $dictionary;
    }
}
