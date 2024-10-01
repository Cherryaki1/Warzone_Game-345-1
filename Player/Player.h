#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include "Map/Map.h"
#include "Cards/Cards.h"
#include "Orders/Orders.h"

using namespace std;

class Orderslist;
class Territory;
class Map;
class Order;

class Player {
private:
        //Hand* playerHand;
        Orderslist* ordersList;
        string playerName;
public:
        Player();
        Player(string name);

        void toDefend();
        void toAttack();
        void issueOrder();
};
#endif
