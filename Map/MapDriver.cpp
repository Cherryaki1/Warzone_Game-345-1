#include <iostream>
#include <string>
#include "MapDriver.h"
#include "MapLoader.h"
#include "Map.h"

using namespace std;

extern Map* globalMap;


int testLoadMap() {
    // Load the map
    const string mapFile = "../DownloadedMaps/Europe 4B.map"; // Change the name of the map file HERE!!!
    MapLoader mapLoader(mapFile);

    cout << "MapLoader created" << endl;

    Map& loadedMap = mapLoader.getMap();

    // Output the number of territories loaded
    cout << "Map loaded with " << loadedMap.getTerritories()->size() << " territories." << endl;

    // Validate the map
    if (loadedMap.validate()) {
        cout << "Map is valid!" << endl;
    } else {
        cout << "Map is invalid!" << endl;
    }

    //cout << loadedMap << endl;

    return 0;
}
