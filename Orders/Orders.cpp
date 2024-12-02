/**
 * @file Orders.cpp
 * @brief This file contains the class and function implementations for Order and its derived classes.
 * 
 * This file is part of the Warzone Game Team Project for COMP 345 - D (Advanced Program Design, C++).
 * It includes the implementation of the Order class, which represents different types of orders in the game,
 * as well as the OrdersList class for managing collections of orders.
 * 
 * Team Members (Team 36):
 * - Amir Vala Khalilzadeh (40253211)
 * - Abdulah Ghulam Ali (40281857)
 * - Arturo Sanchez Escobar (40283236)
 * - Gregory Lajoie (40276231)
 * - Botao Yang (40213554)
 */

#include "Orders.h"
#include "Cards/Cards.h" // Include the header file for the Hand class
#include "Map/Map.h"
#include <iostream>
#include <iterator>
#include <algorithm>

//**************************ORDER**************************

/**
 * @class Order
 * @brief Represents an order in the game.
 */

/**
 * @brief Default constructor for the Order class.
 */
Order::Order() : executed(false) {}

/**
 * @brief Parameterized constructor for the Order class.
 * @param orderType The type of the order.
 */
Order::Order(const std::string &orderType) : orderType(orderType), executed(false) {}

/**
 * @brief Validates the order.
 * @return True if the order is valid, false otherwise.
 */
bool Order::validate()
{
    std::cout << "Validating order: " << orderType << std::endl;
    return true;
}

/**
 * @brief Gets the type of the order.
 * @return The type of the order.
 */
std::string Order::getOrderType() const
{
    return orderType;
}

/**
 * @brief Gets the list of orders.
 * @return A reference to the list of orders.
 */
std::list<Order *> &OrdersList::getOrders()
{
    return orders;
}

/**
 * @brief Stream insertion operator for displaying an order.
 * @param os The output stream.
 * @param order The order to display.
 * @return The output stream.
 */
std::ostream &operator<<(std::ostream &os, const Order &order)
{
    os << "Order Type: " << order.orderType;
    if (order.executed)
    {
        os << " (Executed)";
    }
    return os;
}

/**
 * @brief Converts the order to a loggable string.
 * @return The loggable string representation of the order.
 */
string Order::stringToLog()
{
    return "Order Executed: " + orderType;
}

//**************************DEPLOY ORDER**************************

/**
 * @class DeployOrder
 * @brief Represents a deploy order in the game.
 */

/**
 * @brief Executes the deploy order.
 */
void DeployOrder::execute()
{
    std::cout << "Executing DeployOrder for " << player->getPlayerName() << " deploying "
    <<this->numUnits <<" armies to " << targetTerritory->getName() << " owned by " << targetTerritory->getOwner()->getPlayerName() << std::endl;

    if (targetTerritory->getOwner()->getPlayerName() == player->getPlayerName())
    {
        std::cout << "Player Reinforcement Pool: " << player->getReinforcementPool() << std::endl;
        std::cout << "Number of Units: " << numUnits << std::endl;
        if (player->getReinforcementPool() >= numUnits)
        {
            targetTerritory->setNumberOfArmies(targetTerritory->getNumberOfArmies() + numUnits);
            player->setReinforcementPool(player->getReinforcementPool() - numUnits);
            executed = true;
            notify(this);
        }
        else
        {
            std::cout << "Invalid deploy order: " << player->getPlayerName() << " does not have enough units to deploy" << std::endl;
            executed = false; // Explicitly set this to false
        }
    }
    else
    {
        std::cout << "Invalid deploy order: " << targetTerritory->getName() << " does not belong to " << player->getPlayerName() << std::endl;
        executed = false; // Explicitly set this to false
    }
}


//**************************ADVANCE ORDER**************************

/**
 * @class AdvanceOrder
 * @brief Represents an advance order in the game.
 */

/**
 * @brief Executes the advance order.
 */
void AdvanceOrder::execute()
{
    /*
     * Upper part handles the part where a player is a cheater, it conquers all adjacent once
     * per turn and said territories will now have 3 armies on them for other players to attack
     *
     * Second part handles the normal execution and normal caluclations for conquering a territory
     */
    std::cout << "Executing AdvanceOrder for " << player->getPlayerName() << " deploying "
              <<this->numUnits <<" armies to " << targetTerritory->getName() << " from " << this->sourceTerritory->getName() << std::endl;
    /*
    if(sourceTerritory->getOwner()->getStrategyType() == "cheater") {
        // Conquer all adjacent territories
        for(int i = 0; i < player->toAttack().size(); i++) {
            player->toAttack().at(i)->setOwner(player);
            player->toAttack().at(i)->setNumberOfArmies(3);
            executed = true;
            notify(this);
        }

    */
        // Normal Execute
        if (sourceTerritory->getOwner()->getPlayerName() == player->getPlayerName()){
            if (sourceTerritory->isAdjacent(targetTerritory))
            {
                if (targetTerritory->getOwner()->getPlayerName() == player->getPlayerName())
                {
                    targetTerritory->setNumberOfArmies(targetTerritory->getNumberOfArmies() + numUnits);
                    sourceTerritory->setNumberOfArmies(sourceTerritory->getNumberOfArmies() - numUnits);
                    executed = true;
                    notify(this);
                }
                else
                { // Perform attack simulation
                    if (player->hasTruceWith(targetTerritory->getOwner()->getPlayerName()))
                    {
                        std::cout << "Invalid advance order: " << player->getPlayerName() << " has a truce with " << targetTerritory->getOwner() << std::endl;
                    }
                    else
                    {
                        int attackerArmies = numUnits;
                        int defenderArmies = targetTerritory->getNumberOfArmies();
                        int attackerLosses = 0;
                        int defenderLosses = 0;

                        // Roll dice for attacker and defender
                        for (int i = 0; i < numUnits; i++)
                        {
                            int attackerRoll = rand() % 100 + 1; // Generate a number between 1 and 100
                            int defenderRoll = rand() % 100 + 1; // Generate a number between 1 and 100

                            if (attackerRoll <= 60 && defenderLosses < defenderArmies)
                            { // 60% chance for attacker to kill a defender
                                defenderLosses++;
                            }
                            if (defenderRoll <= 70 && attackerLosses < attackerArmies)
                            { // 70% chance for defender to kill an attacker
                                attackerLosses++;
                            }
                        }

                        if(targetTerritory->getOwner()->getStrategyType()=="neutral"){
                            std::cout << targetTerritory->getOwner()->getPlayerName() <<
                                      " is no longer a neutral player because they were attacked. They are now aggressive" << std::endl;
                            player->setStrategy("aggressive");
                        }

                        // Update armies
                        sourceTerritory->setNumberOfArmies(sourceTerritory->getNumberOfArmies() - attackerLosses);
                        targetTerritory->setNumberOfArmies(defenderArmies - defenderLosses);

                        // Check if defender has been defeated
                        if (targetTerritory->getNumberOfArmies() == 0)
                        {
                            auto oldOwner = targetTerritory->getOwner();
                            oldOwner->removeOwnedTerritory(targetTerritory);
                            targetTerritory->setOwner(player);
                            player->addOwnedTerritory(targetTerritory);
                            targetTerritory->setNumberOfArmies(attackerArmies - attackerLosses);

                            // Award a card to the player if they conquered at least one territory
                            // Card *drawnCard = deck->draw();
                            // player->getHand()->place(drawnCard);
                            std::cout << "Player " << player->getPlayerName() << " has been rewarded a card for successfully conquering " << targetTerritory->getName() << std::endl;
                        }



                    }
                }
            }
            else
            {
                std::cout << "Invalid advance order: " << sourceTerritory->getName() << " is not adjacent to " << targetTerritory->getName() << std::endl;
            }
        }
        else
        {
            std::cout << "Invalid advance order: " << sourceTerritory->getName() << " does not belong to " << player->getPlayerName() << std::endl;
        }
    }



//**************************BOMB ORDER**************************

/**
 * @class BombOrder
 * @brief Represents a bomb order in the game.
 */

/**
 * @brief Executes the bomb order.
 */
void BombOrder::execute()
{
    std::cout << "Executing BombOrder for " << player->getPlayerName() << " bombing " << this->targetTerritory << std::endl;
    if (player->hasTruceWith(targetTerritory->getOwner()->getPlayerName()))
    {
        std::cout << "Invalid bomb order: " << player->getPlayerName() << " has a truce with " << targetTerritory->getOwner() << std::endl;
    }
    else
    {
        // if (player->getHand()->hasCard("Bomb")) {
        if (targetTerritory->getOwner()->getPlayerName() != player->getPlayerName())
        {
            // if the target territory is not adjacent to one of the territory owned by the player -> ionvalid
            bool isAdjacent = false;
            for (Territory *territory : player->getOwnedTerritories())
            {
                if (territory->isAdjacent(targetTerritory))
                {
                    isAdjacent = true;
                    break;
                }
            }
            if (isAdjacent)
            {
                targetTerritory->setNumberOfArmies(targetTerritory->getNumberOfArmies() / 2);
                notify(this);
                executed = true;
                if(targetTerritory->getOwner()->getStrategyType()=="neutral"){
                    std::cout << targetTerritory->getOwner()->getPlayerName() <<
                              " is no longer a neutral player because they were attacked. They are now aggressive" << std::endl;
                    player->setStrategy("aggressive");
                }
            }
            else
            {
                std::cout << "Invalid bomb order:  " << player->getPlayerName() << " does not have any adjacent territory to " << targetTerritory->getName() << std::endl;
            }
        }
        else
        {
            std::cout << "Invalid bomb order: " << targetTerritory->getName() << " belongs to you" << std::endl;
        }
    }
    //}
    // else {
    // std::cout << "Invalid bomb order: " << player->getPlayerName() << " does not have a Bomb card" << std::endl;
    //}
}

//**************************BLOCKADE ORDER**************************

/**
 * @class BlockadeOrder
 * @brief Represents a blockade order in the game.
 */

/**
 * @brief Executes the blockade order.
 */
void BlockadeOrder::execute()
{
    std::cout << "Executing BlockadeOrder for " << player->getPlayerName() << " bombing " << this->targetTerritory << std::endl;
    // if (player->getHand()->hasCard("Blockade")) {
    if (targetTerritory->getOwner()->getPlayerName() == player->getPlayerName())
    {
        targetTerritory->setNumberOfArmies(targetTerritory->getNumberOfArmies() * 2);
//        targetTerritory->setOwner("Neutral");
        notify(this);
        executed = true;
    }
    else
    {
        std::cout << "Invalid blockade order: " << targetTerritory->getName() << " does not belong to " << player->getPlayerName() << std::endl;
    }
    // }
    // else {
    // std::cout << "Invalid blockade order: " << player->getPlayerName() << " does not have a Blockade card" << std::endl;
    // }
}

//**************************AIRLIFT ORDER**************************

/**
 * @class AirliftOrder
 * @brief Represents an airlift order in the game.
 */

/**
 * @brief Executes the airlift order.
 */
void AirliftOrder::execute()
{
    std::cout << "Executing AirLift for " << player->getPlayerName() << " airlifting armies from " << this->targetTerritory << std::endl;

    if (player->hasTruceWith(targetTerritory->getOwner()->getPlayerName()))
    {
        std::cout << "Invalid airlift order: " << player->getPlayerName() << " has a truce with " << targetTerritory->getOwner() << std::endl;
        return;
    }
    // if (player->getHand()->hasCard("Airlift")) {
    if (sourceTerritory->getOwner()->getPlayerName() == player->getPlayerName())
    {
        if (targetTerritory->getOwner()->getPlayerName() == player->getPlayerName())
        {
            targetTerritory->setNumberOfArmies(targetTerritory->getNumberOfArmies() + numUnits);
            sourceTerritory->setNumberOfArmies(sourceTerritory->getNumberOfArmies() - numUnits);
            notify(this);
            executed = true;
        }
        else
        {
            std::cout << "Invalid airlift order: " << targetTerritory->getName() << " does not belong to " << player->getPlayerName() << std::endl;
        }
    }
    else
    {
        std::cout << "Invalid airlift order: " << sourceTerritory->getName() << " does not belong to " << player->getPlayerName() << std::endl;
    }
    // }
    // else {
    // std::cout << "Invalid airlift order: " << player->getPlayerName() << " does not have an Airlift card" << std::endl;
    // }
}

//**************************NEGOTIATE ORDER**************************

/**
 * @class NegotiateOrder
 * @brief Represents a negotiate order in the game.
 */

/**
 * @brief Executes the negotiate order.
 */
void NegotiateOrder::execute()
{
    std::cout << "Executing NegotiateOrder for " << player->getPlayerName() << " with " << this->targetPlayer->getPlayerName() << std::endl;

    // if(player->getHand()->hasCard("Diplomacy")){
    if (player->getPlayerName() == targetPlayer->getPlayerName())
    {
        std::cout << "Invalid negotiate order: " << player->getPlayerName() << " cannot negotiate with themselves" << std::endl;
    }
    else
    {
        player->addTrucePlayer(targetPlayer->getPlayerName());
        targetPlayer->addTrucePlayer(player->getPlayerName());
        notify(this);
        executed = true;
    }
    // }
    // else{
    // std::cout << "Invalid negotiate order: " << player->getPlayerName() << " does not have a Diplomacy card" << std::endl;
    // }
}
//**************************ORDERS LIST**************************

/**
 * @class OrdersList
 * @brief Represents a list of orders in the game.
 */

/**
 * @brief Default constructor for the OrdersList class.
 */
OrdersList::OrdersList() {}

/**
 * @brief Destructor for the OrdersList class.
 */
OrdersList::~OrdersList()
{
    for (auto &order : orders)
    {
        delete order;
    }
}

/**
 * @brief Adds an order to the list.
 * @param order The order to add.
 */
void OrdersList::addOrder(Order *order)
{
    orders.push_back(order);
    notify(this);
}

/**
 * @brief Moves an order from one position to another.
 * @param fromPosition The initial position of the order.
 * @param toPosition The new position of the order.
 */
void OrdersList::move(int fromPosition, int toPosition)
{
    if (fromPosition < 0 || fromPosition >= orders.size() || toPosition < 0 || toPosition >= orders.size())
    {
        std::cout << "Invalid position\n";
        return;
    }

    auto itFrom = std::next(orders.begin(), fromPosition);
    Order *orderToMove = *itFrom;
    orders.erase(itFrom);
    auto itTo = std::next(orders.begin(), toPosition);
    orders.insert(itTo, orderToMove);

    std::cout << "Moved order from position " << fromPosition << " to " << toPosition << std::endl;
}

/**
 * @brief Removes an order from the list.
 * @param position The position of the order to remove.
 */
void OrdersList::remove(int position)
{
    if (position < 0 || position >= orders.size())
    {
        std::cout << "Invalid position\n";
        return;
    }

    auto it = std::next(orders.begin(), position);
    delete *it;
    orders.erase(it);

    std::cout << "Removed order at position " << position << std::endl;
}

/**
 * @brief Checks if the list is empty.
 * @return True if the list is empty, false otherwise.
 */
bool OrdersList::isEmpty()
{
    return orders.empty();
}


/**
 * @brief Gets the next order in the list.
 * @return A pointer to the next order.
 */
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

bool Order::isExecuted() const
{
    return executed;
}

/**
 * @brief Stream insertion operator for displaying an orders list.
 * @param os The output stream.
 * @param ordersList The orders list to display.
 * @return The output stream.
 */
std::ostream &operator<<(std::ostream &os, const OrdersList &ordersList)
{
    int index = 0;
    for (const auto &order : ordersList.orders)
    {
        os << index++ << ": " << *order << std::endl;
    }
    return os;
}

/**
 * @brief Converts the orders list to a loggable string.
 * @return The loggable string representation of the orders list.
 */
string OrdersList::stringToLog()
{
    return "Order Issued: " + orders.back()->getOrderType();
}