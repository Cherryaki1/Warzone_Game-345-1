#include "Player.h"
#include "Orders/Orders.h"
#include "Cards/Cards.h"
#include "Map/Map.h"

using namespace std;

// Default constructor
Player::Player() {
    playerName = new string("Unknown");
    //playerHand = new Hand();        // Assuming Hand has a default constructor
    //ordersList = new Orderslist();  // Assuming Orderslist has a default constructor
}

// Overloaded constructor
Player::Player(string name) {
    playerName = new string(name);
    //playerHand = new Hand();        // Assuming Hand has a default constructor
    //ordersList = new Orderslist();  // Assuming Orderslist has a default constructor
}

// Copy constructor
Player::Player(const Player& other) {
    playerName = new string(*(other.playerName));
    //playerHand = new Hand(*(other.playerHand));        // Assuming Hand has a copy constructor
    //ordersList = new Orderslist(*(other.ordersList));  // Assuming Orderslist has a copy constructor
}

// Assignment operator
Player& Player::operator=(const Player& other) {
    if (this != &other) { // Check for self-assignment
        // Clean up existing resources
        delete playerName;
        //delete playerHand;
        //delete ordersList;

        // Perform deep copy
        playerName = new string(*(other.playerName));
        //playerHand = new Hand(*(other.playerHand));        // Assuming Hand has a copy constructor
        //ordersList = new Orderslist(*(other.ordersList));  // Assuming Orderslist has a copy constructor
    }
    return *this;
}

// Destructor
Player::~Player() {
    delete playerName;
    //delete playerHand;
    //delete ordersList;
}

// Method to set player name
void Player::setPlayerName(string name) {
    *playerName = name;
}

// Method to get player name
string Player::getPlayerName() const {
    return *playerName;
}

// Method for issuing an order (placeholder implementation)
void Player::issueOrder() {
    // Logic to issue an order
}

// Method to identify territories to defend (placeholder implementation)
void Player::toDefend() {
    // Logic to identify territories to defend
}

// Method to identify territories to attack (placeholder implementation)
void Player::toAttack() {
    // Logic to identify territories to attack
}

// Stream insertion operator
ostream& operator<<(ostream& os, const Player& player) {
    os << "Player Name: " << *(player.playerName);
    return os;
}
