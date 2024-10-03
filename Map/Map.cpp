#include "Map.h"
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <map>
using namespace std;

int testLoadMap() {
    return 0;
}

// Territory Class Implementation
Territory::Territory() {
    pName = nullptr;
    pOwner = nullptr;
    pContinentID = nullptr;
    pNumber_of_armies = nullptr;
}

Territory::Territory(string name, string owner, string continentID, int number_of_armies)
{
    *pName = std::move(name);
    *pOwner = std::move(owner);
    *pContinentID = std::move(continentID);
    *pNumber_of_armies = number_of_armies;
}

Territory::~Territory() {
    delete pName;
    delete pOwner;
    delete pContinentID;
    delete pNumber_of_armies;
}

string Territory::getName() {
    return *pName;
}

string Territory::getOwner() {
    return *pOwner;
}

string Territory::getContinentID() {
    return *pContinentID;
}

int Territory::getNumberOfArmies() {
    return *pNumber_of_armies;
}

void Territory::setPlayer(string player) {
    *pOwner = player;
}

void Territory::setNumberOfArmies(int number_of_armies) {
    *pNumber_of_armies = number_of_armies;
}

// Continent Class Implementation

Continent::Continent(string continentID, int bonus) {
    *pContinentID = std::move(continentID);
    *pBonus = bonus;
}


string Continent::getContinentID() {
    return *pContinentID;
}

int Continent::getBonus() {
    return *pBonus;
}

// Map Class Implementation

Map::~Map() {
    this->adjList.clear();
}

void Map::add_edge(Territory u, Territory v) {
    adjList[u].push_back(v);
    adjList[v].push_back(u);
}

void Map::setAdjList(map<Territory, list<Territory>> adjList) {
    this->adjList = std::move(adjList);
}

map<Territory, list<Territory>> Map::getAdjList() {
    return map<Territory, list<Territory>>();
}

void Map::setContinents(vector<Continent> continents) {
    this->continents = continents;
}

vector<Continent> Map::getContinents() {
    return vector<Continent>();
}

void Map::setTerritories(vector<Territory> territories) {
    this->territories = territories;
}

vector<Territory> Map::getTerritories() {
    return vector<Territory>();
}

void Map::print() {
}

bool Map::validate() {
    // DFS
    return false;
}











