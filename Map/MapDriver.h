//
// Created by gregl on 9/24/2024.
//

#ifndef MAPDRIVER_H
#define MAPDRIVER_H
#include "Map.h"

int testLoadMap();
Map& loadMap(string mapFile);
void validateMap(Map& loadedMap);
#endif //MAPDRIVER_H
