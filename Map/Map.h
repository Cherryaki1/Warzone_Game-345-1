#ifndef MAP_H
#define MAP_H


#include <string>
#include <list>
#include <map>
#include <vector>

using std::string;
using std::vector;
using std::list;
using std::map;


class Territory {
private:
    string *pName;
    string *pOwner;  // Pointer to the owner (future Player class)
    string *pContinentID;
    int *pNumber_of_armies;

public:
    Territory();
    Territory(string name, string owner, string continentID, int number_of_armies);
    Territory(const Territory &other);  // Copy constructor
    Territory& operator=(const Territory &other);  // Assignment operator
    ~Territory();

    string getName() const;
    string getOwner() const;
    string getContinentID() const;
    int getNumberOfArmies() const;

    void setPlayer(const string &player);
    void setNumberOfArmies(int number_of_armies);

    bool operator<(const Territory& other) const;  // Comparison for use in map
};

class Continent {
private:
    string *pContinentName;
    int *pBonus;

public:
    Continent();
    Continent(string continentName, int bonus);
    Continent(const Continent &other);  // Copy constructor
    Continent& operator=(const Continent &other);  // Assignment operator
    ~Continent();

    string getContinentName() const;
    int getBonus() const;
};

class Map {
    private:
        vector<Continent*> *pContinents;  // Pointer to vector of continents
        vector<Territory*> *pTerritories;  // Pointer to vector of territories
        map<Territory*, list<Territory*>> *pAdjList;  // Pointer to adjacency list

    public:
        Map();
        Map(int num_territories);
        ~Map();

        void add_edge(Territory* u, Territory* v);

        void setAdjList(map<Territory*, list<Territory*>> *adjList);
        map<Territory*, list<Territory*>>* getAdjList();

        void setContinents(vector<Continent*> *continents);
        vector<Continent*>* getContinents();

        void setTerritories(vector<Territory*> *territories);
        vector<Territory*>* getTerritories();

        void print() const;
        bool validate() const;  // Const because it doesn't modify the object
};


#endif