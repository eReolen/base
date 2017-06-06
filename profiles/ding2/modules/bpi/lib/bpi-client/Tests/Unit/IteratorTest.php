<?php
namespace Bpi\Sdk\Tests\Unit;

use Symfony\Component\DomCrawler\Crawler;
use Symfony\Component\BrowserKit\Response;
use Bpi\Sdk\Document;
use Bpi\Sdk\Authorization;
use Bpi\Sdk\Exception;

class IteratorTest extends \PHPUnit_Framework_TestCase
{
    protected function createMockDocument($fixture)
    {
        $client = $this->getMock('Goutte\Client');
        $client->expects($this->at(0))
              ->method('request')
              ->will($this->returnValue(new Crawler(file_get_contents(__DIR__ . '/Fixtures/' . $fixture . '.bpi'))));

        $client->expects($this->any())->method('getResponse')->will($this->returnValue(new Response()));

        $doc = new Document($client, new Authorization(mt_rand(), mt_rand(), mt_rand()));
        $doc->loadEndpoint('http://example.com');
        return $doc;
    }

    public function testIterateOverSingleEntity()
    {
        $doc = $this->createMockDocument('Node');
        
        $this->assertEquals(1, $doc->count());
        $this->assertTrue($doc->isTypeOf('entity'));
    }
    
    public function testIterateOverMultipleEntities()
    {
        $doc = $this->createMockDocument('Collection');
        
        $this->assertEquals(3, $doc->count());
        
        $i = 0;
        foreach ($doc as $item)
        {
            if ($i == 0)
                $this->assertTrue($item->isTypeOf('collection'));
            elseif ($i == 1 or $i == 2)
                $this->assertTrue($item->isTypeOf('entity'));
            else
                $this->fail('Unexpected');
            $i++;
        }
    }

    public function testReduceItemsByAttr()
    {
        $doc = $this->createMockDocument('Endpoint');
        $this->assertEquals(1, $doc->reduceItemsByAttr('name', 'node')->count(), 'One item with name=profile expected');

        try
        {
            $doc->reduceItemsByAttr('name', mt_rand());
            $this->fail('Exception expected trying reduce items by non existing attribute value');
        } catch (Exception\EmptyList $e) {
            $this->assertTrue(true);
        }

        try
        {
            $doc->reduceItemsByAttr(mt_rand(), 'node');
            $this->fail('Exception expected trying reduce items by non existing attribute');
        } catch (Exception\EmptyList $e) {
            $this->assertTrue(true);
        }
    }
}
