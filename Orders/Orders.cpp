#include "Orders.h"
#include <iostream>
#include <iterator>
#include <algorithm>

// Base Order class implementations
Order::Order() : executed(false) {}
Order::Order(const std::string& orderType) : orderType(orderType), executed(false) {}
Order::~Order() {}

bool Order::validate() {
    // Simple validation logic; actual logic depends on the specific order type
    std::cout << "Validating order: " << orderType << std::endl;
    return true;
}

void Order::execute() {
    if (validate()) {
        std::cout << "Executing order: " << orderType << std::endl;
        executed = true;
    } else {
        std::cout << "Order is not valid: " << orderType << std::endl;
    }
}

std::ostream& operator<<(std::ostream& os, const Order& order) {
    os << "Order Type: " << order.orderType;
    if (order.executed) {
        os << " (Executed)";
    }
    return os;
}

// Deploy Order implementations
DeployOrder::DeployOrder() : Order("Deploy") {}

// Advance Order implementations
AdvanceOrder::AdvanceOrder() : Order("Advance") {}

// Bomb Order implementations
BombOrder::BombOrder() : Order("Bomb") {}

// Blockade Order implementations
BlockadeOrder::BlockadeOrder() : Order("Blockade") {}

// Airlift Order implementations
AirliftOrder::AirliftOrder() : Order("Airlift") {}

// Negotiate Order implementations
NegotiateOrder::NegotiateOrder() : Order("Negotiate") {}

// OrdersList implementations
OrdersList::OrdersList() {}
OrdersList::~OrdersList() {
    for (auto& order : orders) {
        delete order;
    }
}

void OrdersList::addOrder(Order* order) {
    orders.push_back(order);
}

void OrdersList::move(int fromPosition, int toPosition) {
    if (fromPosition < 0 || fromPosition >= orders.size() || toPosition < 0 || toPosition >= orders.size()) {
        std::cout << "Invalid position\n";
        return;
    }

    auto itFrom = std::next(orders.begin(), fromPosition);
    auto itTo = std::next(orders.begin(), toPosition);
    std::iter_swap(itFrom, itTo);

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

std::ostream& operator<<(std::ostream& os, const OrdersList& ordersList) {
    int index = 0;
    for (const auto& order : ordersList.orders) {
        os << index++ << ": " << *order << std::endl;
    }
    return os;
}
