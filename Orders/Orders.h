#ifndef ORDERS_H
#define ORDERS_H

#include <iostream>
#include <string>
#include <list>
#include <stdbool.h>

class Order {
public:
    Order();
    Order(const std::string& orderType);
    ~Order();

    bool validate();
    void execute();

    friend std::ostream& operator<<(std::ostream& os, const Order& order);
protected:
    std::string orderType;
    bool executed;
};

class DeployOrder : public Order {
public:
    DeployOrder();
};

class AdvanceOrder : public Order {
public:
    AdvanceOrder();
};

class BombOrder : public Order {
public:
    BombOrder();
};

class BlockadeOrder : public Order {
public:
    BlockadeOrder();
};

class AirliftOrder : public Order {
public:
    AirliftOrder();
};

class NegotiateOrder : public Order {
public:
    NegotiateOrder();
};

class OrdersList {
private:
    std::list<Order*> orders;

public:
    OrdersList();
    ~OrdersList();
    
    void addOrder(Order* order);
    void move(int fromPosition, int toPosition); // Updated signature for move
    void remove(int position); // Updated signature for remove

    friend std::ostream& operator<<(std::ostream& os, const OrdersList& ordersList);
};

// Test function
void testOrdersList();

#endif
