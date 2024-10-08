#include "Map.h"
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <map>
#include <stack>
#include <set>

using namespace std;

// Territory Class Implementation
Territory::Territory() {
    pName = new string("");
    pOwner = new string("N/A");
    pContinentID = new string("");
    pNumber_of_armies = new int(0);
}

Territory::Territory(string name, string owner, string continentID, int number_of_armies) {
    pName = new string(std::move(name));
    pOwner = new string(std::move(owner));
    pContinentID = new string(std::move(continentID));
    pNumber_of_armies = new int(number_of_armies);
}

Territory::Territory(const Territory &other) {
    pName = new string(*other.pName);
    pOwner = new string(*other.pOwner);
    pContinentID = new string(*other.pContinentID);
    pNumber_of_armies = new int(*other.pNumber_of_armies);
}

Territory& Territory::operator=(const Territory &other) {
    if (this != &other) {
        *pName = *other.pName;
        *pOwner = *other.pOwner;
        *pContinentID = *other.pContinentID;
        *pNumber_of_armies = *other.pNumber_of_armies;
    }
    return *this;
}

Territory::~Territory() {
    delete pName;
    delete pOwner;
    delete pContinentID;
    delete pNumber_of_armies;
}

bool Territory::operator==(const Territory& other) const {
    return *this->pName == *other.pName;
}

bool Territory::operator<(const Territory &other) const {
    return *pName < *other.pName;  // Comparison based on name for map key
}

std::ostream& operator<<(std::ostream& os, const Territory& territory) {
    os << "> Territory: " << territory.getName()
       << ", Owner: " << territory.getOwner()
       << ", Continent: " << territory.getContinentID()
       << ", Armies: " << territory.getNumberOfArmies();
    return os;
}


// Territory: Getters and Setters
string Territory::getName() const {
    return *pName;
}

void Territory::setName(const string &name) {
    *pName = name;
}

string Territory::getOwner() const {
    return *pOwner;
}

void Territory::setOwner(const string &player) {
    *pOwner = player;
}

string Territory::getContinentID() const {
    return *pContinentID;
}

void Territory::setContinentID(const string &continentID) {
    *pContinentID = continentID;
}

int Territory::getNumberOfArmies() const {
    return *pNumber_of_armies;
}

void Territory::setNumberOfArmies(int number_of_armies) {
    *pNumber_of_armies = number_of_armies;
}

// Continent Class Implementation

Continent::Continent() {
    pContinentID = new string("");
    pCTerritories = new vector<Territory *>();
    pBonus = new int(0);
}

Continent::Continent(string continentID, int bonus) {
    pContinentID = new string(std::move(continentID));
    pCTerritories = new vector<Territory *>();
    pBonus = new int(bonus);
}

Continent::Continent(const Continent &other) {
    pContinentID = new string(*other.pContinentID);
    pCTerritories = new vector<Territory *>(*other.pCTerritories);
    pBonus = new int(*other.pBonus);
}

Continent& Continent::operator=(const Continent &other) {
    if (this != &other) {
        *pContinentID = *other.pContinentID;
        *pCTerritories = *other.pCTerritories;
        *pBonus = *other.pBonus;
    }
    return *this;
}

Continent::~Continent() {
    delete pContinentID;
    delete pCTerritories;
    delete pBonus;
}

void Continent::addTerritory(Territory* territory) {
    pCTerritories->push_back(territory);
}

std::ostream& operator<<(std::ostream& os, const Continent& continent) {
    os << "Continent: " << continent.getContinentID()
    << ", Bonus: " << continent.getBonus()
    << "\n- Territories:\n";
    for (const auto& territory : continent.getCTerritories()) {
        os << " " <<*territory << std::endl;
    }

    return os;
}

// Continent: Getters and Setters
string Continent::getContinentID() const {
    return *pContinentID;
}

void Continent::setContinentID(const string &continentID) {
    *pContinentID = continentID;
}

vector <Territory *> Continent::getCTerritories() const {
    return *pCTerritories;
}

void Continent::setCTerritories(vector<Territory *> territories) {
    *pCTerritories = std::move(territories);
}

int Continent::getBonus() const {
    return *pBonus;
}

void Continent::setBonus(int bonus) {
    *pBonus = bonus;
}

// Map Class Implementation

Map::Map() {
    pAdjList = new map<Territory*, list<Territory*>>();
    pContinents = new vector<Continent*>();
    pTerritories = new vector<Territory*>();
}

Map::~Map() {
    delete pAdjList;
    delete pContinents;
    delete pTerritories;
}

void Map::add_edge(Territory* u, Territory* v) {
    (*pAdjList)[u].push_back(v);
}

// Map: Validation

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


bool Map::isGraphConnected() {
    if (pTerritories->empty()) return true;

    set<Territory*> visited;
    DFS((*pTerritories)[0], visited);  // Start DFS from the first territory

    return visited.size() == pTerritories->size();
}

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

std::ostream& operator<<(std::ostream& os, Map& map) {
    os << "\n... MAP DETAILS ...\n";

    // Output continents
    os << "--All Continents--\n";
    for (const auto& continent : *map.getContinents()) {
        os << *continent << std::endl;  // Use the Continent's stream operator
    }

    // Output territories
    os << "\n--All Territories--\n";
    for (const auto& territory : *map.getTerritories()) {
        os << *territory << std::endl;  // Use the Territory's stream operator
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

// Map: Getters and Setters
void Map::setAdjList(map<Territory*, list<Territory*>> *adjList) {
    pAdjList = adjList;
}

map<Territory*, list<Territory*>>* Map::getAdjList() {
    return pAdjList;
}

void Map::setContinents(vector<Continent*> *continents) {
    pContinents = continents;
}

vector<Continent*>* Map::getContinents() {
    return pContinents;
}

void Map::setTerritories(vector<Territory*> *territories) {
    pTerritories = territories;
}

vector<Territory*>* Map::getTerritories() {
    return pTerritories;
}














