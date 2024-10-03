#include <iostream>
#include <string>
#include "MapDriver.h"
#include "MapLoader.h"
#include "Map.h"

using namespace std;

int testLoadMap() {
    // Load the map
    const string mapFile = "map.map"; // change the name of the map file HERE!!!
    MapLoader mapLoader(mapFile);
    cout << "MapLoader created" << endl;

    // Validate
    return 0;
}