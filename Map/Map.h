#ifndef MAP_H
#define MAP_H


#include <string>
#include <list>
#include <map>
#include <set>
#include <vector>

using std::string;
using std::vector;
using std::list;
using std::set;
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

    bool operator==(const Territory& other) const;
    bool operator<(const Territory& other) const;  // Comparison for use in map
    friend std::ostream& operator<<(std::ostream& os, const Territory& territory);

    string getName() const;
    void setName(const string &name);
    string getOwner() const;
    void setOwner(const string &player);
    string getContinentID() const;
    void setContinentID(const string &continentID);
    int getNumberOfArmies() const;
    void setNumberOfArmies(int number_of_armies);
    bool isAdjacent(Territory* other);
    vector<Territory*> adjacentTerritories;
};

class Continent {
private:
    string *pContinentID;
    vector<Territory *> *pCTerritories{};
    int *pBonus;

public:
    Continent();
    Continent(string continentID, int bonus);
    Continent(const Continent &other);  // Copy constructor
    Continent& operator=(const Continent &other);  // Assignment operator
    ~Continent();

    void addTerritory(Territory *territory);

    friend std::ostream& operator<<(std::ostream& os, const Continent& continent);

    string getContinentID() const;
    void setContinentID(const string &continentID);
    vector <Territory *> getCTerritories() const;
    void setCTerritories(vector<Territory *> territories);
    int getBonus() const;
    void setBonus(int bonus);
};

class Map {
    private:
        vector<Continent*> *pContinents;  // Pointer to vector of continents
        vector<Territory*> *pTerritories;  // Pointer to vector of territories
        map<Territory*, list<Territory*>> *pAdjList;  // Pointer to adjacency list

    public:

        Map();
        ~Map();

        void add_edge(Territory* u, Territory* v);

        void DFS(Territory* start, set<Territory*> &visited);
        void DFSContinent(Territory* start, set<Territory*> &visited, Continent* continent);
        bool isGraphConnected();
        bool isContinentConnected(Continent* continent);
        bool hasUniqueContinent();
        bool validate();
        

        friend std::ostream& operator<<(std::ostream& os, Map& map);

        void setAdjList(map<Territory*, list<Territory*>> *adjList);
        map<Territory*, list<Territory*>>* getAdjList();
        void setContinents(vector<Continent*> *continents);
        vector<Continent*>* getContinents();
        void setTerritories(vector<Territory*> *territories);
        vector<Territory*>* getTerritories();
};


#endif