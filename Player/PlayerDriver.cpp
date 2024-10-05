#include "Player.h"
#include "MapLoader.h"
#include <iostream>

extern Map* globalMap;

using namespace std;

void testPlayers() {
    string filename = "../World 2007.map";
    MapLoader mapLoader(filename);
    mapLoader.loadFromFile(filename);
    Map& map = mapLoader.getMap();


    //cout << "Map loaded with " << mapLoader.getMap().getTerritories()->size() << " territories." << endl;

    Player player("John");

    cout << "\nTesting toDefend() method..." << endl;
    vector<Territory*> defendList = player.toDefend(map);
    cout << "Territories to Defend:" << endl;
    for (Territory* territory : defendList) {
        cout << "- " << territory->getName() << " with " << territory->getNumberOfArmies() << " armies" << endl;
    }

    // Step 4: Test toAttack()
    cout << "\nTesting toAttack() method..." << endl;
    vector<Territory*> attackList = player.toAttack(map);
    cout << "Territories to Attack:" << endl;
    for (Territory* territory : attackList) {
        cout << "- " << territory->getName() << " with " << territory->getNumberOfArmies() << " armies" << endl;
    }
}


