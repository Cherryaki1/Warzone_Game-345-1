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
    loadFromFile(filename);
}

MapLoader::~MapLoader() {
    // Destructor
}

Map &MapLoader::getMap() {
    return map;
}

void MapLoader::loadFromFile(const string& filename) {

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Failed to open file!" << endl;
        return;
    }

    string line, section;
    vector<Continent*>* continents = map.getContinents();
    vector<Territory*>* territories = map.getTerritories();
    while (getline(file, line)) {
        if (line.empty() || line[0] == ';') continue;  // Skip comments or empty lines

        if (line[0] == '[') {
            // Section header, like [Map], [Continents], [Territories]
            section = line;
            continue;
        }

        stringstream ss(line);
        if (section == "[Continents]") {
            string continentName;
            int bonus;

            // Read continent name and bonus
            getline(ss, continentName, '=');
            ss >> bonus;

            // Create and store the continent
            Continent* continent = new Continent(continentName, bonus);
            continents->push_back(continent);

        } else if (section == "[Territories]") {
            string name, continent, owner, skip;
            int x, y;
            vector<string> neighbors = {};

            getline(ss, name, ',');  // Territory name
            getline(ss, skip, ',');  // Skip x
            getline(ss, skip, ',');  // Skip y
            getline(ss, continent, ',');  // Continent name

            string neighbor;
            // Parse neighbors
            while (getline(ss, neighbor, ',')) {
                neighbors.push_back(neighbor);
            }

            // Create Territory
            Territory *territory = new Territory(name, owner, continent, 0);
            territories->push_back(territory);  // Add to map's territories

            // Add Territories to Continent
            for (auto& cont : *continents) {
                if (cont->getContinentID() == continent) {
                    cont->addTerritory(territory);  // Add territory to continent
                    break;
                }
            }

            // Initialize adjacency list entry if it doesn't exist
            if (map.getAdjList()->find(territory) == map.getAdjList()->end()) {
                (*map.getAdjList())[territory] = list<Territory*>();
            }

            // Add neighbors as edges
            for (const auto& neighborName : neighbors) {
                // Neighbors are defined as territory names
                Territory *neighborTerritory = new Territory(neighborName, owner, continent, 0);

                map.add_edge(territory, neighborTerritory);  // Add edge between territory and neighbor
            }
        }

    }
  file.close();
}

