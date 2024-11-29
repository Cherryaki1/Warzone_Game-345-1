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
    strategy = new Human(this);
}

// Parameterized constructors
Player::Player(string name) {
    ownedTerritories = {};
    playerHand = new Hand(this);        // Assuming Hand has a default constructor
    ordersList = new OrdersList();  // Assuming OrdersList has a default constructor
    numOfPlayers++;
    playerName = new string(string(name));
    armies = new int(50);
    strategy = new Human(this);
}

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
    armies = new int(*(other.armies));
}


// Assignment operator
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
        territory = nullptr;  // Set each pointer in the vector to nullptr after deletion
    }
    if(armies != nullptr) {
        delete armies;
    }
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

void Player::issueOrder() {
    strategy->issueOrder();
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

void Player::addTrucePlayer(const string& playerName) {
    trucePlayers.push_back(playerName);
}
void Player::clearTrucePlayers() {
    trucePlayers.clear();
}

bool Player::hasTruceWith(const string& playerName) const {
    for (const auto& trucePlayer : trucePlayers) {
        if (trucePlayer == playerName) {
            return true;
        }
    }
    return false;
}


// Stream insertion operator
ostream& operator<<(ostream& os, const Player& player) {
    os << "Player Name: " << *(player.playerName);
    return os;
}

void Player::setStrategy(string strat) {
    if(strat=="human") this->strategy=new Human(this);
    else if(strat=="neutral") this->strategy=new Neutral(this);
    else if(strat=="cheater") this->strategy=new Cheater(this);
    else if(strat=="aggressive") this->strategy=new Aggressive(this);
    else if(strat=="benevolent") this->strategy=new Benevolent(this);
    else throw  runtime_error("Invalid strategy entered!");
}

string Player::getStrategyType() {return strategy->getType();}

void Player::addToOrderList(Order *newOrder) {
    ordersList->addOrder(newOrder);
}
