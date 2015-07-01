Feature: Free materials
  In order to be able to loan more materials
  As a user
  I want to be able to find free materials

  Scenario: See if the viewed material is free.
    Given I am looking at the material "870970-basis:29302111"
    Then I want to see a "free" icon on the cover of "870970-basis:29302111"

  Scenario: See if the viewed material is on quota.
    Given I am looking at the material "870970-basis:51665023"
    Then I want to see a "quota" icon on the cover of "870970-basis:51665023"

  Scenario: Whether the materials on a collection is free.
    Given I am looking at the collection "870970-basis:51436423"
    Then I want to see a "free" icon on the cover of "870970-basis:51436423"
    And I want to see a "free" icon on the cover of "870970-basis:28455410"

  Scenario: Quota icons on search results.
    Given I search for "tågens folk"
    Then I want to see a "quota" icon on the cover of "870970-basis:28684282"
    
  Scenario: No quota icons on collection search results with multiple materials.
    Given I search for "kampen om palanthas"
    Then I want to see no quota icon on the cover of "870970-basis:51436423"
    
