#ifndef ORDERS_H
#define ORDERS_H

#include <iostream>
#include <string>
#include <list>
#include <stdbool.h>
void testOrdersLists();

class Order {
public:
    Order();
    Order(const std::string& orderType);
    ~Order();

    bool validate();
    void execute();  // Base execute method

    std::string getOrderType() const;  // Getter for the order type

    friend std::ostream& operator<<(std::ostream& os, const Order& order);
protected:
    std::string orderType;
    bool executed;
};

class DeployOrder : public Order {
public:
    DeployOrder();
    void execute();
};

class AdvanceOrder : public Order {
public:
    AdvanceOrder();
    void execute();
};

class BombOrder : public Order {
public:
    BombOrder();
    void execute();
};

class BlockadeOrder : public Order {
public:
    BlockadeOrder();
    void execute();
};

class AirliftOrder : public Order {
public:
    AirliftOrder();
    void execute();
};

class NegotiateOrder : public Order {
public:
    NegotiateOrder();
    void execute();
};

class OrdersList {
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
};


#endif
