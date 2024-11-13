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

    cout << "Creating Player3" << endl;
    Player* player3 = new Player("Player3");

    cout << "Creating Player4" << endl;
    Player* player4 = new Player("Player4");

    // Create territories with no armies
    cout << "Creating Territory1 (in Continent1) with no armies and belongs to Player1" << endl;
    Territory* territory1 = new Territory("Territory1", player1->getPlayerName(), "Continent1", 0);
    
    cout << "Creating Territory2 (in Continent1) with no armies and belongs to Player1" << endl;
    Territory* territory2 = new Territory("Territory2", player1->getPlayerName(), "Continent1", 0);

    cout << "Creating Territory3 (in Continent2) with no armies and belongs to Player2" << endl;
    Territory* territory3 = new Territory("Territory3", player2->getPlayerName(), "Continent2", 0);

    cout << "Creating Territory4 (in Continent2) with no armies and belongs to Player2" << endl;
    Territory* territory4 = new Territory("Territory4", player2->getPlayerName(), "Continent2", 0);

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
    cout << "DeployOrder:" << endl;
    cout << "Adding 5 troops to Player1's reinforcement pool..." << endl;
    player1->setReinforcementPool(5);
    cout << "1. If the target territory does not belong to the player that issued the order, the order is invalid." << endl;
    cout << "Deploying the 5 troops of Player1 to Territory3..." << endl;
    DeployOrder* deployOrder1 = new DeployOrder(player1, territory3, 5);
    deployOrder1->execute();
    cout << "Troop count on Territory1: " << territory1->getNumberOfArmies() << endl;

    cout << "2. If the target territory belongs to the player that issued the deploy order, the selected number of army units is added to the number of army units on that territory." << endl; 
    cout << "Deploying the 5 troops of Player1 Territory1..." << endl;
    DeployOrder* deployOrder2 = new DeployOrder(player1, territory1, 5);
    deployOrder2->execute();
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
    cout << "Troop count on Territory 2: " << territory2->getNumberOfArmies() << endl;
    AdvanceOrder* advanceOrder3 = new AdvanceOrder(player1, territory1, territory2, 5);
    advanceOrder3->execute();
    cout << "4. If the target territory belongs to another player than the player that issued the advance order, an attack is simulated when the order is executed." << endl;
    cout << "Adding 5 troops to Territory4 (adjacent but owned by Player2)..." << endl;
    territory4->setNumberOfArmies(5);
    cout << "Player1 trying to advance 5 troops from Territory1 to Territory4..." << endl;
    AdvanceOrder* advanceOrder4 = new AdvanceOrder(player1, territory1, territory4, 5);
    advanceOrder4->execute();

    cout << "\n" << endl;
    cout << "BombOrder:" << endl;
    cout << "1. If the target belongs to the player that issued the order, the order is invalid." << endl;
    cout << "Player1 trying to bomb Territory1..." << endl;
    BombOrder* bombOrder1 = new BombOrder(player1, territory1);
    bombOrder1->execute();
    cout << "2. If the target territory is not adjacent to one of the territories owned by the player that issued the order, the order is invalid." << endl;
    cout << "Temporarly disconnecting Territory1 from Territory4..." << endl;
    territory1->adjacentTerritories.pop_back();
    territory4->adjacentTerritories.pop_back();
    cout << "Player1 trying to bomb Territory3..." << endl;
    BombOrder* bombOrder2 = new BombOrder(player1, territory3);
    bombOrder2->execute();
    cout << "Reconnecting Territory1 to Territory4..." << endl;
    territory1->adjacentTerritories.push_back(territory4);
    territory4->adjacentTerritories.push_back(territory1);
    cout << "3. If the order is valid, half of the army units are removed from this territory." << endl;
    cout << "Setting Territory4 troop size to 10..." << endl;
    territory4->setNumberOfArmies(10);
    cout << "Player1 trying to bomb Territory4..." << endl;
    BombOrder* bombOrder3 = new BombOrder(player1, territory4);
    bombOrder3->execute();

    cout << "\n" << endl;
 

    // // Clean up
    // delete player1;
    // delete player2;
    // delete territory1;
    // delete territory2;
    // delete territory3;
    // delete deck;


}
