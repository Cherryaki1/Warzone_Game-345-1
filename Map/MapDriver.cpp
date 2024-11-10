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
        cout << " ** MAP IS VALID **" << endl;
        // FULL MAP:
        cout << loadedMap << endl;
    } else {
        cout << " !! MAP IS INVALID !!" << endl;
    }

    return 0;
}

