<?php
namespace Bpi\Sdk;

use Symfony\Component\DomCrawler\Crawler;

class Link
{
    /**
     *
     * @var \Symfony\Component\DomCrawler\Crawler
     */
    protected $crawler;

    /**
     * @throws Exception\UndefinedHypermedia
     *
     * @param \Symfony\Component\DomCrawler\Crawler $crawler
     */
    public function __construct(Crawler $crawler)
    {
        $this->crawler = $crawler;
        $this->testConsistency();
    }
    
    /**
     * Try crawler for consistency of data
     * 
     * @throws Exception\InvalidHypermedia
     *
     * @returns bool
     */
    protected function testConsistency()
    {
        try {
            $this->crawler->attr('href');
            $this->crawler->attr('rel');
        } catch (\InvalidArgumentException $e) {
          throw  $e;
          throw new Exception\UndefinedHypermedia();
            return false;
        }

        return true;
    }

    /**
     * 
     * @param \Bpi\Sdk\Document $document
     */
    public function follow(Document $document)
    {
        $this->get($document);
    }

    /**
     * Perform HTTP GET for given URI
     *
     * @param \Bpi\Sdk\Document $document
     */
    public function get(Document $document)
    {
        $document->request('GET', $this->crawler->attr('href'));
    }

    /**
     * Perform HTTP POST for given URI
     *
     * @param \Bpi\Sdk\Document $document
     */
    public function post(Document $document)
    {
        $document->request('POST', $this->crawler->attr('href'));
    }

    /**
     * Perform HTTP DELETE for given URI
     *
     * @param \Bpi\Sdk\Document $document
     */
    public function delete(Document $document)
    {
        $document->request('DELETE', $this->crawler->attr('href'));
    }

    /**
     * Perform HTTP PUT for given URI
     *
     * @param \Bpi\Sdk\Document $document
     */
    public function put(Document $document)
    {
        $document->request('PUT', $this->crawler->attr('href'));
    }

    /**
     * 
     * @return array properties
     */
    public function toArray()
    {
        $properties = array();
        foreach($this->crawler as $node)
        {
            foreach ($node->attributes as $attr_name => $attr)
            {
                $properties[$attr_name] = $attr->value;
            }
        }
        return $properties;
    }
}
