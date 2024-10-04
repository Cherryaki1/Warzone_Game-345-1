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
    pOwner = new string("");
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

std::ostream& Territory::operator<<(std::ostream& os, const Territory& territory) {
    os << "Territory: " << territory.getName()
       << ", Owner: " << territory.getOwner()
       << ", Continent: " << territory.getContinentID()
       << ", Armies: " << territory.getNumberOfArmies();
    return os;
}

bool Territory::operator<(const Territory &other) const {
    return *pName < *other.pName;  // Comparison based on name for map key
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
    pTerritories = new vector<Territory *>();
    pBonus = new int(0);
}

Continent::Continent(string continentID, vector<Territory *> territories, int bonus) {
    pContinentID = new string(std::move(continentID));
    pTerritories = new vector<Territory *>(std::move(territories));
    pBonus = new int(bonus);
}

Continent::Continent(const Continent &other) {
    pContinentID = new string(*other.pContinentID);
    pTerritories = new vector<Territory *>(*other.pTerritories);
    pBonus = new int(*other.pBonus);
}

Continent& Continent::operator=(const Continent &other) {
    if (this != &other) {
        *pContinentID = *other.pContinentID;
        *pTerritories = *other.pTerritories;
        *pBonus = *other.pBonus;
    }
}

Continent::~Continent() {
    delete pContinentID;
    delete pTerritories;
    delete pBonus;
}

std::ostream& operator<<(std::ostream& os, const Continent& continent) {
    os << "Continent: " << continent.getContinentID() << ", Bonus: " << continent.getBonus();
    return os;
}

// Continent: Getters and Setters
string Continent::getContinentID() const {
    return *pContinentID;
}

void Continent::setContinentID(const string &continentID) {
    *pContinentID = continentID;
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
    (*pAdjList)[v].push_back(u);
}

// Map: Validation

void DFS(Territory* start, set<Territory*> &visited, map<Territory*, list<Territory*>> adjList) {
    stack<Territory*> s;
    s.push(start);

    while (!s.empty()) {
        Territory* current = s.top();
        s.pop();

        if (visited.find(current) == visited.end()) {
            visited.insert(current);
            for (Territory* neighbor : adjList[current]) {
                if (visited.find(neighbor) == visited.end()) {
                    s.push(neighbor);
                }
            }
        }
    }
}

bool isGraphConnected(Map &map) {
    if (map.getTerritories()->empty()) return true;

    set<Territory*> visited;
    DFS((*map.getTerritories())[0], visited, *map.getAdjList());

    return visited.size() == map.getTerritories()->size();
}

bool isContinentConnected(Continent* continent, Map &map) {
    if (continent->(continentTerritories()->size)) return true;

    set<Territory*> visited;
    DFS(continent->territories[0], visited);

    // Check if all territories in the continent were visited
    for (Territory* territory : continent->territories) {
        if (visited.find(territory) == visited.end()) {
            return false;  // A territory was not reachable, subgraph is not connected
        }
    }
    return true;
}

bool hasUniqueContinent() {

}

bool Map::validate() const {
    // DFS
    return false;
}

std::ostream& Map::operator<<(std::ostream& os, Map& map) {
    os << "Map Details:\n";

    // Output continents
    os << "Continents:\n";
    for (const auto& continent : map.getContinents()) {
        os << *continent << std::endl;  // Use the Continent's stream operator
    }

    // Output territories
    os << "\nTerritories:\n";
    for (const auto& territory : map.getTerritories()) {
        os << *territory << std::endl;  // Use the Territory's stream operator
    }

    // Output adjacency list
    os << "\nAdjacency List:\n";
    for (const auto& entry : map.getAdjList()) {
        os << entry.first->name << " -> ";
        for (const auto& neighbor : entry.second) {
            os << neighbor->name << " ";
        }
        os << std::endl;
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














