
#ifndef MAPLOADER_H
#define MAPLOADER_H
#include "Map.h"

class MapLoader {
public:
    MapLoader() = default;
    ~MapLoader() = default;

    MapLoader(const string &filename);

    bool loadFromFile(const string &filename);
};

#endif //MAPLOADER_H
