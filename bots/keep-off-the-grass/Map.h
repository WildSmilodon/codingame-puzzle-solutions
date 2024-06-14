#pragma once
#include <iostream>
#include "Common.h"
#include "Tile.h"

class Map {

public:

    int width;
    int height;

    Tile tiles[maxHeight][maxWidth];

    Map();
    void read();
    void readWH();

};