#include <iostream>
#include <string>
#include "MapDriver.h"
#include "MapLoader.h"
#include "Map.h"

using namespace std;

extern Map* globalMap;


void testLoadMap(string name) {
    // Load the map
    const string mapFile = "../DownloadedMaps/" + name; // Change the name of the map file HERE!!!

    MapLoader mapLoader(mapFile);
    cout << "MapLoader created" << endl;
    Map& loadedMap = mapLoader.getMap();
    //Output the number of territories loaded
    cout << "Map loaded succesfully with " << loadedMap.getTerritories()->size() << " territories." << endl;

    // Validate the map
    if (loadedMap.validate()) {
        cout << " ** MAP IS VALID **" << endl;
        // FULL MAP:
        cout << loadedMap << endl;

    } else {
        cout << " !! MAP IS INVALID !!" << endl;

    }
}

void validateMap(Map& loadedMap) {
    // Validate the map
    if (loadedMap.validate()) {
        cout << " ** MAP IS VALID **" << endl;
        // FULL MAP:
        cout << loadedMap << endl;

    } else {
        cout << " !! MAP IS INVALID !!" << endl;

    }
}

