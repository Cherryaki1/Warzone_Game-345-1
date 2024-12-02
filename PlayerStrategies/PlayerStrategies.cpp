/**
 * @file PlayerStrategies.cpp
 * @brief This file contains the class and function implementations for various player strategies.
 * 
 * This file is part of the Warzone Game Team Project for COMP 345 - D (Advanced Program Design, C++).
 * It includes the implementation of different player strategies such as Neutral, Cheater, Human, Aggressive, and Benevolent.
 * 
 * Team Members (Team 36):
 * - Amir Vala Khalilzadeh (40253211)
 * - Abdulah Ghulam Ali (40281857)
 * - Arturo Sanchez Escobar (40283236)
 * - Gregory Lajoie (40276231)
 * - Botao Yang (40213554)
 */

#include "PlayerStrategies.h"
#include "Cards.h"
#include "GameEngine.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Player;
class Territory;
class Order;

/**
 * @brief Gets the type of the player strategy.
 * @return The type of the player strategy.
 */
string PlayerStrategy::getType() {return *type;}

// ****************************** Neutral Player ******************************

/**
 * @class Neutral
 * @brief Represents a neutral player strategy.
 */

/**
 * @brief Constructs a Neutral player strategy.
 * @param player The player associated with this strategy.
 */
Neutral::Neutral(Player *player) {
    this->player = player;
    type= new string("neutral");
}

/**
 * @brief Neutral Player issues a specific order
 * @param o The order to issue.
 */
void Neutral::issueOrder(Order *o) {

}

/**
 * @brief Neutral Player issues an order.
 */
void Neutral::issueOrder() {
    cout << player->getPlayerName() << " is a neutral player. No actions taken during this turn." << endl;
}

/**
 * @brief Neutral Player: Does not attack.
 * @return An empty vector as Neutral player does not attack.
 */
vector<Territory *> Neutral::toAttack() {
    return {}; //Neutral player does not attack unprovoked
}

/**
 * @brief Neutral Player: Does not defend.
 * @return An empty vector as Neutral player does not defend.
 */
vector<Territory *> Neutral::toDefend() {
    return {}; //Neutral player does not defend unprovoked
}

// ****************************** Cheater Player ******************************

/**
 * @class Cheater
 * @brief Represents a cheater player strategy.
 */

/**
 * @brief Constructs a Cheater player strategy.
 * @param player The player associated with this strategy.
 */
Cheater::Cheater(Player *player) {
    this->player = player;
    type= new string("cheater");
}

/**
 * @brief Issues a specific order for the Cheater player.
 * @param o The order to issue.
 */
void Cheater::issueOrder(Order *o) {

}

/**
 * @brief Issues an order for the Cheater player.
 */
void Cheater::issueOrder() {
    // Conquers all adjacent territories
    for (Territory* territory : player->getOwnedTerritories()) {
        for (Territory* neighbor : territory->adjacentTerritories) {
            if (neighbor->getOwner()->getPlayerName() != player->getPlayerName()) {
                auto oldOwner = neighbor->getOwner();
                neighbor->setOwner(player);
                player->addOwnedTerritory(neighbor);
                oldOwner->removeOwnedTerritory(neighbor);
                cout << player->getPlayerName() << " has conquered " << neighbor->getName() << " from " << neighbor->getOwner()->getPlayerName() << endl;
            }
        }
    }
}

/**
 * @brief Identifies the territories to attack for the Cheater player.
 * @return A vector of territories to attack.
 */
vector<Territory *> Cheater::toAttack() {
    vector<Territory *> attackList;
    for (Territory* territory : player->getOwnedTerritories()) {
        for (Territory* neighbor : territory->adjacentTerritories) {
            if (neighbor->getOwner() != player) {
                attackList.push_back(neighbor);
            }
        }
    }
    return attackList;
}

/**
 * @brief Identifies the territories to defend for the Cheater player.
 * @return A vector of territories to defend.
 */
vector<Territory *> Cheater::toDefend() {
    return player->getOwnedTerritories();
}


// ****************************** Human Player ******************************

/**
 * @class Human
 * @brief Represents a human player strategy.
 */

/**
 * @brief Constructs a Human player strategy.
 * @param player The player associated with this strategy.
 */
Human::Human(Player *player) {
    this->player = player;
    type=new string("human");
}

/**
 * @brief Issues a specific order for the Human player.
 * @param newOrder The order to issue.
 */
void Human::issueOrder(Order *newOrder) {
    if (newOrder != nullptr) {
        player->addToOrderList(newOrder);
        std::cout << newOrder->getOrderType() << " order issued." << std::endl;
    } else {
        std::cout << "Error: Cannot issue a null order." << std::endl;
    }
}

/**
 * @brief Issues an order for the Human player.
 */
void Human::issueOrder() {
    cout << "\n*****\n" <<player->getPlayerName() << ": What are your orders?" << endl;
    cout << "---You have " << player->getReinforcementPool() << " armies available for deployment\nOPTIONS (enter the number):" << endl;
    cout << "1 - Deploy Armies\n2 - Advance Armies\n3 - Play a card\n4 - Display Map\n5 - End your turn\n--Enter your choice: " << endl;
    string choice;
    choice = processor->getCommand()->getCommandText();
    if(choice == "1"){ //Deploy
        try{
            cout << "Deployment chosen\n\tWhere would you like to deploy your armies?"<<endl;
            for(int i = 0; i<player->toDefend().size(); i++){
                cout<<"\t" << (i+1) << "\t" << player->toDefend().at(i)->getName() << endl;
            }
            choice = processor->getCommand()->getCommandText();
            int choiceNum = stoi(choice);
            Territory *chosenTerr = player->toDefend().at((choiceNum - 1));
            string chosenTerrStr = chosenTerr->getName();
            cout << "How many units would you like to deploy to " << chosenTerrStr << "?" << "  Total maximum of " <<
                    player->getReinforcementPool() << ", otherwise order will be invalid upon execution" << endl;
            choice = processor->getCommand()->getCommandText();
            choiceNum = stoi(choice);
            if (choiceNum>0){
                Order* deployOrder = new DeployOrder(player, chosenTerr, choiceNum);
                player->addToOrderList(deployOrder);
                cout << "Order deploying " <<choiceNum<< " armies to " << chosenTerrStr << " added to " << player->getPlayerName() << "'s orderlist!" <<endl;
            } else {
                cout << "\nNumber of units must be an integer greater than 0." << endl;
            }
        } catch(...){
            cout << "\nInvalid entry - enter a valid option" <<endl;
        }
        this->issueOrder();
    }
    else if (choice == "2"){ //Advance
        try{
            cout << "Advancement chosen\n\tWhat is the source territory?"<<endl;
            for(int i = 0; i<player->getOwnedTerritories().size(); i++){
                cout<<"\t" << (i+1) << "\t" << player->getOwnedTerritories().at(i)->getName() << endl;
            }
            choice = processor->getCommand()->getCommandText();
            int choiceNum = stoi(choice);
            Territory *sourceTerr = player->getOwnedTerritories().at((choiceNum - 1));
            string sourceTerrStr = sourceTerr->getName();

            cout << "\tWhat is the target territory?"<<endl;
            for(int i = 0; i<sourceTerr->adjacentTerritories.size(); i++){
                    cout<<"\t" << (i+1) << "\t" << sourceTerr->adjacentTerritories.at(i)->getName() << endl;
            }
            choice = processor->getCommand()->getCommandText();
            choiceNum = stoi(choice);
            Territory *targetTerr = sourceTerr->adjacentTerritories.at(choiceNum-1);
            string targetTerrStr = targetTerr->getName();
            cout << "How many units would you like to deploy to " << targetTerrStr << "?" <<  endl;
            choice = processor->getCommand()->getCommandText();
            choiceNum = stoi(choice);
            if (choiceNum>0){
                Order* advanceOrder = new AdvanceOrder(player, sourceTerr, targetTerr, choiceNum);
                player->addToOrderList(advanceOrder);
                cout << "Order advancing " <<choiceNum<< " armies to " << targetTerrStr << " added to " << player->getPlayerName() << "'s orderlist!" <<endl;
            } else {
                cout << "\nNumber of units must be an integer greater than 0." << endl;
            }

        } catch(...){
            cout << "\nInvalid entry - enter a valid option" <<endl;
        }
        this->issueOrder();
    }
    else if (choice == "3"){ //Play Card
        auto playerHand = player->getHand();
        cout << "Which card would you like to play?"<<endl;
        cout << playerHand <<endl;
        try{
            choice = processor->getCommand()->getCommandText();
            int choiceNum = stoi(choice);

            auto toPlay = playerHand->getHand()->at(choiceNum-1);
            string type = toPlay->getType();
            toPlay->play();
            //"Bomb", "Reinforcement", "Blockade", "Airlift", "Diplomacy"
            if (type == "Bomb"){
                cout << toPlay << endl;
                cout << "Choose a territory to bomb:" <<endl;
                for (int i = 0; i<player->toAttack().size(); i++){
                    cout << "\t" << (i+1) << "\t" << player->toAttack().at(i)->getName() << endl;
                }
                choice = processor->getCommand()->getCommandText();
                choiceNum = stoi(choice);
                Territory *targetTerr = player->toAttack().at(choiceNum-1);
                string targetTerrStr = targetTerr->getName();

                auto bombOrder = new BombOrder(player, targetTerr);
                player->addToOrderList(bombOrder);

                cout << "Order bombing " <<targetTerrStr << " added to " << player->getPlayerName() << "'s orderlist!" <<endl;

            }

            else if (type == "Reinforcement"){ //what do we do with this
                cout << "The reinforcement card is deprecated, please use the deploy function." << endl;
            }

            else if (type == "Blockade"){
                cout << toPlay << endl;
                cout << "Choose a territory to blockade:" << endl;
                for (int i = 0; i<player->getOwnedTerritories().size(); i++){
                    cout << "\t" << (i+1) << "\t" << player->getOwnedTerritories().at(i)->getName() << endl;
                }
                choice = processor->getCommand()->getCommandText();
                choiceNum = stoi(choice);
                Territory *targetTerr = player->getOwnedTerritories().at(choiceNum-1);
                string targetTerrStr = targetTerr->getName();

                auto blockadeOrder = new BlockadeOrder(player, targetTerr);
                player->addToOrderList(blockadeOrder);

                cout << "Order blockading " <<targetTerrStr << " added to " << player->getPlayerName() << "'s orderlist!" <<endl;
            }

            else if (type == "Airlift"){
                cout << toPlay << endl;
                cout << "Choose the territory to airlift from:" <<endl;
                for (int i = 0; i<player->getOwnedTerritories().size(); i++){
                    cout << "\t" << (i+1) << "\t" << player->getOwnedTerritories().at(i)->getName() << endl;
                }
                choice = processor->getCommand()->getCommandText();
                choiceNum = stoi(choice);
                Territory *sourceTerr = player->getOwnedTerritories().at(choiceNum - 1);
                string sourceTerrStr = sourceTerr->getName();

                cout << "Choose the territory to airlift to:" <<endl;
                for (int i = 0; i<player->getOwnedTerritories().size(); i++){
                    cout << "\t" << (i+1) << "\t" << player->getOwnedTerritories().at(i)->getName() << endl;
                }
                choice = processor->getCommand()->getCommandText();
                choiceNum = stoi(choice);
                Territory *targetTerr = player->getOwnedTerritories().at(choiceNum - 1);
                string targetTerrStr = targetTerr->getName();

                cout << "Your source territory has " <<sourceTerr->getNumberOfArmies() << " armies."
                << " How many would you like to airlift to your target?"<<endl;
                choice = processor->getCommand()->getCommandText();
                choiceNum = stoi(choice);

                auto airliftOrder = new AirliftOrder(player, sourceTerr, targetTerr, choiceNum);
                player->addToOrderList(airliftOrder);

                cout << "Order airlifting " <<choiceNum << " armies from " << sourceTerrStr << " to "
                << targetTerrStr << " has been added to" << player->getPlayerName() << "'s orderlist!" <<endl;
            }

            else if (type == "Diplomacy"){ //need to get the playerlist visible here somehow
                cout << toPlay << endl;

                cout << "Choose a player to negotiate with:" <<endl;
                for (int i = 0; i<player->getCurrentGameEngine()->getPlayerList()->size(); i++){
                    cout << "\t" << (i+1) << "\t" << player->getCurrentGameEngine()->getPlayerList()->at(i)->getPlayerName() << endl;
                }
                choice = processor->getCommand()->getCommandText();
                choiceNum = stoi(choice);

                auto chosenPlayer = player->getCurrentGameEngine()->getPlayerList()->at(choiceNum-1);
                auto negotiateOrder = new NegotiateOrder(player, chosenPlayer);
                player->addToOrderList(negotiateOrder);

                cout << "Order to negotiate with " << chosenPlayer->getPlayerName() << " has been added to " << player->getPlayerName() << "'s orderlist!" <<endl;
            }
            else {throw runtime_error("Incorrect Card!");}

        } catch(...){
            cout << "\nInvalid entry - enter a valid option" <<endl;
            }

        this->issueOrder();
    }
    else if (choice == "4"){ //End turn
        cout << *(player->getCurrentGameEngine()->getGameMap())<<endl;
    }
    else if (choice == "5"){ //End turn
        cout << "End of this turn."<<endl;
    }
    else {
        cout << "Invalid option!"<<endl;
        this->issueOrder();
    }

}

/**
 * @brief Identifies the territories to attack for the Human player.
 * @return A vector of territories to attack.
 */
vector<Territory *> Human::toAttack() {
    return vector<Territory *>();
}

/**
 * @brief Identifies the territories to defend for the Human player.
 * @return A vector of territories to defend.
 */
vector<Territory *> Human::toDefend() {
    return vector<Territory *>();
}


// ****************************** Aggressive Player ******************************

/**
 * @class Aggressive
 * @brief Represents an aggressive player strategy.
 */

/**
 * @brief Constructs an Aggressive player strategy.
 * @param player The player associated with this strategy.
 */
Aggressive::Aggressive(Player *player) {
    this->player = player;
    type=new string("aggressive");
}

/**
 * @brief Issues a specific order for the Aggressive player.
 * @param o The order to issue.
 */
void Aggressive::issueOrder(Order *o) {

}

/**
 * @brief Issues an order for the Aggressive player.
 */
void Aggressive::issueOrder() {
    // Deploy armies on the strongest country
    Territory* strongestTerritory = nullptr;
    int maxArmies = -1;
    for (Territory* territory : player->getOwnedTerritories()) {
        if (territory->getNumberOfArmies() > maxArmies) {
            maxArmies = territory->getNumberOfArmies();
            strongestTerritory = territory;
        }
    }

    if (strongestTerritory != nullptr) {
        Order* deployOrder = new DeployOrder(player, strongestTerritory, player->getReinforcementPool());
        player->addToOrderList(deployOrder);
        cout << "Order deploying " << player->getReinforcementPool() << " armies to " << strongestTerritory->getName() << " added to " << player->getPlayerName() << "'s order list!" << endl;
    }

    // Advance armies to enemy territories
    for (Territory* sourceTerritory : player->getOwnedTerritories()) {
        for (Territory* targetTerritory : sourceTerritory->adjacentTerritories) {
            if (targetTerritory->getOwner() != player && sourceTerritory->getNumberOfArmies()>0) {
                Order* advanceOrder = new AdvanceOrder(player, sourceTerritory, targetTerritory, sourceTerritory->getNumberOfArmies());
                player->addToOrderList(advanceOrder);
                cout << "Order advancing " << sourceTerritory->getNumberOfArmies() << " armies from " << sourceTerritory->getName() << " to " << targetTerritory->getName() << " added to " << player->getPlayerName() << "'s order list!" << endl;
            }
        }
    }

    // Use any card with an aggressive purpose
    auto playerHand = player->getHand();
    auto toPlay = playerHand->getHand();
    for (int i = 0; i < toPlay->size(); i++) {
        if (toPlay->at(i)->getType() == "Bomb" || toPlay->at(i)->getType() == "Airlift") {
            toPlay->at(i)->play();
        }
    }
}

/**
 * @brief Identifies the territories to attack for the Aggressive player.
 * @return A vector of territories to attack.
 */
vector<Territory *> Aggressive::toAttack() {
    vector<Territory *> attackList;
    for (Territory* territory : player->getOwnedTerritories()) {
        for (Territory* neighbor : territory->adjacentTerritories) {
            if (neighbor->getOwner() != player) {
                attackList.push_back(neighbor);
            }
        }
    }
    return attackList;
}

/**
 * @brief Identifies the territories to defend for the Aggressive player.
 * @return A vector of territories to defend.
 */
vector<Territory *> Aggressive::toDefend() {
    vector<Territory *> defendList;
    Territory* strongestTerritory = nullptr;
    int maxArmies = -1;
    for (Territory* territory : player->getOwnedTerritories()) {
        if (territory->getNumberOfArmies() > maxArmies) {
            maxArmies = territory->getNumberOfArmies();
            strongestTerritory = territory;
        }
    }
    if (strongestTerritory != nullptr) {
        defendList.push_back(strongestTerritory);
    }
    return defendList;
}


// ****************************** BenevolentPlayer ******************************

/**
 * @class Benevolent
 * @brief Represents a benevolent player strategy.
 */

/**
 * @brief Constructs a Benevolent player strategy.
 * @param player The player associated with this strategy.
 */
Benevolent::Benevolent(Player *player) {
    this->player = player;
    type=new string("benevolent");
}

/**
 * @brief Issues a specific order for the Benevolent player.
 * @param o The order to issue.
 */
void Benevolent::issueOrder(Order *o) {

}

/**
 * @brief Issues an order for the Benevolent player.
 */
void Benevolent::issueOrder() {
    // Deploy armies on the weakest countries
    int lowestArmyCountry = 999;
    string lowestArmyCountryStr = "";
    Territory *chosenTerr;
    for(int i = 0; i<player->toDefend().size(); i++) {
        if( (player->toDefend().at(i)->getNumberOfArmies()) < lowestArmyCountry) {
            lowestArmyCountry = player->toDefend().at(i)->getNumberOfArmies();
            chosenTerr = player->toDefend().at(i);
            lowestArmyCountryStr = chosenTerr->getName();

        }
    }
    Order* deployOrder = new DeployOrder(player, chosenTerr, player->getArmies() + player->getReinforcementPool());
    player->addToOrderList(deployOrder);
    cout << "Order deploying " << player->getArmies() << " armies to " << lowestArmyCountryStr << " added to " << player->getPlayerName() << "'s orderlist!" <<endl;

    // Will use cards but non harming ones (Blockade, Diplomacy, Reinforcement)
    auto playerHand = player->getHand();
    auto toPlay = playerHand->getHand();
    for(int i = 0; i< toPlay->size(); i++) {
        if(toPlay->at(i)->getType() == "Blockade") {
            Territory *targetTerr = player->getOwnedTerritories().at(i);
            string targetTerrStr = targetTerr->getName();

            auto blockadeOrder = new BlockadeOrder(player, targetTerr);
            player->addToOrderList(blockadeOrder);

            cout << "Order blockading " <<targetTerrStr << " added to " << player->getPlayerName() << "'s orderlist!" <<endl;
        }
        else if(toPlay->at(i)->getType() == "Diplomacy") {
            auto chosenPlayer = player->getCurrentGameEngine()->getPlayerList()->at(i);
            auto negotiateOrder = new NegotiateOrder(player, chosenPlayer);
            player->addToOrderList(negotiateOrder);

            cout << "Order to negotiate with " << chosenPlayer->getPlayerName() << " has been added to " << player->getPlayerName() << "'s orderlist!" <<endl;
        }
        else if(toPlay->at(i)->getType() == "Reinforcement") {
            cout << "The reinforcement card is deprecated, please use the deploy function." << endl;
        }
        else {throw runtime_error("Incorrect Card!");}
    }

}

/**
 * @brief Identifies the territories to attack for the Benevolent player.
 * @return An empty vector as Benevolent player does not attack.
 */
vector<Territory *> Benevolent::toAttack() {
    return {}; // Never advances on enemy territory
}

/**
 * @brief Identifies the territories to defend for the Benevolent player.
 * @return A vector of territories to defend.
 */
vector<Territory *> Benevolent::toDefend() {
    return vector<Territory *>(); // Only defends its territories
}


