#ifndef ORDERS_H
#define ORDERS_H

#include <iostream>
#include <string>
#include <list>
#include <stdbool.h>
#include "LogObserver/LoggingObserver.h"
#include "Map/Map.h"
class Player;


void testOrdersLists();


// ----------------------------------------------------------
//                        Order class
// ----------------------------------------------------------
class Order : public Subject, public ILoggable {
    public:
        // Constructors and Destructor
        Order();
        virtual ~Order() = default;
        Order(const std::string& orderType);

        // Methods
        bool validate();
        virtual void execute() = 0; // Pure virtual method
        std::string getOrderType() const;
        friend std::ostream& operator<<(std::ostream& os, const Order& order);

    private:
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
    bool executed;
    int numUnits;

public:
    DeployOrder()=default;
    DeployOrder(Player* player, Territory* target, int units) : player(player), targetTerritory(target), numUnits(units), Order("Deploy") {}
    void execute() override;
};


class AdvanceOrder : public Order {
private:
    Player* player;
    Territory* sourceTerritory;
    Territory* targetTerritory;
    int numUnits;
    bool executed;

public:
    AdvanceOrder() = default;
    AdvanceOrder(Player* player, Territory* source, Territory* target, int units) : player(player), sourceTerritory(source), targetTerritory(target), numUnits(units), Order("Advance") {}
    void execute() override;
};



class BombOrder : public Order {
private:
    Player* player;
    Territory* targetTerritory;
    bool executed;

public:
    BombOrder() = default;
    BombOrder(Player* player, Territory* target) : player(player), targetTerritory(target), Order("Bomb") {}
    void execute() override;
};


class BlockadeOrder : public Order {
private:
    Player* player;
    Territory* targetTerritory;
    bool executed;

public:
    BlockadeOrder() = default;
    BlockadeOrder(Player* player, Territory* target) : player(player), targetTerritory(target), Order("Blockade") {}
    void execute() override;
};


class AirliftOrder : public Order {
private:
    Player* player;
    Territory* sourceTerritory;
    Territory* targetTerritory;
    int numUnits;
    bool executed;

public:
    AirliftOrder() = default;
    AirliftOrder(Player* player, Territory* source, Territory* target, int units) : player(player), sourceTerritory(source), targetTerritory(target), numUnits(units), Order("Airlift") {}
    void execute() override;
};


class NegotiateOrder : public Order {
private:
    Player* player;
    Player* targetPlayer;
    bool executed;

public:
    NegotiateOrder() = default;
    NegotiateOrder(Player* player, Player* target) : player(player), targetPlayer(target), Order("Negotiate") {}
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

    // get next order on the list
    Order *getNextOrder();

    std::list<Order*>& getOrders();

    friend std::ostream& operator<<(std::ostream& os, const OrdersList& ordersList);

    string stringToLog() override;
};


#endif // ORDERS_H
