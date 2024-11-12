// Abdulah Ghulam Ali (40281857), Team 36
// COMP 345 - D (Advanced Program Design, C++)
// Warzone Game Team Project - Assignment 1
// October 4, 2024
// *******************************************
// This is a cpp file for Part 2 of the assignment.
// It contains the class and function implementations for Player

#include "Player.h"
#include "Orders/Orders.h"
#include "Cards/Cards.h"
#include "Map/Map.h"
#include "Map/MapDriver.h"
#include "Map/MapLoader.h"

using namespace std;

int Player::numOfPlayers = 0;

// Default constructor
Player::Player() {
    ownedTerritories = {};
    playerHand = new Hand(this);        // Assuming Hand has a default constructor
    ordersList = new OrdersList();  // Assuming OrdersList has a default constructor
    numOfPlayers++;
    playerName = new string("Player " + to_string(numOfPlayers));
    armies = new int(50);
}

// Parameterized constructors
Player::Player(string name) {
    ownedTerritories = {};
    playerHand = new Hand(this);        // Assuming Hand has a default constructor
    ordersList = new OrdersList();  // Assuming OrdersList has a default constructor
    numOfPlayers++;
    playerName = new string(string(name));
    armies = new int(50);
}

Player::Player(Hand *initialHand, vector<Territory *> &initialTerritories, string name)
{
    ownedTerritories = initialTerritories;
    playerHand = initialHand;
    ordersList = new OrdersList();
    numOfPlayers++;
    playerName = new string(string(name));
    armies = new int(50);
}

// Copy constructor
Player::Player(const Player& other) {
    // Perform a deep copy of each territory pointer in ownedTerritories
    for (auto& territory : other.ownedTerritories) {
        ownedTerritories.push_back(new Territory(*territory));  // Assuming Territory has a copy constructor
    }
    playerHand = new Hand(*(other.playerHand));        // Assuming Hand has a copy constructor
    ordersList = new OrdersList(*(other.ordersList));  // Assuming OrdersList has a copy constructor
    numOfPlayers++;
    playerName = new string(*(other.playerName));
    armies = new int(*(other.armies));  // Directly copy the value from other.armies
}



// Assignment operator
Player& Player::operator=(const Player& other) {
    if (this != &other) { // Check for self-assignment
        // Clean up existing resources
        delete playerName;
        delete playerHand;
        delete ordersList;
        delete armies;

        if (armies != nullptr) {
            delete armies;
        }

        for (auto& territory : ownedTerritories) {
            delete territory;
        }
        ownedTerritories.clear();

        // Perform deep copy
        playerName = new string(*(other.playerName));
        playerHand = new Hand(*(other.playerHand));        // Assuming Hand has a copy constructor
        ordersList = new OrdersList(*(other.ordersList));  // Assuming OrdersList has a copy constructor
        armies = new int(*(other.armies));  // Copy armies value

        // Deep copy of each territory pointer in ownedTerritories
        for (auto& territory : other.ownedTerritories) {
            ownedTerritories.push_back(new Territory(*territory));  // Assuming Territory has a copy constructor
        }
    }
    return *this;
}


// Destructor
Player::~Player() {
    delete playerName;
    playerName = nullptr;  // Set to nullptr after deletion

    delete playerHand;
    playerHand = nullptr;  // Set to nullptr after deletion

    delete ordersList;
    ordersList = nullptr;  // Set to nullptr after deletion

    for (auto& territory : ownedTerritories) {
        delete territory;
    }
    ownedTerritories.clear();  // Clear the vector after deleting its contents

    delete armies;  // Delete armies pointer
    armies = nullptr;  // Set to nullptr after deletion
}


// Method to set player name
void Player::setPlayerName(string name) {
    *playerName = name;
}

// Method to get player name
string Player::getPlayerName() const {
    return *playerName;
}

// Method to get player hand
Hand* Player::getHand() const {
    return playerHand;
}

OrdersList* Player::getOrdersList() const {
    return ordersList;
}
void Player::setArmies(int* arm) {
    if (armies != nullptr) {
        delete armies; // Free existing memory
    }
    armies = arm;
}
int Player::getArmies() const {
    return *armies;
}

int Player::getReinforcementPool()
{
    return reinforcementPool;
}

void Player::setReinforcementPool(int numUnits)
{
    reinforcementPool = numUnits;
}

vector<Territory *> Player::getOwnedTerritories() const {
    return ownedTerritories;
}

// Pushes a new territory onto the player's list of owned territories.
void Player::addOwnedTerritory(Territory *territory){
    ownedTerritories.push_back(territory);
}

// Pops an existing territory from the player's list of owned territories. Returns its reference.
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

// Method to check if player has a card of a certain type
bool Player::hasCard(string cardType) {
    vector<Card*>* hand = playerHand->getHand();
    for (Card* card : *hand) {
        if (card->getType() == cardType) {
            return true;
        }
    }
    return false;
}

// Method for issuing an order (placeholder implementation)
void Player::issueOrder(Order* newOrder) {
    if (newOrder != nullptr) {
        ordersList->addOrder(newOrder);
        cout << newOrder->getOrderType() << " order issued." << endl;
    } else {
        cout << "Error: Cannot issue a null order." << endl;
    }
}

// Method to identify territories to defend (placeholder implementation)
vector<Territory*> Player::toDefend() {
    // Logic to identify territories to defend
    vector<Territory*> defendList = getOwnedTerritories();
    return defendList;
}

// Method to identify territories to attack (placeholder implementation)
vector<Territory*> Player::toAttack() {
    // Logic to identify territories to attack'
    vector<Territory *> attackList;
    for (auto territory : getOwnedTerritories())
    {
        for (auto neighbor : territory->adjacentTerritories)
        {
            if (neighbor->getOwner().compare(*playerName) != 0)
            {
                attackList.push_back(neighbor);
            }
        }
    }

    return attackList;
}

// Stream insertion operator
ostream& operator<<(ostream& os, const Player& player) {
    os << "Player Name: " << *(player.playerName);
    return os;
}
