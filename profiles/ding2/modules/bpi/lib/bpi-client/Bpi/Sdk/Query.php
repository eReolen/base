<?php
namespace Bpi\Sdk;

use Symfony\Component\DomCrawler\Crawler;

class Query
{
    /**
     *
     * @var Symfony\Component\DomCrawler\Crawler
     */
    protected $crawler;

    /**
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
            $this->crawler->filter('param');
        } catch (\InvalidArgumentException $e) {
            throw new Exception\UndefinedHypermedia('Query has no href attribute or parameters inside');
            return false;
        }

        return true;
    }

    /**
     * 
     * @param array $params
     * @throws Exception\InvalidQueryParameter
     */
    protected function validate(array $params)
    {
        foreach ($params as $user_param => $value)
        {
            $param = $this->crawler->filter("param[name='{$user_param}']");
            if ($param->count() <= 0)
            {
                throw new Exception\InvalidQueryParameter(sprintf('The API has no such query parameter [%s] on page [%s]', $user_param, $this->crawler->attr('href')));
            }

            if ($param->attr('type') == 'multiple' && !is_array($value))
            {
                throw new Exception\InvalidQueryParameter(sprintf('The API has declared a multiple value query parameter [%s], array expected', $user_param));
            }

            if (is_array($value) && $param->attr('type') != 'multiple')
            {
                throw new Exception\InvalidQueryParameter(sprintf('The API has declared query parameter [%s] as single value, array was given', $user_param));
            }
        }
    }
    
    /**
     * Transform query to array
     * 
     * @return array
     */
    public function toArray()
    {
        $result = array();
        foreach($this->crawler as $node)
        {
            foreach ($node->attributes as $attr_name => $attr)
            {
                $result[$attr_name] = $attr->value;
            }
        }
        
        foreach ($this->crawler->filter('param') as $node)
        {
            foreach ($node->attributes as $attr_name => $attr)
            {
                $result['params'][$attr_name] = $attr->value;
            }
        }
        
        return $result;
    }

    /**
     *
     * @param array $params
     * @return string URI
     */
    protected function buildURI(array $params)
    {
        $query_separator = parse_url($this->crawler->attr('href'), PHP_URL_QUERY) === null ? '?' : '&';
        return $this->crawler->attr('href') . $query_separator . http_build_query($params, '', '&');
    }

    /**
     * 
     * @param \Bpi\Sdk\Document $document
     * @param array $params multidimensional arrays as well
     */
    public function send(Document $document, array $params)
    {
        $this->validate($params);
        $document->request('GET', $this->buildURI($params));
    }
}
