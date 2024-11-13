// Arturo Sanchez Escobar (40283236), Team 36
// COMP 345 - D (Advanced Program Design, C++)
// Warzone Game Team Project - Assignment 1
// October 4, 2024
// *******************************************
// This is a cpp file for Part 5 of the assignment.
// It contains the logic the Game Engine follows, to move from one state to another, loop and end

# include <iostream>
# include "GameEngine.h"
using namespace std;



void testStartUpPhase() {
    GameEngine engine;
    engine.startUpPhase();
}

void testMainGameLoop() {
    // Call the main game loop here
    GameEngine engine;
    engine.startUpPhase();
    engine.mainGameLoop();
}

void testOrderExecution() {
    // Create players
    Player* player1 = new Player("Player1");
    Player* player2 = new Player("Player2");

    // Create territories
    Territory* territory1 = new Territory("Territory1", player1->getPlayerName(), "Continent1", 10);
    Territory* territory2 = new Territory("Territory2", player2->getPlayerName(), "Continent1", 5);
    Territory* territory3 = new Territory("Territory3", player1->getPlayerName(), "Continent1", 8);

    // Set adjacent territories
    territory1->adjacentTerritories.push_back(territory2);
    territory2->adjacentTerritories.push_back(territory1);
    territory2->adjacentTerritories.push_back(territory3);
    territory3->adjacentTerritories.push_back(territory2);

    // Add territories to players
    player1->addOwnedTerritory(territory1);
    player1->addOwnedTerritory(territory3);
    player2->addOwnedTerritory(territory2);

    // Create a deck
    Deck* deck = new Deck();
    deck->initialize();

    // Assign hands to players
    player1->getHand()->place(deck->draw());
    player2->getHand()->place(deck->draw());

    // Test Deploy Order
    DeployOrder deployOrder(player1, territory1, 5);
    deployOrder.execute();

    // Test Advance Order
    AdvanceOrder advanceOrder(player1, territory1, territory2, 5);
    advanceOrder.execute();
    cout << "Owner of " << territory2->getName() << " after attack: " << territory2->getOwner() << endl;

    // Test Bomb Order
    BombOrder bombOrder(player1, territory2);
    bombOrder.execute();

    // Test Blockade Order
    BlockadeOrder blockadeOrder(player1, territory1);
    blockadeOrder.execute();
    cout << "Owner of " << territory1->getName() << " after blockade: " << territory1->getOwner() << endl;

    // Test Airlift Order
    AirliftOrder airliftOrder(player1, territory1, territory3, 3);
    airliftOrder.execute();

    // Test Negotiate Order
    NegotiateOrder negotiateOrder(player1, player2);
    negotiateOrder.execute();

    // Attempt to attack after negotiation
    AdvanceOrder advanceOrderAfterNegotiate(player1, territory3, territory2, 3);
    advanceOrderAfterNegotiate.execute();

    // Clean up
    delete player1;
    delete player2;
    delete territory1;
    delete territory2;
    delete territory3;
    delete deck;
}

void testGameStates() {
    GameEngine gameEngine;
//    if(gameEngine.startUpPhase("../DownloadedMaps/Europe 4B.map")) {
        cout << "Game Engine StartUpPhase Completed, proceeding to Reinforcement Phase" << std::endl;
        if(gameEngine.reinforcementPhase()) {
            cout << "Reinforcement Phase Completed, proceeding to Orders Execution" << endl;
            if(gameEngine.ordersIssuingPhase()) {
                cout << "Orders Issuing Phase Completed, proceeding to Orders Execution" << endl;
                if(gameEngine.ordersExecutionPhase() == "endexecorders") {
                    cout << "Orders Execution Phase Completed, checking End Phase" << endl;
                    testGameStates();
                }else {
                    if(gameEngine.endPhase()) {
                        cout << "Congratulations, a player has won!" << endl;
                        cout << "Thank you for playing!" << endl;
                    }else {
                        cout << "The win conditions have not been met yet!" << endl;
                        testGameStates();
                    }

                }
            }
        }
    }




//}