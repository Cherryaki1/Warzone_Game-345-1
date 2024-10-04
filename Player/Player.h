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
#include "Cards/Cards.h"
#include "Orders/Orders.h"

#include <string>
#include <vector>

using std::string;
using std::vector;


class Player {
private:
    Hand* playerHand;
    OrdersList* ordersList;
    string* playerName;
public:
    Player();
    Player(string name);
    Player(const Player& other);       // Copy constructor
    Player& operator=(const Player& other); // Assignment operator
    ~Player();

    void setPlayerName(string name);
    string getPlayerName() const;

    void toDefend();
    void toAttack();
    void issueOrder(const std::string& orderType);

    friend std::ostream& operator<<(std::ostream& os, const Player& player); // Stream insertion operator

};

void testPlayers();


#endif
