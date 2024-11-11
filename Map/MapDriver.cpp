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

    // Output the number of territories loaded
    cout << "Map loaded with " << loadedMap.getTerritories()->size() << " territories." << endl;

}

Map& loadMap(string name) {
    const string mapFile = "../DownloadedMaps/" + name;
    MapLoader *mapLoader = new MapLoader(mapFile);
    cout << "MapLoader created" << endl;
    Map& loadedMap = mapLoader->getMap();

    // Output the number of territories loaded
    cout << "Map loaded with " << loadedMap.getTerritories()->size() << " territories." << endl;
    return loadedMap;
}
bool validateMap(Map& loadedMap) {
    // Validate the map
    if (loadedMap.validate()) {
        cout << " ** MAP IS VALID **" << endl;
        // FULL MAP:
        cout << loadedMap << endl;
        return true;
    } else {
        cout << " !! MAP IS INVALID !!" << endl;
        return false;
    }
}

