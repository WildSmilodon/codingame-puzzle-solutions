#pragma once
#include "Common.h"
#include "Tile.h"

class Map {
public:
    std::vector<Tile> tiles;
    std::vector<int> myBases;
    std::vector<int> hisBases;
    int number_of_tiles; // amount of hexagonal cells in this map
    int number_of_bases;

    Map();
    void readInit();
    void readTurn();

    friend std::ostream& operator<<(std::ostream& ioOut, const Map& obj);

    std::vector<int> getPath(int start, int end);

};