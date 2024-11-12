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

#include <string>
#include <vector>
class Hand;
class OrdersList;
using std::string;
using std::vector;


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

public:
    //Default constructor
    Player();

    //Parameterized constructors
    Player(string name);
    Player(Hand* initialHand, vector<Territory *> &initialTerritories, string name);

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

    void addTrucePlayer(const string& playerName);
    void clearTrucePlayers();
    bool hasTruceWith(const string& playerName) const;

    void issueOrder(Order* newOrder);


    //Stream insertion operator
    friend std::ostream& operator<<(std::ostream& os, const Player& player);

};

void testPlayers();


#endif

