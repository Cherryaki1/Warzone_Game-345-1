#ifndef ORDERS_H
#define ORDERS_H

#include <iostream>
#include <string>
#include <list>
#include <stdbool.h>
#include "Cards/Cards.h"
#include "Map/Map.h"
#include "Player/Player.h"

class Order {
public:
    Order();
    Order(std::string order);
    Order(const Order& other);
    Order& operator=(const Order& other);
    ~Order();

    bool validate();
    void execute();
};

class orderList {
private:
    list<Order> orders;

public:
    orderList();

    void move(Order order, int position); 
    void remove(int position);
};

class deploy: public Order {
    
};

class advance: public Order {

};

class bomb: public Order {

};

class blockage: public Order {

};

class airlift: public Order {

};

class negotiate: public Order {
            
};