<?php
namespace Bpi\Sdk\Tests\Unit;

use Symfony\Component\DomCrawler\Crawler;
use Symfony\Component\BrowserKit\Response;
use Bpi\Sdk\Document;
use Bpi\Sdk\Authorization;

class HypermediaEngineTest extends \PHPUnit_Framework_TestCase
{
    protected function createMockClient($fixture = 'Node')
    {
        $client = $this->getMock('Goutte\Client');
        $client->expects($this->at(0))
              ->method('request')
              ->with($this->equalTo('GET'), $this->equalTo('http://example.com'))
              ->will($this->returnValue(new Crawler(file_get_contents(__DIR__ . '/Fixtures/' . $fixture . '.bpi'))));

        $client->expects($this->any())->method('getResponse')->will($this->returnValue(new Response()));

        return $client;
    }

    protected function createDocument($client)
    {
        return new Document($client, new Authorization(mt_rand(), mt_rand(), mt_rand()));
    }

    public function testLink()
    {
        $client = $this->createMockClient();
        $doc = $this->createDocument($client);
        $doc->loadEndpoint('http://example.com');

        $properties = $doc->link('collection')->toArray();
        $this->assertEquals('collection', $properties['rel']);
        $this->assertEquals('http://example.com/collection', $properties['href']);
        $this->assertEquals('Collection', $properties['title']);
    }

    public function testUndefinedHypermediaAccess()
    {
        $client = $this->createMockClient();
        $doc = $this->createDocument($client);
        $doc->loadEndpoint('http://example.com');

        try {
            $doc->link(mt_rand());
            $this->fail('Undefined link exception expected');
        }
        catch(\Bpi\Sdk\Exception\UndefinedHypermedia $e) {
            $this->assertTrue(true);
        }

        try {
            $doc->query(mt_rand());
            $this->fail('Undefined query exception expected');
        }
        catch(\Bpi\Sdk\Exception\UndefinedHypermedia $e) {
            $this->assertTrue(true);
        }

        try {
            $doc->template(mt_rand());
            $this->fail('Undefined template exception expected');
        }
        catch(\Bpi\Sdk\Exception\UndefinedHypermedia $e) {
            $this->assertTrue(true);
        }
    }

    public function testFollowLink()
    {
        $client = $this->createMockClient();
        
        $client->expects($this->at(2))
              ->method('request')
              ->with($this->equalTo('GET'), $this->equalTo('http://example.com/collection'))
              ->will($this->returnValue(new Crawler('<?xml version="1.0" encoding="UTF-8"?><bpi version="0.1"><item type="entity" name="foo"/></bpi>')));

        $doc = $this->createDocument($client);
        $doc->loadEndpoint('http://example.com')
            ->link('collection')
            ->follow($doc);

        $this->assertEquals(1, $doc->firstItem('name', 'foo')->count(), 'Expected foo tag in response');
    }
    
    public function testQuery()
    {
        $client = $this->createMockClient();
        $doc = $this->createDocument($client);
        $doc->loadEndpoint('http://example.com');
        $dump = $doc->query('search')->toArray();
        $this->assertEquals('search', $dump['rel']);
        $this->assertEquals('http://example.com/search', $dump['href']);
        $this->assertEquals('Search', $dump['title']);
        $this->assertEquals('id', $dump['params']['name']);
    }
    
    public function testSendQuery()
    {
        $client = $this->createMockClient();
        $client->expects($this->at(2))
              ->method('request')
              ->with($this->equalTo('GET'), $this->equalTo('http://example.com/search?id=foo'))
              ->will($this->returnValue(new Crawler(file_get_contents(__DIR__ . '/Fixtures/Node.bpi'))));

        $doc = $this->createDocument($client);
        $doc->loadEndpoint('http://example.com');
        $doc->sendQuery($doc->query('search'), array('id' => 'foo'));
    }
    
    /**
     * @expectedException \Bpi\Sdk\Exception\InvalidQueryParameter
     */
    public function testSendQuery_WithInvalidParameter()
    {
        $client = $this->createMockClient();
        $doc = $this->createDocument($client);
        $doc->loadEndpoint('http://example.com');
        $doc->sendQuery($doc->query('search'), array('id' => 'foo', 'zoo' => 'foo'));
    }

    public function testSendQuery_WithMultipleValues()
    {
        $client = $this->createMockClient('Collection');
        $client->expects($this->at(2))
              ->method('request')
              ->with($this->equalTo('GET'), $this->equalTo('http://example.com/collection?filter%5Btitle%5D=foo&filter%5Bbody%5D=zoo'))
              ->will($this->returnValue(new Crawler(file_get_contents(__DIR__ . '/Fixtures/Node.bpi'))));

        $doc = $this->createDocument($client);
        $doc->loadEndpoint('http://example.com');
        $doc->sendQuery($doc->query('filter'), array('filter' => array('title' => 'foo', 'body' => 'zoo')));
    }

    public function testSendQuery_WithMultipleValues_Exceptions()
    {
        $client = $this->createMockClient('Collection');
        $doc = $this->createDocument($client);
        $doc->loadEndpoint('http://example.com');

        try
        {
            $doc->sendQuery($doc->query('filter'), array('filter' => 'flat_value'));
            $this->fail('Exception expected');
        }
        catch(\Bpi\Sdk\Exception\InvalidQueryParameter $e)
        {
            $this->assertTrue(true);
        }

        try
        {
            $doc->sendQuery($doc->query('search'), array('id' => array(1)));
            $this->fail('Exception expected');
        }
        catch(\Bpi\Sdk\Exception\InvalidQueryParameter $e)
        {
            $this->assertTrue(true);
        }
    }

    public function testTemplate()
    {
        $client = $this->createMockClient();
        $doc = $this->createDocument($client);
        $doc->loadEndpoint('http://example.com');
        $self = $this;
        $doc->template('push')->eachField(function($field) use($self) {
            $self->assertNotEmpty((string) $field);
        });
    }

    public function testPostTemplate()
    {
        $client = $this->createMockClient();
        $post_data = array('title' => 'title_a', 'teaser' => 'teaser_a', 'body' => 'body_a', 'type' => 'article');
        $client->expects($this->at(2))
              ->method('request')
              ->with($this->equalTo('POST'), $this->equalTo('http://example.com/node'), $this->equalTo($post_data))
              ->will($this->returnValue(new Crawler(file_get_contents(__DIR__ . '/Fixtures/Node.bpi'))));

        $doc = $this->createDocument($client);
        $doc->loadEndpoint('http://example.com');
        $doc->template('push')->eachField(function($field) use($post_data) {
              $field->setValue($post_data[(string) $field]);
        })->post($doc);
    }
}
