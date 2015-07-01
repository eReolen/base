<?php

use Behat\Behat\Tester\Exception\PendingException;
use Drupal\DrupalExtension\Context\RawDrupalContext;
use Behat\Behat\Context\SnippetAcceptingContext;
use Behat\Gherkin\Node\PyStringNode;
use Behat\Gherkin\Node\TableNode;

/**
 * Defines application features from the specific context.
 */
class FeatureContext extends RawDrupalContext implements SnippetAcceptingContext
{

    /**
     * Initializes context.
     *
     * Every scenario gets its own context instance.
     * You can also pass arbitrary arguments to the
     * context constructor through behat.yml.
     */
    public function __construct()
    {
    }

    /**
     * Find a specific cover on the page.
     *
     * @param string $id
     *   Ting id we're looking for.
     *
     * @return NodeElement
     *   The cover element.
     */
    protected function findCover($id) {
        $page  = $this->getSession()->getPage();
        $cover = $page->find('xpath', '//*[@data-ting-cover-object-id="' . $id . '"]');
        if (!$cover) {
            throw new \Exception(sprintf('Could not find cover for %s', $id));
        }

        return $cover;
    }

    /**
     * @Given /^I am looking at the (?P<type>material|collection) "(?P<id>[^"]+)"$/
     */
    public function iAmLookingAtTheMaterial($type, $id)
    {
        $this->visitPath('ting/' . ($type == 'collection' ? 'collection' : 'object'). '/' . $id);
    }

    /**
     * @Then I want to see a :type icon on the cover of :id
     */
    public function iWantToSeeAIconOnTheCoverOf($type, $id)
    {
        $typeMapping = [
            'free' => 'type-icon-noquota',
            'quota' => 'type-icon-quota',
        ];

        if (!in_array($type, array('free', 'quota'))) {
            throw new \Exception(sprintf('Unknown type icon type: %s', $type));
        }

        $cover = $this->findCover($id);

        if (!$cover->hasClass($typeMapping[$type])) {
            throw new \Exception(sprintf('Material %s does not have the right type icon.', $id));
        }

        // There shouldn't be any other type icon on the cover.
        foreach ($typeMapping as $name => $class) {
            if ($name != $type) {
                if ($cover->hasClass($class)) {
                    throw new \Exception(sprintf('Unexpected %s icon on material %s.', $name, $id));
                }
            }
        }
    }


    /**
     * @Given I search for :search_string
     */
    public function iSearchFor($search_string)
    {
        $this->visitPath('search/ting/' . $search_string);
    }

    /**
     * @Then I want to see no quota icon on the cover of :id
     */
    public function iWantToSeeNoQuotaIconOnTheCoverOf($id)
    {
        $cover = $this->findCover($id);

        if ($cover->hasClass('type-icon')) {
            throw new \Exception(sprintf('Unexpected cover icon on material %s.', $id));
        }
    }
}
