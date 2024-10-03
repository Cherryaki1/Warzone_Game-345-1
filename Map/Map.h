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
        string continentID;
        int bonus;
        vector<Territory> territories;

    public:
        Continent() {};
        Continent(const string* continentID, int* bonus);
        Continent(const string* continentID, vector<Territory*> territories);

        string getContinentID() const;
        vector<Territory> getTerritories();

};

class Map {
    private:
        int num_territories;
        vector<Continent> continents; // Changed to a vector to hold multiple continents
        vector<Territory> territories;
        map<Territory, list<Territory>> adjList;

    public:
        ~Map();
        Map() {};
        Map(int num_territories);
        void add_edge(Territory u, Territory v);

        void setAdjList(map<Territory, list<Territory>> adjList);
        map<Territory, list<Territory>> getAdjList();
        void setContinents(vector<Continent> continents);
        vector<Continent> getContinents();
        void setTerritories(vector<Territory> territories);
        vector<Territory> getTerritories();

        void print();
        bool validate();
};;


#endif MAP_H