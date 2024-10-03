#ifndef MAP_H
#define MAP_H


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
        string *pName;
        string *pOwner; // Change to Player class
        string *pContinentID;
        int *pNumber_of_armies;

    public:
        Territory();
        Territory(string name, string owner, string continentID, int number_of_armies);
        ~Territory();
        string getName();
        string getOwner();
        string getContinentID();
        int getNumberOfArmies();

        void setPlayer(string player);
        void setNumberOfArmies(int number_of_armies);
};

class Continent {
    private:
        string *pContinentID;
        int *pBonus;

    public:
        Continent() {};
        Continent(string continentID, int bonus);

        string getContinentID();
        int getBonus();

};

class Map {
    private:
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


#endif