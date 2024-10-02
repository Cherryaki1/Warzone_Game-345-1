#include "Map.h"
#include <iostream>
#include <string>
#include <utility>
using namespace std;

int testLoadMap() {
    return 0;
}

// Territory Class Implementation

Territory::Territory(string* name, string* owner, const string* continentID, int* number_of_armies)
{
    this->name = *name;
    this->owner = *owner;
    this->continentID = *continentID;
    this->number_of_armies = *number_of_armies;
}

Territory::~Territory() {
    this->owner.clear();
}

string Territory::getName() const {
    return this->name;
}

string Territory::getOwner() {
    return this->owner;
}

string Territory::getContinentID() const {
    return this->continentID;
}

int Territory::getNumberOfArmies() {
    return this->number_of_armies;
}

void Territory::setPlayer(string player) {
    this->owner = player;
}

void Territory::setNumberOfArmies(int number_of_armies) {
    this->number_of_armies = number_of_armies;
}

// Continent Class Implementation

Continent::Continent(string* name, const string* continentID, vector<Territory*> territories) {
    this->name = *name;
    this->continentID = *continentID;
    for (auto &territory : territories) {
        this->territories.push_back(*territory);
    }
}

string Continent::getName() const {
    return this->name;
}

string Continent::getContinentID() const {
    return this->continentID;
}

vector<Territory> Continent::getTerritories() {
    return this->territories;
}

// Map Class Implementation

Map::Map(map<Territory, list<Territory> > adjList) {
    this->adjList = std::move(adjList);
}

Map::~Map() {
    this->adjList.clear();
}

void Map::add_edge(Territory u, Territory v) {
    this->adjList[u].push_back(v);
}

void Map::print() {
    for (auto &i : this->adjList) {
        cout << i.first.getName() << " -> ";
        for (auto &j : i.second) {
            cout << j.getName() << " ";
        }
        cout << endl;
    }
}











