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
    armies = new int(other.getArmies());
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
        armies = new int(other.getArmies());
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
void Player::issueOrder(const std::string& orderType) {
    Order* newOrder = nullptr;

    // Create the correct subclass of Order based on the orderType
    if (orderType == "Bomb") {
        newOrder = new BombOrder();
        cout << "Bomb order issued.\n";
    }
    else if (orderType == "Blockade") {
        newOrder = new BlockadeOrder();
        cout << "Blockade order issued.\n";
    }
    else if (orderType == "Airlift") {
        newOrder = new AirliftOrder();
        cout << "Airlift order issued.\n";
    }
    else if (orderType == "Negotiate") {
        newOrder = new NegotiateOrder();
        cout << "Negotiate order issued.\n";
    }
    else if (orderType == "Reinforcement") {
        // Player can either deploy or advance troops when playing a reinforcement card
        cout << "Reinforcement card played. Choose an action: \n";
        cout << "1. Deploy troops\n";
        cout << "2. Advance troops\n";
        int choice;
        cin >> choice;

        if (choice == 1) {
            newOrder = new DeployOrder();
            cout << "Deploy order issued." << endl;
        }
        else if (choice == 2) {
            newOrder = new AdvanceOrder();
            cout << "Advance order issued." << endl;
        }
    }
    else {
        cout << "Unknown order type: " << orderType << endl;
        return; // No order created, so return early
    }

    // Add the newly created order to the player's OrdersList
    if (newOrder != nullptr) {
        ordersList->addOrder(newOrder);
    }
}



// Method to identify territories to defend (placeholder implementation)
vector<Territory*> Player::toDefend(Map& map) {
    // Logic to identify territories to defend
    vector<Territory*> defendList;
    vector<Territory*> allTerritories = *map.getTerritories();

    srand(time(0));  // Seed for random selection

    // Randomly select 3 territories to defend (you can adjust the number)
    for (int i = 0; i < 3 && i < allTerritories.size(); ++i) {
        int randomIndex = rand() % allTerritories.size();
        defendList.push_back(allTerritories.at(randomIndex));
    }

    return defendList;
}

// Method to identify territories to attack (placeholder implementation)
vector<Territory*> Player::toAttack(Map& map) {
    // Logic to identify territories to attack'
    vector<Territory*> attackList;
    vector<Territory*> allTerritories = *map.getTerritories();

    srand(time(0));  // Seed for random selection

    // Randomly select 3 territories to attack (you can adjust the number)
    for (int i = 0; i < 3 && i < allTerritories.size(); ++i) {
        int randomIndex = rand() % allTerritories.size();
        attackList.push_back(allTerritories.at(randomIndex));
    }

    return attackList;
}

// Stream insertion operator
ostream& operator<<(ostream& os, const Player& player) {
    os << "Player Name: " << *(player.playerName);
    return os;
}
