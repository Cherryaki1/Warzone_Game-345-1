#ifndef MAP_H
#define MAP_H

#include <string>
#include <list>
#include <map>
#include <vector>

#include "Map.h"

using namespace std;


class Territory {
    string name;
    string player; // Change to Player class
    int continentID;
    int number_of_armies;

public:
    Territory(string name, int continentID, string player, int number_of_armies = 0);

};

class Continent {
    string name;
    int continentID;
    vector<Territory> territories;

public:
    Continent(string name, Territory territories);
};

class Map {
    map<Territory, list<Territory> > adjList;
    Continent continents;
    Territory territories;

    public:
    Map(map<Territory, list<Territory> > adjList, Territory territories, Continent continents);
    void add_edge(Territory u, Territory v);
    void print();
    bool validate();
};

#endif