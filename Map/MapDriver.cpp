#include <iostream>
#include <string>
#include "MapDriver.h"
#include "MapLoader.h"
#include "Map.h"

using namespace std;

extern Map* globalMap;

int testLoadMap() {
    // Load the map
    const string mapFile = "../World 2007.map"; // change the name of the map file HERE!!!
    MapLoader mapLoader(mapFile);
    cout << "MapLoader created" << endl;
    //cout << "Map loaded with " << map.getTerritories()->size() << " territories." << endl;

    // Validate
    return 0;
}