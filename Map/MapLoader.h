
#ifndef MAPLOADER_H
#define MAPLOADER_H
#include "Map.h"

class MapLoader {
public:
    MapLoader() = default;
    ~MapLoader();

    MapLoader(const string &filename);

    void loadFromFile(const string &filename, Map &map);
};

#endif
