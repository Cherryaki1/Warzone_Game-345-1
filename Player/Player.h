#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include "Map/Map.h"
#include "Cards/Cards.h"
#include "Orders/Orders.h"


class Orderslist;
class Territory;
class Hand;
class Map;
class Order;

class Player {
private:
        Hand* playerHand;
        Orderslist* ordersList;
        std::string* playerName;
public:
        Player();
        Player(std::string name);
        Player(const Player& other);       // Copy constructor
        Player& operator=(const Player& other); // Assignment operator
        ~Player();

        void setPlayerName(std::string name);
        std::string getPlayerName() const;

        void toDefend();
        void toAttack();
        void issueOrder();

        friend std::ostream& operator<<(std::ostream& os, const Player& player); // Stream insertion operator

};

void testPlayers();


#endif
