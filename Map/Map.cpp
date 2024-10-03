#include "Map.h"
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <map>
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

// Getters and Setters
string Territory::getName() const {
    return *pName;
}

string Territory::getOwner() const {
    return *pOwner;
}

string Territory::getContinentID() const {
    return *pContinentID;
}

int Territory::getNumberOfArmies() const {
    return *pNumber_of_armies;
}

void Territory::setPlayer(const string &player) {
    *pOwner = player;
}

void Territory::setNumberOfArmies(int number_of_armies) {
    *pNumber_of_armies = number_of_armies;
}

bool Territory::operator<(const Territory &other) const {
    return *pName < *other.pName;  // Comparison based on name for map key
}
// Continent Class Implementation

Continent::Continent() {
    pContinentName = new string("");
    pBonus = new int(0);
}

Continent::Continent(string continentName, int bonus) {
    pContinentName = new string(std::move(continentName));
    pBonus = new int(bonus);
}

Continent::Continent(const Continent &other) {
    pContinentName = new string(*other.pContinentName);
    pBonus = new int(*other.pBonus);
}

Continent& Continent::operator=(const Continent &other) {
    if (this != &other) {
        *pContinentName = *other.pContinentName;
        *pBonus = *other.pBonus;
    }
}

Continent::~Continent() {
    delete pContinentName;
    delete pBonus;
}

// Getters and Setters
string Continent::getContinentName() const {
    return *pContinentName;
}

int Continent::getBonus() const {
    return *pBonus;
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


// Getters and Setters
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

void Map::print() const {
    // Implement to print map details
}


bool Map::validate() const {
    // DFS
    return false;
}













