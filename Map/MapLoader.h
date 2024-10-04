
#ifndef MAPLOADER_H
#define MAPLOADER_H
#include "Map.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

class MapLoader {
public:
    MapLoader() = default;
    ~MapLoader();

    MapLoader(const string &filename);

    void loadFromFile(const string &filename, Map &map);

    Map& getMap();
private:
    Map map; // Internal map object where loaded data is stored
};

#endif
