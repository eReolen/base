<?php

namespace Bpi\Sdk\Tests\WebService;

require_once __DIR__ . '/WebServiceTestCase.php';

class NodeWebServiceTest extends WebServiceTestCase
{
    public function testNodes()
    {
        $nodes = $this->client->searchNodes([]);
        $this->assertEquals(0, count($nodes));
    }

    public function testCanCreateNode()
    {
        $nodes = $this->client->searchNodes();
        $numberOfNodes = count($nodes);

        $data = [
            'title' => uniqid(__METHOD__),
        ];

        $node = $this->createNode($data);

        $this->assertEquals($data['title'], $node->getProperties()['title']);

        $nodes = $this->client->searchNodes();
        $newNumberOfNodes = count($nodes);

        $this->assertEquals($numberOfNodes + 1, $newNumberOfNodes);

        $nodes = $this->client->searchNodes(['search' => $data['title']]);
        $this->assertEquals(1, count($nodes));
        $nodes->rewind();
        $this->assertEquals($data['title'], $nodes->current()->getProperties()['title']);
    }

    public function testCanCreateNodeWithAssets()
    {
        $nodes = $this->client->searchNodes();
        $numberOfNodes = count($nodes);

        $data = [
            'title' => uniqid(__METHOD__),
            'category' => 'Test',
            'audience' => 'Test',

            'images' => [
                [
                    'path' => 'https://placekitten.com/200/400',
                    'alt' => 'Kittens',
                    'title' => 'Kittens',
                ],
                [
                    'path' => 'https://placekitten.com/400/200',
                    'alt' => 'Kittens',
                    'title' => 'Kittens',
                ],
            ],
        ];

        $node = $this->createNode($data);

        $nodes = $this->client->searchNodes();
        $newNumberOfNodes = count($nodes);

        $this->assertEquals($numberOfNodes + 1, $newNumberOfNodes);

        $this->assertEquals($data['title'], $node->getProperties()['title']);
        $this->assertEquals(2, count($node->getAssets()));
    }

    public function testCanLimitNodes()
    {
        $this->createNode();
        $this->createNode();

        $nodes = $this->client->searchNodes();
        $this->assertTrue(count($nodes) > 1);

        $nodes = $this->client->searchNodes([
            'amount' => 1,
        ]);

        $this->assertEquals(1, count($nodes));
    }

    public function testCanGetNode()
    {
        $data = [
            'title' => uniqid(__METHOD__),
        ];
        $newNode = $this->createNode($data);
        $this->assertNotEmpty($newNode->getProperties());
        $node = $this->client->getNode($newNode->getProperties()['id']);

        $this->assertEquals($data['title'], $node->getProperties()['title']);
        $this->assertEquals($newNode->getProperties()['title'], $node->getProperties()['title']);
    }

    public function testCanGetFacets()
    {
        $nodes = $this->client->searchNodes([]);
        $facets = $nodes->getFacets()->getFacets();

        $this->createNode(['category' => 'Book']);
        $this->createNode(['category' => 'Event']);
        $this->createNode(['category' => 'Film']);

        $newFacets = $nodes->getFacets()->getFacets();

        $this->assertEquals(count($facets), count($newFacets));
    }

    public function testCanFilterOnFacet()
    {
        $nodes = $this->client->searchNodes([]);
        $facets = $nodes->getFacets()->getFacets();

        if ($facets) {
            foreach ($facets as $facet) {
                $facetName = $facet->getFacetName();
                foreach ($facet->getFacetTerms() as $term) {
                    $nodes = $this->client->searchNodes([
                        'filter' => [
                            $facetName => [
                                $term->getName(),
                            ],
                        ]
                    ]);
                    $this->assertEquals($nodes->total, $term->getAmount(), $facetName . ': ' . $term->getName());
                }
            }
        }
    }

    public function testCanSyndicateNode()
    {
        // $node = $this->createNode();
        // $properties = $node->getProperties();
        // $actual = $this->client->syndicateNode($properties['id']);
        // $this->assertTrue($actual);
    }

    public function testCanDeleteNode()
    {
        $node = $this->createNode();

        $nodes = $this->client->searchNodes();
        $numberOfNodes = count($nodes);

        $result = $this->client->deleteNode($node->getProperties()['id']);

        $this->assertEquals(true, $result);

        $nodes = $this->client->searchNodes();
        $this->assertEquals($numberOfNodes - 1, count($nodes));
    }

    public function testCanSearchByText()
    {
        $nodes = $this->client->searchNodes([
            'search' => uniqid(__METHOD__),
        ]);

        $this->assertEquals(0, count($nodes));
    }

    public function testCanSortByTitle()
    {
        $this->canSortBy('title');
    }

    public function testCanSortByPushed()
    {
        $this->canSortBy('pushed');
    }

    public function testCanSortBySyndications()
    {
        $this->canSortBy('syndications');
    }

    public function testCanGetStatistics()
    {
        $statistics = $this->client->getStatistics('2000-01-01', '2100-01-01');
        $properties = $statistics->getProperties();

        $this->assertArrayHasKey('push', $properties);
        $this->assertArrayHasKey('syndicate', $properties);
    }

    public function testCanGetDictionaries()
    {
        $dictionaries = $this->client->getDictionaries();
        $this->assertTrue(is_array($dictionaries));
        $this->assertArrayHasKey('audience', $dictionaries);
        $this->assertArrayHasKey('category', $dictionaries);
    }

    private function canSortBy($name)
    {
        $nodes = $this->client->searchNodes([
            'sort' => [
                $name => 'asc',
            ],
        ]);
        $reversedNodes = $this->client->searchNodes([
            'sort' => [
                $name => 'desc',
            ],
        ]);

        $nodes = iterator_to_array($nodes);
        $reversedNodes = iterator_to_array($reversedNodes);

        $this->assertTrue(count($nodes) > 1);
        $this->assertTrue(count($reversedNodes) > 1);
        $this->assertEquals(count($nodes), count($reversedNodes));
        // $this->assertNotEquals($nodes, $reversedNodes);
    }

    private function createNode(array $data = [])
    {
        $data = array_merge([
            'title' => uniqid(__METHOD__),
            'body' => '',
            'teaser' => '',
            'type' => 'test',
            'creation' => date('c'),
            'category' => 'Other',
            'audience' => 'All',
            'editable' => 1,
            'authorship' => '',
            'agency_id' => $this->agencyId,
            'local_id' => 87,
            'firstname' => 'test',
            'lastname' => '',
            'assets' => [],
            'related_materials' => [],
            'tags' => 'test',
            'url' => '',
            'data' => '',
        ], $data);

        $node = $this->client->push($data);

        if (!$node) {
            throw new \Exception('Cannot create node');
        }

        return $node;
    }
}
