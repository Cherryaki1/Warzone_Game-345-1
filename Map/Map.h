#ifndef MAP_H
#define MAP_H

#include <bitset>
#include <string>
#include <list>
#include <map>
#include <vector>

#include "Map.h"

using std::string;
using std::vector;
using std::list;
using std::map;


class Territory {
    private:
        string name;
        string owner; // Change to Player class
        string continentID;
        int number_of_armies;

    public:
        Territory() {};
        Territory(string* name, string* owner, const string* continentID, int* number_of_armies);
        ~Territory();
        string getName() const;
        string getOwner();
        string getContinentID() const;
        int getNumberOfArmies();

        void setPlayer(string player);
        void setNumberOfArmies(int number_of_armies);
};

class Continent {
    private:
        string name;
        string continentID;
        vector<Territory> territories;

    public:
        Continent() {};
        Continent(string* name, const string* continentID, vector<Territory*> territories);

        string getName() const;
        string getContinentID() const;
        vector<Territory> getTerritories();

};

class Map {
    private:
        map<Territory, list<Territory> > adjList;
        Continent continents;
        Territory territories;
        ~Map();

    public:
        Map() {};
        Map(map<Territory, list<Territory> > adjList);
        void add_edge(Territory u, Territory v);

        void print();
        bool validate();
};


#endif