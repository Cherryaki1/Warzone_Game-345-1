//
// Created by gregl on 9/11/2024.
//

#include "MapLoader.h"
#include "Map.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

using std::ifstream;
using std::stringstream;
using std::cout;
using std::endl;

MapLoader::MapLoader(const string& filename) {
    Map map = Map();
    loadFromFile(filename, map);
}

MapLoader::~MapLoader() {
    // Destructor
}

void MapLoader::loadFromFile(const string& filename, Map &map) {

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Failed to open file!" << endl;
        return;
    }

    string line, section;
    while (getline(file, line)) {
        if (line.empty() || line[0] == ';') continue;  // Skip comments or empty lines

        if (line[0] == '[') {
            // Section header, like [Map], [Continents], [Territories]
            section = line;
            continue;
        }

        stringstream ss(line);
        if (section == "[Continents]") {
            stringstream continentLineStream(line);
            string continentName;
            string bonusStr;

            while (getline(ss, line)) {
                // Create Continent
                getline(continentLineStream, continentName, '=');
                getline(continentLineStream, bonusStr);

                int bonus = stoi(bonusStr);

                cout << "Continent " << continentName << " created with bonus " << bonus << endl;

                Continent *continent = new Continent(continentName, bonus);
                map.getContinents().push_back(continent);
            }
        } else if (section == "[Territories]") {
            string name, continent, owner, skip;
            int x, y;
            vector<string> neighbors;

            getline(ss, name, ',');  // Territory name
            getline(ss, skip, ',');  // Skip x
            getline(ss, skip, ',');  // Skip y
            getline(ss, continent, ',');  // Continent name

            string neighbor;
            // Parse neighbors
            while (getline(ss, neighbor, ',')) {
                neighbors.push_back(neighbor);
            }

            // Territory Creation
            cout << "Territory " << name << " in continent " << continent << endl;
            Territory *territory = new Territory(name, owner, continent, 0);

            // Add Territories to Continent
            for (unsigned int i = 0; i < map.getContinents().size(); i++) {
                if (map.getContinents()[i]->getContinentID() == continent) {
                    map.getContinents()[i]->addTerritory(territory);
                }
            }
            map.getTerritories().push_back(territory);

            // Initialize adjacency list entry if it doesn't exist
            if (map.getAdjList().find(territory) == map.getAdjList().end()) {
                map.getAdjList()[territory] = list<Territory*>();
            }

            // Add neighbors as edges
            for (const auto& neighborName : neighbors) {
                // Neighbors are defined as territory names
                Territory *neighbor = new Territory(neighborName, owner, continent, 0);

                cout << "Territory adj " << neighbor->getName() << " in continent " << territory->getContinentID()
                << " connected to " << territory->getName() << endl;

                map.add_edge(territory, neighbor);
            }
        }
    }
  file.close();
}

