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

bool MapLoader::loadFromFile(const string& filename) { 

    Map map = Map();
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Failed to open file!" << endl;
        return false;
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
        if (section == "[Map]") {
            // Handle Map metadata if needed
        } else if (section == "[Continents]") {
            vector<Continent> continents;
            string continentName;
            int bonus;

            int i = 0;
            while (ss >> continentName >> bonus) {
                // Create Continent
                continents[i] = Continent(&continentName, &bonus);
                i++;
            }
            map.setContinents(continents);
        } else if (section == "[Territories]") {
            string name, continent, owner;
            int x, y;
            vector<string> neighbors;

            getline(ss, name, ',');  // Territory name
            ss >> x >> y;            // Coordinates (not used here, but could be stored)
            getline(ss, continent, ',');  // Continent name

            string neighbor;
            // Parse neighbors
            while (getline(ss, neighbor, ',')) {
                neighbors.push_back(neighbor);
            }
            
            Territory territory(&name, &owner, &continent, 0);
            // Initialize adjacency list entry if it doesn't exist
            if (map.getAdjList().find(territory) == map.getAdjList().end()) {
                map.getAdjList()[territory] = list<Territory>();
            }
            
            // Add neighbors as edges
            for (auto& neighborName : neighbors) {
                // Neighbors are defined as territory names
                Territory neighbor(&neighborName, &owner, &continent, 0);
                map.add_edge(territory, neighbor);
            }
        }
    }

  file.close();
}