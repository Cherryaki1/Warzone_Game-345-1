/**
 * @file Map.cpp
 * @brief This file contains the class and function implementations for Territory, Continent, and Map.
 * 
 * This file is part of the Warzone Game Team Project for COMP 345 - D (Advanced Program Design, C++).
 * It includes the implementation of the Territory class, which represents territories in the game,
 * as well as the Continent and Map classes for managing the game's map structure.
 * 
 * Team Members (Team 36):
 * - Amir Vala Khalilzadeh (40253211)
 * - Abdulah Ghulam Ali (40281857)
 * - Arturo Sanchez Escobar (40283236)
 * - Gregory Lajoie (40276231)
 * - Botao Yang (40213554)
 */

#include "Map.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <map>
#include <stack>
#include <set>

using namespace std;

//**************************TERRITORY**************************

/**
 * @class Territory
 * @brief Represents a territory in the game.
 */

/**
 * @brief Default constructor for the Territory class.
 */
Territory::Territory() {
    pName = new string("");
    pOwner = nullptr;
    pContinentID = new string("");
    pNumber_of_armies = new int(0);
}

/**
 * @brief Parameterized constructor for the Territory class.
 * @param name The name of the territory.
 * @param owner The owner of the territory.
 * @param continentID The ID of the continent the territory belongs to.
 * @param number_of_armies The number of armies in the territory.
 */
Territory::Territory(string name, Player* owner, string continentID, int number_of_armies) {
    pName = new string(std::move(name));
    pOwner = owner;
    pContinentID = new string(std::move(continentID));
    pNumber_of_armies = new int(number_of_armies);
}

/**
 * @brief Copy constructor for the Territory class.
 * @param other The Territory object to copy from.
 */
Territory::Territory(const Territory &other) {
    pName = new string(*other.pName);
    pOwner = new Player(*other.pOwner);
    pContinentID = new string(*other.pContinentID);
    pNumber_of_armies = new int(*other.pNumber_of_armies);
}

/**
 * @brief Assignment operator for the Territory class.
 * @param other The Territory object to assign from.
 * @return A reference to the assigned Territory object.
 */
Territory& Territory::operator=(const Territory &other) {
    if (this != &other) {
        *pName = *other.pName;
        *pOwner = *other.pOwner;
        *pContinentID = *other.pContinentID;
        *pNumber_of_armies = *other.pNumber_of_armies;
    }
    return *this;
}

/**
 * @brief Destructor for the Territory class.
 */
Territory::~Territory() {
    delete pName;
    delete pOwner;
    delete pContinentID;
    delete pNumber_of_armies;
}

bool Territory::operator==(const Territory& other) const {
    return pName == other.pName && pOwner == other.pOwner && pContinentID == other.pContinentID;
}

bool Territory::operator<(const Territory &other) const {
    return *pName < *other.pName;  // Comparison based on name for map key
}

/**
 * @brief Stream insertion operator for displaying a territory.
 * @param os The output stream.
 * @param territory The territory to display.
 * @return The output stream.
 */
std::ostream& operator<<(std::ostream& os, const Territory& territory) {
    string ownerName = "";
    if(territory.pOwner != nullptr){ ownerName=territory.getOwner()->getPlayerName();}
    os << "> Territory: " << territory.getName()
       << ", Owner: " << ownerName
       << ", Continent: " << territory.getContinentID()
       << ", Armies: " << territory.getNumberOfArmies();
    return os;
}

/**
 * @brief Gets the name of the territory.
 * @return The name of the territory.
 */
string Territory::getName() const {
    return *pName;
}

/**
 * @brief Sets the name of the territory.
 * @param name The name to set.
 */
void Territory::setName(const string &name) {
    *pName = name;
}

/**
 * @brief Gets the owner of the territory.
 * @return A pointer to the owner of the territory.
 */
Player* Territory::getOwner() const {
    return pOwner;
}

/**
 * @brief Sets the owner of the territory.
 * @param owner A pointer to the owner to set.
 */
void Territory::setOwner(Player* owner) {
    pOwner = owner;
}

/**
 * @brief Gets the continent ID of the territory.
 * @return The continent ID of the territory.
 */
string Territory::getContinentID() const {
    return *pContinentID;
}

/**
 * @brief Sets the continent ID of the territory.
 * @param continentID The continent ID to set.
 */
void Territory::setContinentID(const string &continentID) {
    *pContinentID = continentID;
}

/**
 * @brief Gets the number of armies in the territory.
 * @return The number of armies in the territory.
 */
int Territory::getNumberOfArmies() const {
    return *pNumber_of_armies;
}

/**
 * @brief Sets the number of armies in the territory.
 * @param number_of_armies The number of armies to set.
 */
void Territory::setNumberOfArmies(int number_of_armies) {
    *pNumber_of_armies = number_of_armies;
}

/**
 * @brief Checks if the territory is adjacent to another territory.
 * @param other The other territory to check adjacency with.
 * @return True if the territories are adjacent, false otherwise.
 */
bool Territory::isAdjacent(Territory* other) {
    for (const auto& territory : adjacentTerritories) {
        if (territory == other) {
            return true;
        }
    }
    return false;
}


//**************************CONTINENT**************************

/**
 * @class Continent
 * @brief Represents a continent in the game.
 */

/**
 * @brief Default constructor for the Continent class.
 */
Continent::Continent() {
    pContinentID = new string("");
    pCTerritories = new vector<Territory *>();
    pBonus = new int(0);
}

/**
 * @brief Parameterized constructor for the Continent class.
 * @param continentID The ID of the continent.
 * @param bonus The bonus of the continent.
 */
Continent::Continent(string continentID, int bonus) {
    pContinentID = new string(std::move(continentID));
    pCTerritories = new vector<Territory *>();
    pBonus = new int(bonus);
}

/**
 * @brief Copy constructor for the Continent class.
 * @param other The Continent object to copy from.
 */
Continent::Continent(const Continent &other) {
    pContinentID = new string(*other.pContinentID);
    if(!(other.pCTerritories == nullptr)) {
        pCTerritories = new vector<Territory *>(*other.pCTerritories);
    }
    pBonus = new int(*other.pBonus);
}

/**
 * @brief Assignment operator for the Continent class.
 * @param other The Continent object to assign from.
 * @return A reference to the assigned Continent object.
 */
Continent& Continent::operator=(const Continent &other) {
    if (this != &other) {
        *pContinentID = *other.pContinentID;
        *pCTerritories = *other.pCTerritories;
        *pBonus = *other.pBonus;
    }
    return *this;
}

/**
 * @brief Destructor for the Continent class.
 */
Continent::~Continent() {
    delete pContinentID;
    delete pCTerritories;
    delete pBonus;
}

/**
 * @brief Adds a territory to the continent.
 * @param territory The territory to add.
 */
void Continent::addTerritory(Territory* territory) {
    pCTerritories->push_back(territory);
}

/**
 * @brief Stream insertion operator for displaying a continent.
 * @param os The output stream.
 * @param continent The continent to display.
 * @return The output stream.
 */
std::ostream& operator<<(std::ostream& os, const Continent& continent) {
    os << "Continent: " << continent.getContinentID()
    << ", Bonus: " << continent.getBonus()
    << "\n- Territories:\n";
    for (const auto& territory : continent.getCTerritories()) {
        os << " " <<*territory << std::endl;
    }

    return os;
}

/**
 * @brief Gets the continent ID.
 * @return The continent ID.
 */
string Continent::getContinentID() const {
    return *pContinentID;
}

/**
 * @brief Sets the continent ID.
 * @param continentID The continent ID to set.
 */
void Continent::setContinentID(const string &continentID) {
    *pContinentID = continentID;
}

/**
 * @brief Gets the territories in the continent.
 * @return A vector of pointers to the territories in the continent.
 */
vector <Territory *> Continent::getCTerritories() const {
    return *pCTerritories;
}

/**
 * @brief Sets the territories in the continent.
 * @param territories The territories to set.
 */
void Continent::setCTerritories(vector<Territory *> territories) {
    *pCTerritories = std::move(territories);
}

/**
 * @brief Gets the bonus of the continent.
 * @return The bonus of the continent.
 */
int Continent::getBonus() const {
    return *pBonus;
}

/**
 * @brief Sets the bonus of the continent.
 * @param bonus The bonus to set.
 */
void Continent::setBonus(int bonus) {
    *pBonus = bonus;
}

//**************************MAP**************************

/**
 * @class Map
 * @brief Represents the map of the game.
 */

/**
 * @brief Default constructor for the Map class.
 */
Map::Map() {
    pContinents = new vector<Continent*>();
    pTerritories = new vector<Territory*>();
    pAdjList = new map<Territory*, list<Territory*>>();
}

/**
 * @brief Destructor for the Map class.
 */
Map::~Map() {
    if (pContinents != nullptr) {
        delete pContinents;
        pContinents = nullptr;
    }

    if (pTerritories != nullptr) {
        delete pTerritories;
        pTerritories = nullptr;
    }

    if (pAdjList != nullptr) {
        delete pAdjList;
        pAdjList = nullptr;
    }
}

/**
 * @brief Adds an edge between two territories.
 * @param u The first territory.
 * @param v The second territory.
 */
void Map::add_edge(Territory* u, Territory* v) {
    (*pAdjList)[u].push_back(v);
}


/**
 * @brief Performs a depth-first search (DFS) on the map.
 * @param start The starting territory.
 * @param visited The set of visited territories.
 */
void Map::DFS(Territory* start, set<Territory*>& visited) {
    map<Territory*, list<Territory*>> adjListCopy = *pAdjList;
    stack<Territory*> s;
    s.push(start);
    int count = 0;

    while (!s.empty()) {
        Territory* current = s.top(); // Get the current territory
        s.pop(); // Remove it from the stack

        // Check if we have already visited this territory
        if (visited.find(current) == visited.end()) {
            visited.insert(current); // Mark it as visited
            // TO SEE VISITED DFS: std::cout << ++count << " Visited: " << current->getName() << std::endl;

            // Check if current is a key in the adjacency list
            if (adjListCopy.find(current) != adjListCopy.end()) {
                const auto& neighbors = adjListCopy[current];

                for (Territory* neighbor : neighbors) {
                    // Push only unvisited neighbors onto the stack
                    if (visited.find(neighbor) == visited.end()) {
                        s.push(neighbor);
                    }
                }
            } else {
                std::cout << "No neighbors found for: " << current->getName() << std::endl;
            }
        }
    }
}

/**
 * @brief Performs a depth-first search (DFS) on a continent.
 * @param start The starting territory.
 * @param visited The set of visited territories.
 * @param continent The continent to perform DFS on.
 */
void Map::DFSContinent(Territory* start, set<Territory*>& visited, Continent* continent) {
    map<Territory*, list<Territory*>> adjListCopy = *pAdjList;
    stack<Territory*> s;
    s.push(start);
    int count = 0; // Initialize count

    while (!s.empty()) {
        Territory* current = s.top(); // Get the current territory
        s.pop(); // Remove it from the stack

        // Check if we have already visited this territory and if it belongs to the continent
        if (visited.find(current) == visited.end() && current->getContinentID() == continent->getContinentID()) {
            visited.insert(current); // Mark it as visited
            // TO SEE VISITED DFS: std::cout << ++count << " Visited: " << current->getName() << std::endl;

            // Check if current is a key in the adjacency list
            if (adjListCopy.find(current) != adjListCopy.end()) {
                const auto& neighbors = adjListCopy[current];

                for (const auto& neighbor : neighbors) {
                    // Push only unvisited neighbors that belong to the same continent onto the stack
                    if (visited.find(neighbor) == visited.end() && neighbor->getContinentID() == continent->getContinentID()) {
                        s.push(neighbor);
                    }
                }
            } else {
                std::cout << "No neighbors found for: " << current->getName() << std::endl;
            }
        }
    }
}


/**
 * @brief Checks if the map is connected.
 * @return True if the map is connected, false otherwise.
 */
bool Map::isGraphConnected() {
    if (pTerritories->empty()) return true;

    set<Territory*> visited;
    DFS((*pTerritories)[0], visited);  // Start DFS from the first territory

    return visited.size() == pTerritories->size();
}

/**
 * @brief Checks if a continent is connected.
 * @param continent The continent to check.
 * @return True if the continent is connected, false otherwise.
 */
bool Map::isContinentConnected(Continent* continent) {
    // Get territories for the continent
    vector<Territory*> territories = continent->getCTerritories();
    // DFS DEBUG: cout << "\n" << territories.size() << " - " << continent->getContinentID() << "\n";
    if (territories.empty()) return true;

    set<Territory*> visited;
    DFSContinent(territories[0], visited, continent);  // Start DFS within the continent

    // Check if all territories in the continent were visited
    return visited.size() == territories.size();
}

/**
 * @brief Checks if each territory belongs to only one continent.
 * @return True if each territory belongs to only one continent, false otherwise.
 */
bool Map::hasUniqueContinent() {
    set<Territory*> uniqueTerritories; // Set to track territories that have already been assigned

    for (Continent* continent : *pContinents) {
        vector<Territory*> territories = continent->getCTerritories();
        for (Territory* territory : territories) {
            if (uniqueTerritories.find(territory) != uniqueTerritories.end()) {
                return false;  // Duplicate territory found
            }
            uniqueTerritories.insert(territory);
        }
    }
    return true;
}

/**
 * @brief Validates the map.
 * @return True if the map is valid, false otherwise.
 */
bool Map::validate() {
    // 1. Check if the map is a connected graph
    if (!isGraphConnected()) {
        std::cout << "!! MAP IS NOT CONNECTED !!" << std::endl;
        return false;
    }

    // 2. Check if each continent forms a connected subgraph
    for (Continent* continent : *pContinents) {
        if (!isContinentConnected(continent)) {
            std::cout << "!! CONTINENT " << continent->getContinentID() << " IS NOT CONNECTED !!" << std::endl;
            return false;
        }
    }

    // 3. Ensure each territory belongs to exactly one continent
    if (!hasUniqueContinent()) {
        std::cout << "!! A TERRITORY BELONGS TO MULTIPLE CONTINENTS !!" << std::endl;
        return false;
    }

    // If all checks pass
    return true;
}

/**
 * @brief Stream insertion operator for displaying a map.
 * @param os The output stream.
 * @param map The map to display.
 * @return The output stream.
 */
std::ostream& operator<<(std::ostream& os, Map& map) {
    os << "\n... MAP DETAILS ...\n";

    // Output continents
    os << "--All Continents and their Territories--\n";
    for (const auto& continent : *map.getContinents()) {
        os << *continent << std::endl;  // Use the Continent's stream operator
    }

    // Output adjacency list
    os << "\n--Adjacency List--\n";
    for (const auto& entry : *map.getAdjList()) {  // Dereference to get the map
        os << entry.first->getName() << " -> ";
        for (const auto& neighbor : entry.second) {
            os << neighbor->getName() << ", ";
        }
        os << std::endl;  // Move to the next line after listing neighbors
    }
    return os;
}

/**
 * @brief Sets the adjacency list of the map.
 * @param adjList The adjacency list to set.
 */
void Map::setAdjList(map<Territory*, list<Territory*>> *adjList) {
    pAdjList = adjList;
}

/**
 * @brief Gets the adjacency list of the map.
 * @return A pointer to the adjacency list.
 */
map<Territory*, list<Territory*>>* Map::getAdjList() {
    return pAdjList;
}

/**
 * @brief Sets the continents in the map.
 * @param continents The continents to set.
 */
void Map::setContinents(vector<Continent*> *continents) {
    pContinents = continents;
}

/**
 * @brief Gets the continents in the map.
 * @return A pointer to the vector of continents.
 */
vector<Continent*>* Map::getContinents() {
    return pContinents;
}

/**
 * @brief Sets the territories in the map.
 * @param territories The territories to set.
 */
void Map::setTerritories(vector<Territory*> *territories) {
    pTerritories = territories;
}

/**
 * @brief Gets the territories in the map.
 * @return A pointer to the vector of territories.
 */
vector<Territory*>* Map::getTerritories() {
    return pTerritories;
}














