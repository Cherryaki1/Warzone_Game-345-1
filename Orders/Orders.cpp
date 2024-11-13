#include "Orders.h"
#include "Cards/Cards.h" // Include the header file for the Hand class
#include "Map/Map.h"
#include <iostream>
#include <iterator>
#include <algorithm>


// ----------------------------------------------------------
//              Base Order class implementations
// ----------------------------------------------------------
Order::Order() : executed(false) {}
Order::Order(const std::string& orderType) : orderType(orderType), executed(false) {}

bool Order::validate() {
    std::cout << "Validating order: " << orderType << std::endl;
    return true;
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
}


// ----------------------------------------------------------
//              execute() of Derived Order classes
// ----------------------------------------------------------

// Deploy Order
void DeployOrder::execute() {
    if (targetTerritory->getOwner() == player->getPlayerName()) {
        if (player->getReinforcementPool() >= numUnits) {
            targetTerritory->setNumberOfArmies(targetTerritory->getNumberOfArmies() + numUnits);
            player->setReinforcementPool(player->getReinforcementPool() - numUnits);
            notify(this);
            executed = true;
        }
        else {
            std::cout << "Invalid deploy order: " << player->getPlayerName() << " does not have enough units to deploy" << std::endl;
        }
    }
    else {
        std::cout << "Invalid deploy order: " << targetTerritory->getName() << " does not belong to " << player->getPlayerName() << std::endl;
    }
}


extern Deck* deck = new Deck;
// Advance Order
void AdvanceOrder::execute() {
    if (sourceTerritory->getOwner() == player->getPlayerName()) {
        if (sourceTerritory->isAdjacent(targetTerritory)) {
            if (targetTerritory->getOwner() == player->getPlayerName()) {
                targetTerritory->setNumberOfArmies(targetTerritory->getNumberOfArmies() + numUnits);
                sourceTerritory->setNumberOfArmies(sourceTerritory->getNumberOfArmies() - numUnits);
                notify(this);
                executed = true;
            }
            else { // Perform attack simulation
            if (player->hasTruceWith(targetTerritory->getOwner())) {
                std::cout << "Invalid advance order: " << player->getPlayerName() << " has a truce with " << targetTerritory->getOwner() << std::endl;
                return;
            }
                int attackerArmies = numUnits;
                int defenderArmies = targetTerritory->getNumberOfArmies();
                int attackerLosses = 0;
                int defenderLosses = 0;

                // Roll dice for attacker and defender
                for (int i = 0; i < numUnits; i++) {
                    int attackerRoll = rand() % 100 + 1; // Generate a number between 1 and 100
                    int defenderRoll = rand() % 100 + 1; // Generate a number between 1 and 100

                    if (attackerRoll <= 60 && defenderLosses < defenderArmies) { // 60% chance for attacker to kill a defender
                        defenderLosses++;
                    }
                    if (defenderRoll <= 70 && attackerLosses < attackerArmies) { // 70% chance for defender to kill an attacker
                        attackerLosses++;
                    }
                }

                // Update armies
                sourceTerritory->setNumberOfArmies(sourceTerritory->getNumberOfArmies() - attackerLosses);
                targetTerritory->setNumberOfArmies(defenderArmies - defenderLosses);

                // Check if defender has been defeated
                if (targetTerritory->getNumberOfArmies() == 0) {
                    targetTerritory->setOwner(player->getPlayerName());
                    targetTerritory->setNumberOfArmies(attackerArmies - attackerLosses);

                    // Award a card to the player if they conquered at least one territory
                    Card* drawnCard = deck->draw();
                    player->getHand()->place(drawnCard);
                    std::cout << "Player " << player->getPlayerName() << " has been rewarded a card for successfully conquering " << targetTerritory->getName() << std::endl;
                }
            }
        }
        else {
            std::cout << "Invalid advance order: " << sourceTerritory->getName() << " is not adjacent to " << targetTerritory->getName() << std::endl;
        }
    }
    else {
        std::cout << "Invalid advance order: " << sourceTerritory->getName() << " does not belong to " << player->getPlayerName() << std::endl;
    }
}

// Bomb Order
void BombOrder::execute() {
    if (player->hasTruceWith(targetTerritory->getOwner())) {
        std::cout << "Invalid bomb order: " << player->getPlayerName() << " has a truce with " << targetTerritory->getOwner() << std::endl;
        return;
    }
    if (player->getHand()->hasCard("Bomb")) {
        if (targetTerritory->getOwner() != player->getPlayerName()) {
            //if the target territory is not adjacent to one of the territory owned by the player -> ionvalid
            bool isAdjacent = false;
            for (Territory* territory : player->getOwnedTerritories()) {
                if (territory->isAdjacent(targetTerritory)) {
                    isAdjacent = true;
                    break;
                }
            }
            if (isAdjacent) {
                targetTerritory->setNumberOfArmies(targetTerritory->getNumberOfArmies() / 2);
                notify(this);
                executed = true;
            }
            else {
                std::cout << "Invalid bomb order:  " << player->getPlayerName() << " does not have any adjacent territory to " << targetTerritory->getName() << std::endl;
            }
        }
        else {
            std::cout << "Invalid bomb order: " << targetTerritory->getName() << " belongs to you" << std::endl;
        }
    }
    else {
        std::cout << "Invalid bomb order: " << player->getPlayerName() << " does not have a Bomb card" << std::endl;
    }
}

// Blockade Order
void BlockadeOrder::execute() {
    if (player->getHand()->hasCard("Blockade")) {
        if (targetTerritory->getOwner() == player->getPlayerName()) {
            targetTerritory->setNumberOfArmies(targetTerritory->getNumberOfArmies() * 2);
            targetTerritory->setOwner("Neutral");
            notify(this);
            executed = true;
        }
        else {
            std::cout << "Invalid blockade order: " << targetTerritory->getName() << " does not belong to " << player->getPlayerName() << std::endl;
        }
    }
    else {
        std::cout << "Invalid blockade order: " << player->getPlayerName() << " does not have a Blockade card" << std::endl;
    }
}

// Airlift Order
void AirliftOrder::execute() {
    if (player->hasTruceWith(targetTerritory->getOwner())) {
        std::cout << "Invalid airlift order: " << player->getPlayerName() << " has a truce with " << targetTerritory->getOwner() << std::endl;
        return;
    }
    if (player->getHand()->hasCard("Airlift")) {
        if (sourceTerritory->getOwner() == player->getPlayerName()) {
            if (targetTerritory->getOwner() == player->getPlayerName()) {
            targetTerritory->setNumberOfArmies(targetTerritory->getNumberOfArmies() + numUnits);
            sourceTerritory->setNumberOfArmies(sourceTerritory->getNumberOfArmies() - numUnits);
            notify(this);
            executed = true;
            }
            else {
                std::cout << "Invalid airlift order: " << targetTerritory->getName() << " does not belong to " << player->getPlayerName() << std::endl;
            }
        }
        else {
            std::cout << "Invalid airlift order: " << sourceTerritory->getName() << " does not belong to " << player->getPlayerName() << std::endl;
        }
    }
    else {
        std::cout << "Invalid airlift order: " << player->getPlayerName() << " does not have an Airlift card" << std::endl;
    }

}

// Negotiate Order
void NegotiateOrder::execute() {
    if(player->getHand()->hasCard("Diplomacy")){
        if(player->getPlayerName() == targetPlayer->getPlayerName()){
            std::cout << "Invalid negotiate order: " << player->getPlayerName() << " cannot negotiate with themselves" << std::endl;
        }
        else{
            player->addTrucePlayer(targetPlayer->getPlayerName());
            targetPlayer->addTrucePlayer(player->getPlayerName());
            notify(this);
            executed = true;
        }
    }
    else{
        std::cout << "Invalid negotiate order: " << player->getPlayerName() << " does not have a Diplomacy card" << std::endl;
    }
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

// get next order on the list
Order *OrdersList::getNextOrder()
{
    std::cout << "getNextOrder() was called\n"
              << std::endl;

    // if list not empty, pop and return next order
    if (!orders.empty())
    {
        Order *nextOrderPtr = orders.front();
        orders.pop_front();
        return nextOrderPtr;
    }
    else
    { // if list is empty, print a message
        std::cout << " -- Order list is empty !" << std::endl;
        return nullptr;
    }
}

std::ostream& operator<<(std::ostream& os, const OrdersList& ordersList) {
    int index = 0;
    for (const auto& order : ordersList.orders) {
        os << index++ << ": " << *order << std::endl;
    }
    return os;
}

string OrdersList::stringToLog(){
    return "Order Issued: " + orders.back()->getOrderType();
}