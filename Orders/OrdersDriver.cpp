#include <iostream>
#include "Orders.h"
#include "Player/Player.h"
#include "Map/Map.h"
#include "Cards/Cards.h"
#include "GameEngine/GameEngine.h"

using namespace std;

void testOrderExecution() {
    // Create players
    cout << "Creating Player1" << endl;
    Player* player1 = new Player("Player1");

    cout << "Creating Player2" << endl;
    Player* player2 = new Player("Player2");

    // Create territories with no armies
    cout << "Creating Territory1 (in Continent1) with no armies and belongs to Player1" << endl;
    Territory* territory1 = new Territory("Territory1", player1, "Continent1", 0);
    
    cout << "Creating Territory2 (in Continent1) with no armies and belongs to Player1" << endl;
    Territory* territory2 = new Territory("Territory2", player1, "Continent1", 0);

    cout << "Creating Territory3 (in Continent2) with no armies and belongs to Player2" << endl;
    Territory* territory3 = new Territory("Territory3", player2, "Continent2", 0);

    cout << "Creating Territory4 (in Continent2) with no armies and belongs to Player2" << endl;
    Territory* territory4 = new Territory("Territory4", player2, "Continent2", 0);

    // Set adjacent territories
    cout << "Setting Territory1 adjacent to Territory2" << endl;
    territory1->adjacentTerritories.push_back(territory2);
    territory2->adjacentTerritories.push_back(territory1);

    cout << "Setting Territory2 adjacent to Territory3" << endl;
    territory2->adjacentTerritories.push_back(territory3);
    territory3->adjacentTerritories.push_back(territory2);

    cout << "Setting Territory3 adjacent to Territory4" << endl;
    territory3->adjacentTerritories.push_back(territory4);
    territory4->adjacentTerritories.push_back(territory3);

    cout << "Setting Territory4 adjacent to Territory1" << endl;
    territory4->adjacentTerritories.push_back(territory1);
    territory1->adjacentTerritories.push_back(territory4);

    // Create a deck
    cout << "Creating a deck" << endl;
    Deck* deck = new Deck();
    deck->initialize();

    cout << "\n" << endl;
    cout << "Demonstractions:" << endl;
    cout << "\n" << endl;
    cout << "(1) each order is validated before being executed according to the above description." << endl;
    cout << "\n" << endl;
    cout << "DeployOrder:" << endl;
    cout << "Adding 5 troops to Player1's reinforcement pool..." << endl;
    player1->setReinforcementPool(5);
    cout << "1. If the target territory does not belong to the player that issued the order, the order is invalid." << endl;
    cout << "Deploying the 5 troops of Player1 to Territory3..." << endl;
    DeployOrder* deployOrder1 = new DeployOrder(player1, territory3, 5);
    deployOrder1->execute();
    cout << "2. If the target territory belongs to the player that issued the deploy order, the selected number of army units is added to the number of army units on that territory." << endl; 
    cout << "Deploying the 5 troops of Player1 Territory1..." << endl;
    DeployOrder* deployOrder2 = new DeployOrder(player1, territory1, 5);
    deployOrder2->execute();
    cout << "Troop count on territory1: " << territory1->getNumberOfArmies() << endl;

    cout << "\n" << endl;
    cout << "AdvanceOrder:" << endl;
    cout << "1. If the source territory does not belong to the player that issued the order, the order is invalid." << endl;
    cout << "Player1 trying to advance 5 troops from Territory3 to Territory2..." << endl;
    AdvanceOrder* advanceOrder1 = new AdvanceOrder(player1, territory3, territory2, 5);
    advanceOrder1->execute();
    cout << "2. If the target territory is not adjacent to the source territory, the order is invalid" << endl;
    cout << "Player1 trying to advance 5 troops from Territory1 to Territory3..." << endl;
    AdvanceOrder* advanceOrder2 = new AdvanceOrder(player1, territory1, territory3, 5);
    advanceOrder2->execute();
    cout << "3. If the source and target territory both belong to the player that issued the order, the army units are moved from the source to the target territory." << endl;
    cout << "Player1 trying to advance 5 troops from Territory1 to Territory2..." << endl;
    cout << "Troop count on Territory 2 before: " << territory2->getNumberOfArmies() << endl;
    AdvanceOrder* advanceOrder3 = new AdvanceOrder(player1, territory1, territory2, 5);
    advanceOrder3->execute();
    cout << "Troop count on Territory 2 after: " << territory2->getNumberOfArmies() << endl;
    cout << "(2) ownership of a territory is transferred to the attacking player if a territory is conquered as a result of an advance order;" << endl;
    cout << "(3) one card is given to a player if they conquer at least one territory in a turn" << endl;
    cout << "4. If the target territory belongs to another player than the player that issued the advance order, an attack is simulated when the order is executed." << endl;
    cout << "Player1 trying to advance 5 troops from Territory1 to Territory4... (Terrotiry4 has no troops, Player1 should win)" << endl;
    AdvanceOrder* advanceOrder4 = new AdvanceOrder(player1, territory1, territory4, 5);
    advanceOrder4->execute();
    cout << "Territory4 owner after attack: " << territory4->getOwner() << endl;

    cout << "\n" << endl;
    cout << "BombOrder:" << endl;
    cout << "1. If the target belongs to the player that issued the order, the order is invalid." << endl;
    cout << "Player1 trying to bomb Territory1..." << endl;
    BombOrder* bombOrder1 = new BombOrder(player1, territory1);
    bombOrder1->execute();
    cout << "2. If the order is valid, half of the army units are removed from this territory." << endl;
    cout << "Setting Territory3 troop size to 10..." << endl;
    territory3->setNumberOfArmies(10);
    cout << "Player1 trying to bomb Territory3..." << endl;
    cout << "Territory3 troop count before bomb: " << territory3->getNumberOfArmies() << endl;
    player1->addOwnedTerritory(territory1);
    player1->addOwnedTerritory(territory2);
    BombOrder* bombOrder3 = new BombOrder(player1, territory3);
    bombOrder3->execute();
    cout << "Territory3 troop count after bomb: " << territory3->getNumberOfArmies() << endl;
    cout << "3. If the target territory is not adjacent to one of the territories owned by the player that issued the order, the order is invalid." << endl;
    cout << "Disconnecting Territory1 from Territory4..." << endl;
    territory1->adjacentTerritories.pop_back();
    territory4->adjacentTerritories.pop_back();
    cout << "Player1 trying to bomb Territory3..." << endl;
    BombOrder* bombOrder2 = new BombOrder(player1, territory3);
    bombOrder2->execute();

    cout << "\n" << endl;
    cout << "BlockadeOrder:" << endl;
    cout << "1. If the target territory does not belong to the player that issued the order, the order is invalid." << endl;
    cout << "Player1 trying to blockade Territory3..." << endl;
    BlockadeOrder* blockadeOrder1 = new BlockadeOrder(player1, territory3);
    blockadeOrder1->execute();
    cout << "(5) the blockade order transfers ownership to the Neutral player" << endl;
    cout << "2. If the order is valid, the number of army units on the target territory is doubled and the territory is set to neutral." << endl;
    cout << "Setting troops of Territory1 to 5..." << endl;
    territory1->setNumberOfArmies(5);
    cout << "Player1 trying to blockade Territory1..." << endl;
    BlockadeOrder* blockadeOrder2 = new BlockadeOrder(player1, territory1);
    blockadeOrder2->execute();
    cout << "Troop count on Territory1: " << territory1->getNumberOfArmies() << endl;
    cout << "Owner of Territory1: " << territory1->getOwner() << endl;

    cout << "\n" << endl;
    cout << "AirliftOrder:" << endl;
//    territory1->setOwner("player1");
    cout << "1. If the source territory does not belong to the player that issued the order, the order is invalid." << endl;
    cout << "Player1 trying to airlift 5 troops from Territory3 to Territory2..." << endl;
    AirliftOrder* airliftOrder1 = new AirliftOrder(player1, territory3, territory2, 5);
    airliftOrder1->execute();
    cout << "2. If both the source and target territories belong to the player that issue the airlift order, then the selected number of army units is moved from the source to the target territory" << endl;
    cout << "Player1 trying to airlift 5 troops from Territory1 to Territory2..." << endl;
    cout << "Troop count on Territory2: " << territory2->getNumberOfArmies() << endl;
    AirliftOrder* airliftOrder2 = new AirliftOrder(player1, territory1, territory2, 5);
    airliftOrder2->execute();
    cout << "Troop count on Territory2 after Airlift: " << territory2->getNumberOfArmies() << endl;

    cout << "\n" << endl;
    cout << "NegotiateOrder:" << endl;
    cout << "1. If the target is the player issuing the order, then the order is invalid." << endl;
    cout << "Player1 trying to negotiate with themselves..." << endl;
    NegotiateOrder* negotiateOrder1 = new NegotiateOrder(player1, player1);
    negotiateOrder1->execute();
    cout << "(4) the negotiate order attacks between the two players involved" << endl;
    cout << "2. If the order is valid, then a truce is established between the two players." << endl;
    cout << "Player1 trying to negotiate with Player2..." << endl;
    NegotiateOrder* negotiateOrder2 = new NegotiateOrder(player1, player2);
    negotiateOrder2->execute();
    cout << "Player1 trying to advance 5 troops from Territory2 to Territory3..." << endl;
    AdvanceOrder* advanceOrder5 = new AdvanceOrder(player1, territory2, territory3, 5);
    advanceOrder5->execute();

    // Clean up
    // delete player1;
    // delete player2;
    // delete territory1;
    // delete territory2;
    // delete territory3;
    // delete territory4;
    // delete deck;


}
