/**
 * @file Player.cpp
 * @brief This file contains the class and function implementations for the Player class.
 * 
 * This file is part of the Warzone Game Team Project for COMP 345 - D (Advanced Program Design, C++).
 * It includes the implementation of the Player class, which represents players in the game,
 * and manages their territories, cards, and orders.
 * 
 * Team Members (Team 36):
 * - Amir Vala Khalilzadeh (40253211)
 * - Abdulah Ghulam Ali (40281857)
 * - Arturo Sanchez Escobar (40283236)
 * - Gregory Lajoie (40276231)
 * - Botao Yang (40213554)
 */

#include "Player.h"
#include "Orders/Orders.h"
#include "Cards/Cards.h"
#include "Map/Map.h"
#include "Map/MapDriver.h"
#include "Map/MapLoader.h"

using namespace std;

int Player::numOfPlayers = 0;

//**************************PLAYER**************************

/**
 * @class Player
 * @brief Represents a player in the game.
 */

/**
 * @brief Default constructor for the Player class.
 */
Player::Player() {
    ownedTerritories = {};
    playerHand = new Hand(this);        // Assuming Hand has a default constructor
    ordersList = new OrdersList();  // Assuming OrdersList has a default constructor
    numOfPlayers++;
    playerName = new string("Player " + to_string(numOfPlayers));
    armies = new int(50);
    strategy = new Human(this);
}

/**
 * @brief Parameterized constructor for the Player class.
 * @param name The name of the player.
 * @param engine Pointer to the game engine.
 */
Player::Player(string name, GameEngine* engine) {
    ownedTerritories = {};
    playerHand = new Hand(this);        // Assuming Hand has a default constructor
    ordersList = new OrdersList();  // Assuming OrdersList has a default constructor
    numOfPlayers++;
    playerName = new string(string(name));
    armies = new int(50);
    strategy = new Human(this);
    pEngine = engine;
}

/**
 * @brief Parameterized constructor for the Player class.
 * @param name The name of the player.
 */
Player::Player(string name) {
    ownedTerritories = {};
    playerHand = new Hand(this);        // Assuming Hand has a default constructor
    ordersList = new OrdersList();  // Assuming OrdersList has a default constructor
    numOfPlayers++;
    playerName = new string(string(name));
    armies = new int(50);
    strategy = new Human(this);
}

/**
 * @brief Parameterized constructor for the Player class.
 * @param initialHand Pointer to the initial hand of cards.
 * @param initialTerritories Reference to the vector of initial territories.
 * @param name The name of the player.
 */
Player::Player(Hand *initialHand, vector<Territory *> &initialTerritories, string name)
{
    ownedTerritories = initialTerritories;
    playerHand = initialHand;
    ordersList = new OrdersList();
    numOfPlayers++;
    playerName = new string(string(name));
    armies = new int(50);
    strategy = new Human(this);
}

/**
 * @brief Copy constructor for the Player class.
 * @param other The Player object to copy from.
 */
Player::Player(const Player& other) {
    // Perform a deep copy of each territory pointer in ownedTerritories
    for (auto& territory : other.ownedTerritories) {
        ownedTerritories.push_back(new Territory(*territory));  // Assuming Territory has a copy constructor
    }
    playerHand = new Hand(*(other.playerHand));        // Assuming Hand has a copy constructor
    ordersList = new OrdersList(*(other.ordersList));  // Assuming OrdersList has a copy constructor
    numOfPlayers++;
    playerName = new string(*(other.playerName));
    armies = new int(*(other.armies));
}

/**
 * @brief Assignment operator for the Player class.
 * @param other The Player object to assign from.
 * @return A reference to the assigned Player object.
 */
Player& Player::operator=(const Player& other) {
    if (this != &other) { // Check for self-assignment
        // Clean up existing resources
        delete playerName;
        delete playerHand;
        delete ordersList;
        for (auto& territory : ownedTerritories) {
            delete territory;
        }
        ownedTerritories.clear();

        // Perform deep copy
        playerName = new string(*(other.playerName));
        playerHand = new Hand(*(other.playerHand));        // Assuming Hand has a copy constructor
        ordersList = new OrdersList(*(other.ordersList));  // Assuming OrdersList has a copy constructor
        armies = new int(*(other.armies));  // Copy armies value        // Deep copy of each territory pointer in ownedTerritories
        for (auto& territory : other.ownedTerritories) {
            ownedTerritories.push_back(new Territory(*territory));  // Assuming Territory has a copy constructor
        }
    }
    return *this;
}

/**
 * @brief Destructor for the Player class.
 */
Player::~Player() {
    delete playerName;
    playerName = nullptr;  // Set to nullptr after deletion

    delete playerHand;
    playerHand = nullptr;  // Set to nullptr after deletion

    delete ordersList;
    ordersList = nullptr;  // Set to nullptr after deletion

    for (auto& territory : ownedTerritories) {
        //delete territory;
        territory = nullptr;  // Set each pointer in the vector to nullptr after deletion
    }
    if(armies != nullptr) {
        delete armies;
    }

    delete strategy;
    strategy= nullptr;
}

/**
 * @brief Sets the player's name.
 * @param name The name to set.
 */
void Player::setPlayerName(string name) {
    *playerName = name;
}

/**
 * @brief Gets the player's name.
 * @return The player's name.
 */
string Player::getPlayerName() const {
    return *playerName;
}

/**
 * @brief Gets the player's hand.
 * @return A pointer to the player's hand.
 */
Hand* Player::getHand() const {
    return playerHand;
}

/**
 * @brief Gets the player's orders list.
 * @return A pointer to the player's orders list.
 */
OrdersList* Player::getOrdersList() const {
    return ordersList;
}

/**
 * @brief Sets the number of armies the player has.
 * @param arm Pointer to the number of armies.
 */
void Player::setArmies(int* arm) {
    armies = arm;
}

/**
 * @brief Gets the number of armies the player has.
 * @return The number of armies.
 */
int Player::getArmies() const {
    if(armies != nullptr) {
        return *armies;
    }else {
        return 0;
    }
}

/**
 * @brief Gets the player's reinforcement pool.
 * @return The number of units in the reinforcement pool.
 */
int Player::getReinforcementPool()
{
    return reinforcementPool;
}

/**
 * @brief Sets the player's reinforcement pool.
 * @param numUnits The number of units to set.
 */
void Player::setReinforcementPool(int numUnits)
{
    reinforcementPool = numUnits;
}

/**
 * @brief Gets the territories owned by the player.
 * @return A vector of pointers to the owned territories.
 */
vector<Territory *> Player::getOwnedTerritories() const {
    return ownedTerritories;
}

/**
 * @brief Adds a territory to the player's list of owned territories.
 * @param territory The territory to add.
 */
void Player::addOwnedTerritory(Territory *territory){
    ownedTerritories.push_back(territory);
}

/**
 * @brief Removes a territory from the player's list of owned territories.
 * @param territory The territory to remove.
 * @return A pointer to the removed territory.
 */
Territory* Player::removeOwnedTerritory(const Territory* territory) {
    for (auto it = ownedTerritories.begin(); it != ownedTerritories.end(); ++it) {
        if (*it == territory) {
            Territory* poppedTerritory = *it;
            ownedTerritories.erase(it);
            return poppedTerritory;
        }
    }
    return nullptr;
}

/**
 * @brief Checks if the player has a card of a certain type.
 * @param cardType The type of card to check for.
 * @return True if the player has a card of the specified type, false otherwise.
 */
bool Player::hasCard(string cardType) {
    vector<Card*>* hand = playerHand->getHand();
    for (Card* card : *hand) {
        if (card->getType() == cardType) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Issues an order for the player.
 * @param newOrder The order to issue.
 */
void Player::issueOrder(Order* newOrder) {
    if (newOrder != nullptr) {
        ordersList->addOrder(newOrder);
        cout << newOrder->getOrderType() << " order issued." << endl;
    } else {
        cout << "Error: Cannot issue a null order." << endl;
    }
}

/**
 * @brief Issues an order for the player based on their strategy.
 */
void Player::issueOrder() {
    strategy->issueOrder();
}

/**
 * @brief Identifies the territories to defend.
 * @return A vector of pointers to the territories to defend.
 */
vector<Territory*> Player::toDefend() {
    // Logic to identify territories to defend
    vector<Territory*> defendList = getOwnedTerritories();
    return defendList;
}

/**
 * @brief Identifies the territories to attack.
 * @return A vector of pointers to the territories to attack.
 */
vector<Territory*> Player::toAttack() {
    // Logic to identify territories to attack'
    vector<Territory *> attackList;
    for (auto territory : getOwnedTerritories())
    {
        for (auto neighbor : territory->adjacentTerritories)
        {
            if (neighbor->getOwner()->getPlayerName().compare(*playerName) != 0)
            {
                attackList.push_back(neighbor);
            }
        }
    }

    return attackList;
}

/**
 * @brief Adds a player to the truce list.
 * @param playerName The name of the player to add.
 */
void Player::addTrucePlayer(const string& playerName) {
    trucePlayers.push_back(playerName);
}

/**
 * @brief Clears the truce list.
 */
void Player::clearTrucePlayers() {
    trucePlayers.clear();
}

/**
 * @brief Checks if the player has a truce with another player.
 * @param playerName The name of the other player.
 * @return True if there is a truce, false otherwise.
 */
bool Player::hasTruceWith(const string& playerName) const {
    for (const auto& trucePlayer : trucePlayers) {
        if (trucePlayer == playerName) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Stream insertion operator for displaying a player.
 * @param os The output stream.
 * @param player The player to display.
 * @return The output stream.
 */
ostream& operator<<(ostream& os, const Player& player) {
    os << "Player Name: " << *(player.playerName);
    return os;
}

/**
 * @brief Sets the player's strategy.
 * @param strat The strategy to set.
 */
void Player::setStrategy(string strat) {
    if(strat=="human") this->strategy=new Human(this);
    else if(strat=="neutral") this->strategy=new Neutral(this);
    else if(strat=="cheater") this->strategy=new Cheater(this);
    else if(strat=="aggressive") this->strategy=new Aggressive(this);
    else if(strat=="benevolent") this->strategy=new Benevolent(this);
    else throw  runtime_error("Invalid strategy entered!");
}

/**
 * @brief Gets the type of the player's strategy.
 * @return The type of the strategy.
 */
string Player::getStrategyType() {return strategy->getType();}

/**
 * @brief Adds an order to the player's orders list.
 * @param newOrder The order to add.
 */
void Player::addToOrderList(Order *newOrder) {
    ordersList->addOrder(newOrder);
}

/**
 * @brief Gets the current game engine.
 * @return A pointer to the current game engine.
 */
GameEngine *Player::getCurrentGameEngine() {
    return pEngine;
}
