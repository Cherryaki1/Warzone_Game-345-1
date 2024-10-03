#include <iostream>
#include "MapDriver.h"
#include "MapLoader.h"
#include "Map.h"

using namespace std;

int testLoadMap() {
    // Load the map
    MapLoader mapLoader("USA.map");

    cout << "MapLoader created" << endl;

    // Validate
    return 0;
}