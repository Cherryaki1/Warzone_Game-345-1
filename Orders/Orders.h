#ifndef ORDERS_H
#define ORDERS_H

#include <iostream>
#include <string>
#include <list>
#include <stdbool.h>
#include "LogObserver/LoggingObserver.h"
#include "Player/Player.h"
#include "Map/Map.h"


void testOrdersLists();


// ----------------------------------------------------------
//                        Order class
// ----------------------------------------------------------
class Order : public Subject, public ILoggable {
    public:
        // Constructors and Destructor
        Order() = default; 
        virtual ~Order() = default;
        Order(const std::string& orderType);

        // Methods
        bool validate();
        virtual void execute() = 0; // Pure virtual method
        std::string getOrderType() const;
        friend std::ostream& operator<<(std::ostream& os, const Order& order);

protected:
    std::string orderType;
    bool executed;
    string stringToLog() override;
};

// ----------------------------------------------------------
//                    Derived Order classes
// ----------------------------------------------------------
class DeployOrder : public Order {
private:
    Player* player;
    Territory* targetTerritory;
    int numUnits;

public:
    DeployOrder(Player* player, Territory* target, int units) : player(player), targetTerritory(target), numUnits(units) {}
    void execute() override;
};


class AdvanceOrder : public Order {
private:
    Player* player;
    Territory* sourceTerritory;
    Territory* targetTerritory;
    int numUnits;

public:
    AdvanceOrder(Player* player, Territory* source, Territory* target, int units) : player(player), sourceTerritory(source), targetTerritory(target), numUnits(units) {}
    void execute() override;
};



class BombOrder : public Order {
private:
    Player* player;
    Territory* targetTerritory;

public:
    BombOrder(Player* player, Territory* target) : player(player), targetTerritory(target) {}
    void execute() override;
};


class BlockadeOrder : public Order {
private:
    Player* player;
    Territory* targetTerritory;

public:
    BlockadeOrder(Player* player, Territory* target) : player(player), targetTerritory(target) {}
    void execute() override;
};


class AirliftOrder : public Order {
private:
    Player* player;
    Territory* sourceTerritory;
    Territory* targetTerritory;
    int numUnits;

public:
    AirliftOrder(Player* player, Territory* source, Territory* target, int units) : player(player), sourceTerritory(source), targetTerritory(target), numUnits(units) {}
    void execute() override;
};


class NegotiateOrder : public Order {
private:
    Player* player;
    Player* targetPlayer;

public:
    NegotiateOrder(Player* player, Player* target) : player(player), targetPlayer(target) {}
    void execute() override;
};

// ----------------------------------------------------------
//                        OrdersList class
// ----------------------------------------------------------
class OrdersList : public Subject, public ILoggable{
private:
    std::list<Order*> orders;

public:
    OrdersList();
    ~OrdersList();

    void addOrder(Order* order);
    void move(int fromPosition, int toPosition);
    void remove(int position);
    bool isEmpty();

    std::list<Order*>& getOrders();

    friend std::ostream& operator<<(std::ostream& os, const OrdersList& ordersList);

    string stringToLog() override;
};


#endif // ORDERS_H
