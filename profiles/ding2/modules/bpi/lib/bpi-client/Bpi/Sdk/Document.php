<?php
namespace Bpi\Sdk;

use Goutte\Client;
use Symfony\Component\DomCrawler\Crawler;

/**
 * TODO please add a general description about the purpose of this class.
 */
class Document implements \Iterator, \Countable
{
    /**
     *
     * @var \Goutte\Client
     */
    protected $http_client;

    /**
     *
     * @var \Bpi\Sdk\Authorization
     */
    protected $authorization;

    /**
     *
     * @var \Symfony\Component\DomCrawler\Crawler
     */
    protected $crawler;

    /**
     * Array of available facets relatively current request
     * @var array
     */
    protected $facets;

    /**
     *
     * @param \Goutte\Client $client
     * @param \Bpi\Sdk\Authorization $authorization
     */
    public function __construct(Client $client, Authorization $authorization)
    {
        $this->http_client = $client;
        $this->authorization = $authorization;
    }

    /**
     * @param string $endpoint API URL
     * @return \Bpi\Sdk\Document same instance
     */
    public function loadEndpoint($endpoint)
    {
        $this->request('GET', $endpoint);
        return $this;
    }

    /**
     * Gateway to make direct requests to API
     *
     * @param string $method
     * @param string $uri
     * @param array $params
     *
     * @return \Bpi\Sdk\Document same instance
     */
    public function request($method, $uri, array $params = array())
    {
        $headers = array(
            'HTTP_Auth' => $this->authorization->toHTTPHeader(),
            'HTTP_Content_Type' => 'application/vnd.bpi.api+xml',
        );

        $this->crawler = $this->http_client->request($method, $uri, $params, array(), $headers);
        $this->crawler = $this->crawler->filter('bpi > item');
        $this->crawler->rewind();

        if ($this->status()->isError())
        {
            if ($this->status()->isClientError())
                throw new Exception\HTTP\ClientError($this->http_client->getResponse()->getContent(), $this->status()->getCode());

            if ($this->status()->isServerError())
                throw new Exception\HTTP\ServerError($this->http_client->getResponse()->getContent(), $this->status()->getCode());

            throw new Exception\HTTP\Error($this->http_client->getResponse()->getContent(), $this->status()->getCode());
        }

        return $this;
    }

    /**
     * Get last response status
     *
     * @return \Bpi\Sdk\ResponseStatus
     */
    public function status()
    {
        return new ResponseStatus($this->http_client->getResponse()->getStatus());
    }

    /**
     * Dump latest raw response data
     *
     * @return string
     */
    public function dumpRawResponse()
    {
        return $this->http_client->getResponse();
    }

    /**
     * Dump latest raw request data
     *
     * @return string
     */
    public function dumpRawRequest()
    {
        return print_r($this->http_client->getRequest(), true);
    }

    /**
     * Access hypermedia link.
     *
     * @throws Exception\UndefinedHypermedia
     * @param string $rel
     * @return \Bpi\Sdk\Link
     */
    public function link($rel)
    {
        try {
            $crawler = $this->crawler
                ->filter("hypermedia > link[rel='{$rel}']")
                ->first()
            ;

            return new Link($crawler);
        }
        catch (\InvalidArgumentException $e)
        {
            throw new Exception\UndefinedHypermedia(sprintf('There is no such link [%s]', $rel));
        }
    }

    /**
     * Click on link.
     *
     * @param \Bpi\Sdk\Link $link
     */
    public function followLink(Link $link)
    {
        $link->follow($this);
    }

    /**
     * Access hypermedia query.
     *
     * @throws Exception\UndefinedHypermedia
     * @param string $rel
     * @return \Bpi\Sdk\Query
     */
    public function query($rel)
    {
        try
        {
            $query = $this->crawler
                  ->filter("hypermedia > query[rel='{$rel}']")
                  ->first()
            ;

            return new Query($query);
        }
        catch (\InvalidArgumentException $e)
        {
            throw new Exception\UndefinedHypermedia(sprintf('There is no query [%s]', $rel));
        }
    }

    /**
     * Set facets based on current request
     * @throws \Exception
     */
    public function setFacets()
    {
        try {
            $query = $this->crawler
                  ->filter("item[type='facet']")
                  ->each(
                        function ($e) {
                          return simplexml_import_dom($e);
                        }
                  );

            $facets = new Facets();
            $facets->buildFacets($query);
            $this->facets = $facets;
        } catch (\InvalidArgumentException $e) {
            throw new \Exception('There is no facets');
        }
    }

    /**
     * Get facets for current request
     * @return array
     */
    public function getFacets()
    {
        return $this->facets;
    }

    /**
     * Send query.
     *
     * @param \Bpi\Sdk\Query $query
     * @param array $params
     */
    public function sendQuery(Query $query, $params)
    {
        $query->send($this, $params);
    }

    /**
     * Access hypermedia template.
     *
     * @throws Exception\UndefinedHypermedia
     * @param string $rel
     * @return \Bpi\Sdk\Template
     */
    public function template($rel)
    {
        try
        {
            $query = $this->crawler
                  ->filter("hypermedia > template[rel='{$rel}']")
                  ->first()
            ;

            return new Template($query);
        }
        catch (\InvalidArgumentException $e)
        {
            throw new Exception\UndefinedHypermedia(sprintf('There is no such template [%s]', $rel));
        }
    }

    /**
     * Post rendered template.
     *
     * @param \Bpi\Sdk\Template $template
     */
    public function postTemplate(Template $template)
    {
        $template->post($this);
    }

    /**
     * Checks current item type
     *
     * @param string $type
     * @return bool
     */
    public function isTypeOf($type)
    {
        return $this->crawler->current()->getAttribute('type') == $type;
    }

    /**
     * Iterates over all properties of current item
     */
    public function walkProperties($callback)
    {
        $crawler = new Crawler($this->crawler->current());
        return $crawler->filter('item property')->each(function($e) use($callback) {
            $sxml = simplexml_import_dom($e);
            $callback(current($sxml->attributes()) + array('@value' => (string) $sxml));
        });
    }

    /**
     *
     * @return array
     */
    public function propertiesToArray()
    {
        $properties = array();
        $this->walkProperties(function($p) use(&$properties){
            $properties[$p['name']] = $p['@value'];
        });

        return $properties;
    }

    /**
     * Finds first matched item by attribute value
     *
     * @param string $name
     * @param mixed $value
     * @throws \InvalidArgumentException
     *
     * @return \Bpi\Sdk\Document same instance
     */
    public function firstItem($attr, $value) {
        $this->crawler = $this->crawler
            ->filter("item[$attr='{$value}']")
            ->first()
        ;

        if (!$this->crawler->count())
            throw new \InvalidArgumentException(sprintf('Item with attribute "%s" and value "%s" was not found', $attr, $value));

        $this->crawler->rewind();
        return $this;
    }

    /**
     * Filter items (<item> tags) by attribute values
     *
     * @param string $name
     * @param mixed $value
     * @throws \Bpi\Sdk\Exception\EmptyList
     *
     * @return \Bpi\Sdk\Document same instance
     */
    public function reduceItemsByAttr($attr, $value) {
        $this->crawler = $this->crawler->filter("item[$attr='{$value}']");

        if (!$this->crawler->count()) {
            throw new Exception\EmptyList(sprintf('No items remain after reduce was made by attr [%s], value [%s]', $attr, $value));
        }

        $this->crawler->rewind();
        return $this;
    }

    /**
     * Clear previous response if any
     */
    public function clear()
    {
        $this->crawler = new Crawler();
    }

    /**
     * Iterator interface implementation
     *
     * @group Iterator
     */
    function rewind()
    {
        $this->crawler->rewind();
    }

    /**
     * Returns same instance but with internal pointer to current item in collection
     *
     * @group Iterator
     * @return \Bpi\Sdk\Document will return same instance
     */
    function current()
    {
        return $this;
    }

    /**
     * Key of current iteration position
     *
     * @group Iterator
     */
    function key()
    {
        return $this->crawler->key();
    }

    /**
     * Iterate to next item
     *
     * @group Iterator
     */
    function next()
    {
        $this->crawler->next();
    }

    /**
     * Checks if is ready for iteration
     *
     * @group Iterator
     * @return boolean
     */
    function valid()
    {
        return $this->crawler->valid();
    }

    /**
     * Length of items in document
     *
     * @group Iterator
     */
    public function count()
    {
        return $this->crawler->count();
    }
}
