#include "Orders.h"
#include <iostream>
#include <iterator>
#include <algorithm>

// Base Order class implementations
Order::Order() : executed(false) {}
Order::Order(const std::string& orderType) : orderType(orderType), executed(false) {}
Order::~Order() {}

bool Order::validate() {
    std::cout << "Validating order: " << orderType << std::endl;
    return true;
}

void Order::execute() {
//    std::cout << "Executing base order: " << orderType << std::endl;
    notify(this);
}

std::string Order::getOrderType() const {
    return orderType;
}

std::list<Order*>& OrdersList::getOrders() {
    return orders;
}


std::ostream& operator<<(std::ostream& os, const Order& order) {
    os << "Order Type: " << order.orderType;
    if (order.executed) {
        os << " (Executed)";
    }
    return os;
}

string Order::stringToLog() {
    return "Order Executed: " + orderType;
};


// Deploy Order implementations
DeployOrder::DeployOrder() : Order("Deploy") {}
void DeployOrder::execute() {
    std::cout << "Using Deploy card" << std::endl;
    executed = true;
}

// Advance Order implementations
AdvanceOrder::AdvanceOrder() : Order("Advance") {}
void AdvanceOrder::execute() {
    Order::execute();
    std::cout << "Using Advance card" << std::endl;
    executed = true;
}

// Bomb Order implementations
BombOrder::BombOrder() : Order("Bomb") {}
void BombOrder::execute() {
    Order::execute();
    std::cout << "Using Bomb card" << std::endl;
    executed = true;
}

// Blockade Order implementations
BlockadeOrder::BlockadeOrder() : Order("Blockade") {}
void BlockadeOrder::execute() {
    Order::execute();
    std::cout << "Using Blockade card" << std::endl;
    executed = true;
}

// Airlift Order implementations
AirliftOrder::AirliftOrder() : Order("Airlift") {}
void AirliftOrder::execute() {
    Order::execute();
    std::cout << "Using Airlift card" << std::endl;
    executed = true;
}

// Negotiate Order implementations
NegotiateOrder::NegotiateOrder() : Order("Negotiate") {}
void NegotiateOrder::execute() {
    Order::execute();
    std::cout << "Using Negotiate card" << std::endl;
    executed = true;
}

// OrdersList implementations
OrdersList::OrdersList() {}
OrdersList::~OrdersList() {
    for (auto& order : orders) {
        delete order;
    }
}

void OrdersList::addOrder(Order* order) {
    orders.push_back(order);
    notify(this);
}

void OrdersList::move(int fromPosition, int toPosition) {
    if (fromPosition < 0 || fromPosition >= orders.size() || toPosition < 0 || toPosition >= orders.size()) {
        std::cout << "Invalid position\n";
        return;
    }

    auto itFrom = std::next(orders.begin(), fromPosition);
    Order* orderToMove = *itFrom;
    orders.erase(itFrom);
    auto itTo = std::next(orders.begin(), toPosition);
    orders.insert(itTo, orderToMove);

    std::cout << "Moved order from position " << fromPosition << " to " << toPosition << std::endl;
}

void OrdersList::remove(int position) {
    if (position < 0 || position >= orders.size()) {
        std::cout << "Invalid position\n";
        return;
    }

    auto it = std::next(orders.begin(), position);
    delete *it;
    orders.erase(it);

    std::cout << "Removed order at position " << position << std::endl;
}

bool OrdersList::isEmpty() {
    return orders.empty();
}

std::ostream& operator<<(std::ostream& os, const OrdersList& ordersList) {
    int index = 0;
    for (const auto& order : ordersList.orders) {
        os << index++ << ": " << *order << std::endl;
    }
    return os;
}

string OrdersList::stringToLog(){
    return "Order Issued: " + orders.back()->getOrderType() ;
}
