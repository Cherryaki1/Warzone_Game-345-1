// Abdulah Ghulam Ali (40281857), Team 36
// COMP 345 - D (Advanced Program Design, C++)
// Warzone Game Team Project - Assignment 1
// October 4, 2024
// *******************************************
// This is a header file for Part 2 of the assignment.
// It contains the class and function signatures/declarations for Player

#ifndef PLAYER_H
#define PLAYER_H

#include "Map/Map.h"
#include "Orders/Orders.h"
#include "PlayerStrategies/PlayerStrategies.h"
#include <string>
#include <vector>
class Hand;
class OrdersList;
class GameEngine;
using std::string;
using std::vector;

class PlayerStrategy;

class Player {
private:
    static int numOfPlayers;
    int* armies;
    vector<Territory*> ownedTerritories;
    Hand* playerHand;
    OrdersList* ordersList;
    string* playerName;
    int reinforcementPool = 0;
    vector<string> trucePlayers;
    PlayerStrategy* strategy;
    GameEngine* pEngine;
public:
    //Default constructor
    Player();

    //Parameterized constructors
    Player(string name, GameEngine* engine);
    Player(Hand* initialHand, vector<Territory *> &initialTerritories, string name);
    explicit Player(string name); //DEPRACATED DO NOT USE ANYMORE
    // Copy constructor
    Player(const Player& other);

    // Assignment operator
    Player& operator=(const Player& other);

    //Destructor
    ~Player();

    vector<Territory *> getOwnedTerritories() const;
    void addOwnedTerritory(Territory *territory);
    Territory *removeOwnedTerritory(const Territory *territory);

    Hand* getHand() const;

    OrdersList* getOrdersList() const;

    void setArmies(int* armies);
    int getArmies() const;

    void setPlayerName(string name);
    string getPlayerName() const;

    int getReinforcementPool();
    void setReinforcementPool(int numUnits);

    bool hasCard(string cardType);

    vector<Territory*> toDefend();
    vector<Territory*> toAttack();

    void issueOrder(Order* newOrder);
    void issueOrder();

    void addTrucePlayer(const string& playerName);
    void clearTrucePlayers();
    bool hasTruceWith(const string& playerName) const;

    GameEngine* getCurrentGameEngine();

    void setStrategy(string strat);
    string getStrategyType();
    void addToOrderList(Order* o);
    //Stream insertion operator
    friend std::ostream& operator<<(std::ostream& os, const Player& player);

};

void testPlayers();


#endif

