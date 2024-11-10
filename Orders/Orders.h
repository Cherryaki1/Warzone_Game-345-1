#ifndef ORDERS_H
#define ORDERS_H

#include <iostream>
#include <string>
#include <list>
#include <stdbool.h>
#include "LogObserver/LoggingObserver.h"

void testOrdersLists();

class Order : public Subject, public ILoggable {
public:
    // Constructors and Destructor
    Order(); 
    Order(const std::string& orderType);
    virtual ~Order();
    // Methods
    virtual bool validate() = 0;  // Pure virtual method
    virtual void execute() = 0;  // Pure virtual method
    std::string getOrderType() const;
    friend std::ostream& operator<<(std::ostream& os, const Order& order);
protected:
    std::string orderType;
    bool executed;
    string stringToLog() override;
};

class DeployOrder : public Order {
public:
    DeployOrder();
    void execute();
    bool validate();
};

class AdvanceOrder : public Order {
public:
    AdvanceOrder();
    void execute();
    bool validate();
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
